//ʵ��ɾ���ַ����г��ִ������ٵ��ַ��������ִ������ٵ��ַ��ж������ѳ��ִ������ٵ��ַ���ɾ����
//���ɾ����Щ���ʺ���ַ������ַ����������ַ�����ԭ����˳��

#include<iostream>
#include<map>
#include<vector>
#include<algorithm>
using namespace std;

string delete_str(string str)
{
	int len = str.size();
	int arr_count[26] = { 0 };
	for (int i = 0; i < len; i++) {//ͳ�Ƹ���Сд��ĸ���ֵĴ���
		arr_count[str[i] - 'a'] += 1;
	}
	int min = len;
	for (int i = 0; i < 26; i++) {//�ҳ��ַ�������С�����ı�׼
		if (arr_count[i] <= min&&arr_count[i]!=0) {
			min = arr_count[i];
		}
	}
	//�ؽ��ַ���
	string str_del;
	for (int i = 0; i < len; i++) {
		if (arr_count[str[i]-'a'] > min) {
			str_del += str[i];
		}
	}

	return str_del;
}

int main()
{
	string str;
	cin >> str;
	cout << delete_str(str) << endl;

	return 0;
}