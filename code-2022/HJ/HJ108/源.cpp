//������A��������B ����С��������ָ �ܱ�A��B��������С��������ֵ��
//���һ���㷨��������A��B����С��������

//��ѧԭ���̳��������й�����������������֮������Ϊ��С��������

//��ѧԭ��2����С������ = �����˻��������ǵ����Լ��

//��ѧԭ��3������ʹ�ø��������������Լ����\
������������������еĽϴ�ֵ��ȥ��Сֵ��Ȼ���ڼ�������������\
��֮��ѡȡ������Сֵ���������ֱ�������ͱ�������ȣ��ó������������Լ����

#include<iostream>
using namespace std;

//�����Լ��
int genxiangjiansun(int beijianshu, int jianshu)
{
	if (beijianshu == jianshu)//�ݹ��������
		return jianshu;

	if (beijianshu > jianshu) {
		int cha = beijianshu - jianshu;
		return genxiangjiansun(cha, jianshu);
	}
	else{
		int cha = jianshu - beijianshu;
		return genxiangjiansun(cha, beijianshu);
	}
}

//ŷ������㷨�����Լ��
int gcd(int p, int q)
{
	if (q == 0)//�ݹ��˳�����
		return  p;

	int r = p % q;
	return gcd(q, r);
}

int main()
{
	int a, b;
	cin >> a >> b;
	int max = genxiangjiansun(a, b);
	cout << a * b / gcd(a,b);

	return 0;
}