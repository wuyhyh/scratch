//ĳ�̵�涨����������ˮƿ���Ի�һƿ��ˮ���������ϰ�����ˮƿ�����Ǳ���Ҫ�黹����
//С��������n������ˮƿ������֪���Լ������Ժȵ�����ƿ��ˮ��
//���ݷ�Χ����������������� 1 \le n \le 100 \1��n��100
//
//ע�⣺������ڶ������롣����� 0 ��ʾ�����������������������

//����һ���ݹ�����
//Ҳ����������������
#include<iostream>
using namespace std;

void kidding(int num)
{

	cout << num / 2 << endl;

}

#define SWAP 3
int recursive(int empty_bottle)
{
	if (empty_bottle == SWAP - 1) {//��ƿ�ͽ���
		return 1;
	}
	else if (empty_bottle < SWAP - 1) {//������ƿ����
		return 0;
	}

	//׼����ʼ��
	int rest = 0;
	int drinked = 0;
	drinked = empty_bottle / SWAP;
	rest = drinked + empty_bottle % SWAP;

	return drinked + recursive(rest);//ע�ⷵ�ص����ܵĺȵ���ƿ����
}


int main()
{
	int num;
	while (cin >> num && num != 0) {
		cout << recursive(num) << endl;
		//kidding(num);
	}

	return 0;
}