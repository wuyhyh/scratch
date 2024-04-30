#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<math.h>

/*
ɢ�е���ѧ��ֱ�Ӹ��ݹؼ��ּ��㴦�洢λ�ã���������ͻ��̫��ʱ�ıȽϲ��������ıȽ����½�

ɢ��Ҫ����������⣺
1.ɢ�к����Ĺ��죬Ҫ�򵥣�����
2.������ͻ��ʱ���ȡ��������

ɢ�к����У�
1.ֱ�Ӷ�ַ�������Ҫ�����ݶ���ʹ洢λ�õļ��ϴ�С��ȣ�ֱ����һ�����Ժ���ȷ��λ��
	��������: h(key) = key;
	90��: h(key) = a * key + b
2.���������͹ؼ���,ʹ�ó�����������ע��������ʹ�ú�װ������ p; alpha = n/m
	h(key) = key % table_size
3.�����е���λ�����������仯������Ϊ��ȡ�úõ�Ч������ѡȡ���е�һ������������������������ȫ����
	�������ַ�������
	�۵�����
	ƽ��ȡ�з�
4.�ַ�����ʽ�Ĺؼ��֣����ǿ��Խ���ת��������
	����ASCII��Ӻͷ�;
		ȱ�����ַ�����ʱ��ͻ����
	���俴��27���Ƶ�����;
		Ϊ�˼�����죬������չ��32���ƣ�����ֻ��Ҫ��λ������У������ؾ����㷨���졢
	����ַ���̫����������λ���磬����ֻ�е�λ������;
		���ǿ�����ת��֮ǰ����ѡȡ���Ľ�

װ�����Ӷ���Ϊ��������̶Ȼ��������ƽ�����ȣ��ο�ֵ�ֱ�Ϊ0.5-0.85��2-5��

�����ͻ�ķ���������˼·��
	��һ��ֱ�ӻ���λ�ã����Ŷ�ַ��,�ṹ�ǽ��յģ�����ɾ��ֻ������ɾ���������ܶ�����Ԫ�ء�
	�ڶ����ֶ��ǽ���ͻ��Ԫ�ؼ�����֯������ַ��������ɾ���������Ͻ��У�ȱ���ǲ��ҿ��ܱȽ���

����̽�ⷨ��hi(key) = [h(key) + i] % table_size�����ܲ���һ�ξۼ�����
ƽ��̽�ⷨ��hi(key) = [h(key) + ��+-��i^2] % table_size�����ܲ������ξۼ�����
	�������table_size �� 4k + 3����������ô����̽�⵽���пռ�
˫ɢ�з���hi(key) = [h(key) + (h2(key))] % table_size
	����h2��Ӱ��ɢ�к��������ܣ�һ���ȽϺõ��ǣ�h2(key) = p - (key mod p)
��ɢ�У��������װ�����ӹ���ʱ��Ч�ʻ�����½�����ʱ��ɢ�б������Ǩ��һ��2����С�������С�
	����ʵʱϵͳ�����޷���������ͣ�١�

����ַ�����ýṹ����洢ָ�룬ָ��ָ�������ͷ��㣬�������ͷ�����в��룬β��ɾ��

ɢ�е���ѧ������������̽��ƽ����̽������ַ������ƽ�����Ҵ�����Ϊ���������
	����Ͳ��ɹ��Ĳ��ң�
	�ɹ��Ĳ���

ɢ���Կռ任ʱ�䣬���Ҳ�֧�ַ�Χ���ң������Сֵ�Ĳ��ң�˳�����
	
*/

#include<ctype.h>
//ASCII�Ӻͷ�
int hash_ascii_sum(char* key, int table_size)
{
		int ascii_sum = 0;
		while (*key != '\0') {
			ascii_sum += toascii(*key);
			key++;
		}
		return ascii_sum % table_size;
}

//λ��ӳ�䣬��λ��
int hash_shift(char* key, int table_size)
{
	unsigned hashcode = 0;
	while (*key != '\0') {
		hashcode = (hashcode << 5) + *key;//�ؾ���
		key++;
	}
	return hashcode % table_size;
}

//���Ŷ�ַ���ĳ�ʼ��
#define MAXTABLESIZE 100000//�����ٵ����ɢ�б���
typedef int elemtype;//�ؼ�������
typedef int index;//ɢ�е�ַ����
typedef index position;//�������ڵ�λ�� �� ɢ�е�ַ��һ������

typedef enum { legitimate, empty, deleted }entry_type;//ɢ�б�Ԫ������

typedef struct hash_entry cell;
struct hash_entry {
	elemtype data;
	entry_type info;//��Ԫ״̬
};

//hash����һ�����
typedef struct table_node* hash_table;
struct table_node {
	int table_size;
	cell* cells;//������ݵ�����
};

//����һ����������ɸ��
int next_prime(int n)//����һ������n��������MAXTABLESIZE����С����
{
	int i;
	int p = (n % 2 == 0) ? n + 1 : n+2;//�Ӵ���n����һ����������ǲ�������

	while (p <= MAXTABLESIZE) {
		for (i = (int)sqrt(p); i > 2; i--) {
			if (!(p % i))//����������ʧȥ�ʸ�
				break;
		}
		if (p == 2)//for����������p��һ������
			break;
		else
			p += 2;//ȥ������һ������
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

//����������
int hash_1(int key, int table_size)
{
	return key % table_size;
}

//ʹ��ƽ��̽�ⷨ���в��ҺͲ���ɾ��
position find(hash_table h, elemtype key)
{
	position curr_position;
	position new_position;

	int collision_count = 0;
	new_position = curr_position = hash_1(key, h->table_size);//��ʼɢ��λ��
	while (h->cells[new_position].info != empty &&
		h->cells[new_position].data != key) {
		if (++collision_count % 2) {//�����γ�ͻ
			new_position = curr_position+(collision_count + 1) * (collision_count + 1) / 4;
			if (new_position > h->table_size)
				new_position = new_position % h->table_size;//��ַ�������
		}
		else {//ż���γ�ͻ
			new_position = curr_position - collision_count * collision_count / 4;
			while (new_position < 0)
				new_position += h->table_size;//����Ϊ�Ϸ���ַ
		}
	}

	return new_position;
}

bool insert(hash_table h, elemtype key)
{
	position pos = find(h, key);

	if (h->cells[pos].info != legitimate) {//���û�б�ռ
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


