#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<math.h>

/*
散列的哲学是直接根据关键字计算处存储位置，这样可以突破太耗时的比较操作带来的比较树下界

散列要解决两个问题：
1.散列函数的构造，要简单，均匀
2.发生冲突的时候采取方法处理

散列函数有：
1.直接定址法，这个要求数据对象和存储位置的集合大小相等，直接用一个线性函数确定位置
	比如年龄: h(key) = key;
	90后: h(key) = a * key + b
2.对于数字型关键字,使用除留余数法，注意质数的使用和装填因子 p; alpha = n/m
	h(key) = key % table_size
3.数字有的数位基本不发生变化，我们为了取得好的效果可以选取其中的一部分做除留余数法，而不是全部、
	比如数字分析法、
	折叠法、
	平方取中法
4.字符串形式的关键字，我们可以将其转换成整数
	采用ASCII码加和法;
		缺点是字符串长时冲突严重
	将其看作27进制的整数;
		为了计算更快，可以扩展到32进制，这样只需要移位运算就行，采用秦九韶算法更快、
	如果字符串太长，可能移位出界，或者只有低位起作用;
		我们可以在转换之前进行选取来改进

装填因子定义为数组的填充程度或者链表的平均长度，参考值分别为0.5-0.85；2-5；

处理冲突的方法有两个思路：
	第一种直接换个位置，开放定址法,结构是紧凑的，但是删除只能懒惰删除，带来很多垃圾元素、
	第二种手段是将冲突的元素集中组织，链地址法，插入删除在链表上进行，缺点是查找可能比较慢

线性探测法：hi(key) = [h(key) + i] % table_size，可能产生一次聚集现象
平方探测法：hi(key) = [h(key) + （+-）i^2] % table_size，可能产生二次聚集现象
	这里如果table_size 是 4k + 3的质数，那么可以探测到所有空间
双散列法：hi(key) = [h(key) + (h2(key))] % table_size
	这里h2会影响散列函数的性能，一个比较好的是：h2(key) = p - (key mod p)
再散列：当数组的装填因子过大时，效率会大大的下降，此时将散列表整体搬迁到一个2倍大小的数组中。
	对于实时系统可能无法忍受这种停顿。

链地址法采用结构数组存储指针，指针指向链表的头结点，在链表的头部进行插入，尾部删除

散列的数学分析有线性试探、平方试探、链地址法，按平均查找次数分为两类情况：
	插入和不成功的查找；
	成功的查找

散列以空间换时间，并且不支持范围查找，最大最小值的查找，顺序查找
	
*/

#include<ctype.h>
//ASCII加和法
int hash_ascii_sum(char* key, int table_size)
{
		int ascii_sum = 0;
		while (*key != '\0') {
			ascii_sum += toascii(*key);
			key++;
		}
		return ascii_sum % table_size;
}

//位移映射，移位法
int hash_shift(char* key, int table_size)
{
	unsigned hashcode = 0;
	while (*key != '\0') {
		hashcode = (hashcode << 5) + *key;//秦九韶
		key++;
	}
	return hashcode % table_size;
}

//开放定址法的初始化
#define MAXTABLESIZE 100000//允许开辟的最大散列表长度
typedef int elemtype;//关键字类型
typedef int index;//散列地址类型
typedef index position;//数据所在的位置 和 散列地址是一种类型

typedef enum { legitimate, empty, deleted }entry_type;//散列表单元的类型

typedef struct hash_entry cell;
struct hash_entry {
	elemtype data;
	entry_type info;//单元状态
};

//hash表是一个结点
typedef struct table_node* hash_table;
struct table_node {
	int table_size;
	cell* cells;//存放数据的数组
};

//这是一种求质数的筛法
int next_prime(int n)//返回一个大于n，不超过MAXTABLESIZE的最小质数
{
	int i;
	int p = (n % 2 == 0) ? n + 1 : n+2;//从大于n的下一个奇数检测是不是质数

	while (p <= MAXTABLESIZE) {
		for (i = (int)sqrt(p); i > 2; i--) {
			if (!(p % i))//不是质数，失去资格
				break;
		}
		if (p == 2)//for正常结束，p是一个质数
			break;
		else
			p += 2;//去考虑下一个奇数
	}

	return p;
}

hash_table create_hash_table(int table_size)
{
	hash_table h = (hash_table)malloc(sizeof(struct table_node));
	h->table_size = next_prime(table_size);
	h->cells = (cell*)malloc(h->table_size * sizeof(cell));

	for (int i = 0; i < h->table_size; i++) {
		h->cells[i].info = empty;
	}

	return h;
}

//除留余数法
int hash_1(int key, int table_size)
{
	return key % table_size;
}

//使用平方探测法进行查找和插入删除
position find(hash_table h, elemtype key)
{
	position curr_position;
	position new_position;

	int collision_count = 0;
	new_position = curr_position = hash_1(key, h->table_size);//初始散列位置
	while (h->cells[new_position].info != empty &&
		h->cells[new_position].data != key) {
		if (++collision_count % 2) {//奇数次冲突
			new_position = curr_position+(collision_count + 1) * (collision_count + 1) / 4;
			if (new_position > h->table_size)
				new_position = new_position % h->table_size;//地址过大调整
		}
		else {//偶数次冲突
			new_position = curr_position - collision_count * collision_count / 4;
			while (new_position < 0)
				new_position += h->table_size;//调整为合法地址
		}
	}

	return new_position;
}

bool insert(hash_table h, elemtype key)
{
	position pos = find(h, key);

	if (h->cells[pos].info != legitimate) {//如果没有被占
		h->cells[pos].info = legitimate;
		h->cells[pos].data = key;
		return true;
	}
	else {
		printf("has existed\n");
		return false;
	}
}















int main()
{
	int arr[] = { 47,7,29,11,9,84,54,20,30 };
	int table_size = 13;

	int a = 2;
	printf("%d\n", ++a % 2);


	return 0;
}


