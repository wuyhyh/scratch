//Catcher��MCA�����鱨Ա��������ʱ���ֵй�����һЩ�ԳƵ��������ͨ�ţ�
//��������ЩABBA��ABA��A��123321��
//����������ʱ���ڿ�ʼ�����ʱ����һЩ�޹ص��ַ��Է�ֹ����ƽ⡣
//����������б仯 ABBA->12ABBA, ABA->ABAKK, 123321->51233214����
//��Ϊ�ػ�Ĵ�̫���ˣ����Ҵ��ڶ��ֿ��ܵ������abaaab�ɿ�����aba, ��baaab�ļ�����ʽ��
//Cathcer�Ĺ�����ʵ����̫���ˣ���ֻ������Ը���������
//���ܰ�Catcher�ҳ������Ч���봮��
//
//������ַ����ĳ���

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

bool is_symetry(string str)
{
	int len = str.size();
	if (len % 2 == 0) {//����Ϊż��
		int cut = len / 2;
		string subA = str.substr(0, cut);
		string subB = str.substr(cut, cut);
		reverse(subB.begin(), subB.end());
		if (subA.compare(subB) == 0) {
			return true;
		}
		else {
			return false;
		}
	}
	else {//����Ϊ����
		int cut = len / 2;
		string subA = str.substr(0, cut);
		string subB = str.substr(cut+1, cut);
		reverse(subB.begin(), subB.end());
		if (subA.compare(subB) == 0) {
			return true;
		}
		else {
			return false;
		}
	}
}

//�����㷨��ʱ
int main()
{
	string str;
	cin >> str;
	int longest = 0;
	for (int pos = 0; pos < str.size(); pos++) {
		for (int len = str.size(); len >= 2; len--) {
			string sub = str.substr(pos, len);
			if (is_symetry(sub)) {
				longest = (sub.size() > longest) ? sub.size() : longest;
			}
		}
	}
	cout << longest << endl;

	return 0;
}