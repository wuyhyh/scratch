
#include <stdio.h>
#include <ctype.h>
#include <string.h>

char *name[20] = { //这里有20个人的名字
	"zhangsan", "lisi",			"wangmazi",		 "ergoudan",	"tieniu",
	"dabendan", "xunan",		"zhoulei",		 "wuyuhang",	"gaowenwen",
	"jujiayi",	"zhaoshunchao", "zhangtianhang", "dengxianli",	"fengchenfan",
	"qinzhen",	"yaochan",		"suhuiqing",	 "caizhongjun", "lizhi"
};

//我们把名字这种字符串当作大整数，这里需要一种转换
int name_to_int(char *name)
{
	int temp = 0;
	int i = 0;
	while (*name++ != '\0')
		temp += toascii(name[i]);
	return temp;
}

#define M 41 //除留余数法散列数组大小要选质数，0~42,这里的装填因子大概是0.5
typedef char *Key;
Key keys[M]; //键保存名字的字符串

//散列函数
int hash(Key key)
{
	int index = name_to_int(key) % M; //除余法
	return index;
}

int insert_key(Key key)
{
	int i;
	for (i = hash(key); keys[i] != NULL;
		 i = (i + 1) % M) { //如果冲突就向右边移动一位再次用除余法探测
		if (key == keys[i]) {
			return;
		}
	}
	keys[i] = key;
	return i;
}

int get_index(Key key) //查找key的位置
{
	int i;
	for (i = hash(key); keys[i] != NULL; i = (i + 1) % M) {
		if (strcmp(key, keys[i]) == 0) {
			return i;
		}
	}
	return -1;
}

void delete_key(
	Key key) //删除一个键，删除一个键不能简单将其设为空，还可能要把其右边的元素移动过来
{
	if (get_index(key) < 0) {
		return;
	}

	int i = hash(key); //检查有没有冲突的清况，避免杀错人
	while (strcmp(key, keys[i]) != 0) {
		i = (i + 1) % M;
	}
	keys[i] = NULL;
	i = (i + 1) % M;

	while (keys[i] !=
		   NULL) { //先保存要移除的元素(key_to_remove),把右侧的元素迁移过来
		Key key_to_re = keys[i];
		keys[i] = NULL;
		insert_key(key_to_re);
		i = (i + 1) % M;
	}
}

void show_keys()
{
	printf("序号\t\t键\n\n");
	for (int i = 0; i < M; i++) {
		printf("%2d:%15s\n", i, keys[i]);
	}
	printf("\n\n");
}

int main()
{
	//show_keys();
	//构建hash表
	for (int i = 0; i < 20; i++) {
		insert_key(name[i]);
	}
	show_keys();

	while (1) {
		printf("输入新的key:\n");
		char new_name[100] = { 0 };
		scanf("%s", &new_name);
		getchar();

		int pos = get_index(new_name);
		if (pos > 0) {
			printf("%s 已存在在位置 %d,是否删除(y/n)\n", new_name, pos);
			int c = getchar();
			getchar();
			switch (c) {
			case 'n':
				break;
			case 'y': {
				printf("%s 已删除\n", new_name), delete_key(new_name);
				break;
			}
			default:
				printf("无效输入\n");
				break;
			}
		} else {
			printf("%s 不存在，已插入到位置%d\n", new_name,
				   insert_key(new_name));
		}

		printf("是否显示hash_table(y/n)\n");
		int c = getchar();
		getchar();
		switch (c) {
		case 'n':
			break;
		case 'y':
			show_keys();
			break;
		default:
			printf("无效输入\n");
			break;
		}
	}

	return 0;
}

//我们希望尽量快地查找某些关键字，如果我们可以把关键字转换成数组的坐标，再把关键字放在那里，形成一对。
//我们称为键值对，键key就是关键字，比如字符串，值value就是根据key算出来的。
//我们下次要找的时候，直接计算出坐标去找就只需要很少的时间。
//问题的关键是寻找一种好的计算公式，hash函数，够简单，分布够均匀。（我们用除余法）
//有一个问题值得注意，不同的key可能会计算出相同的value，这样就放不下了，我们需要一个策略来处理这种冲突。（线性探测）
//hash是一个空间换时间的例子，我们要在适度的时空之中权衡。