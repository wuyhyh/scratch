//һ�� DNA ������ A / C / G / T �ĸ���ĸ�����������ɡ�
//G �� C �ı���������Ϊ GC - Ratio ��
//�������� G �� C ������ĸ���ܵĳ��ִ��������ܵ���ĸ��Ŀ��Ҳ�������г��ȣ���
//�ڻ��򹤳��У���������ǳ���Ҫ����Ϊ�ߵ� GC - Ratio �����ǻ������ʼ�㡣
//����һ���ܳ��� DNA ���У��Լ��޶����Ӵ����� N ��
//������о���Ա�ڸ����� DNA �����д��������ҳ� GC - Ratio ����ҳ���Ϊ N �ĵ�һ���Ӵ���
//DNA����Ϊ ACGT ���Ӵ��� : ACG, CG, CGT �ȵȣ�����û�� AGT �� CT �ȵ�

//�������ڵ�˼��
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<utility>
using namespace std;

int count_GC(string str)
{
	int GC = 0;
	for (int i = 0; i < str.size(); i++) {
		if (str[i] == 'G' || str[i] == 'C') {
			GC++;
		}
	}
	return GC;
}

string max_GC_ratio(string str,int len)
{
	if (str.size() == len) {
		return str;
	}

	int max_GC = 0;
	vector<int> gc;
	for (int i = 0; i < str.size() - len; i++) {
		int temp = count_GC(str.substr(i, len));
		gc.push_back(temp);
		max_GC = (max_GC > temp) ? max_GC : temp;
	}

	for (int i = 0; i < gc.size(); i++) {
		if (gc[i] == max_GC) {
			return str.substr(i, len);
		}
	}
	return " ";
}

int main()
{
	string str;
	while (cin >> str) {
		int len;
		cin >> len;
		cout << max_GC_ratio(str, len) << endl;
	}

	return 0;
}
