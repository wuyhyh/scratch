//��һ�ּ��ɿ��Զ����ݽ��м��ܣ���ʹ��һ��������Ϊ�����ܳס�
//���������Ĺ���ԭ�����ȣ�ѡ��һ��������Ϊ�ܳף���TRAILBLAZERS��
//��������а������ظ�����ĸ��ֻ������1���������ý����Ϊ����ĸ��ͷ��
//�����½�������ĸ����δ���ֵ���ĸ����������ĸ��˳���������ĸ��������ʾ��
//A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
//T R A I L B Z E S C D F G H J K M N O P Q U V W X Y
//(ʵ���轨��Сд��ĸ����ĸ������ĸ���Ϊ������ʾ��
//������������ĸ����ʣ�����ĸ���������
//�ڶ���Ϣ���м���ʱ����Ϣ�е�ÿ����ĸ���̶��ڶ������У�
//�����������еĶ�Ӧ��ĸһһȡ��ԭ�ĵ���ĸ(��ĸ�ַ��Ĵ�Сд״̬Ӧ�ñ���)��
//��ˣ�ʹ������ܳף� Attack AT DAWN(����ʱ����)�ͻᱻ����ΪTpptad TP ITVH��

#include<iostream>
#include<string>
#include<cctype>
#include<vector>
#include<utility>
#include<algorithm>
#include<set>
using namespace std;

string Alpha_t = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
string alpha_t = "abcdefghijklmnopqrstuvwxyz";

string unify_key(string str)
{
	for (int i = 0; i < str.size(); i++) {
		str[i] = tolower(str[i]);
	}
	
	string res;
	int is_repeat[26] = { 0 };
	for (int i = 0; i < str.size(); i++) {
		if (is_repeat[str[i] - 'a'] == 0) {
			res += str[i];
			is_repeat[str[i] - 'a'] = 1;
		}
	}

	return res;
}

string generate_new_t(string key) 
{
	string pre = unify_key(key);//ȫ��Сд��ĸ
	int is_exsit[26] = { 0 };
	for (int i = 0; i < pre.size(); i++) {
		is_exsit[pre[i] - 'a'] = 1;
	}
	string post;
	for (int i = 0; i < alpha_t.size(); i++) {
		if (is_exsit[alpha_t[i] - 'a'] == 0) {
			post += alpha_t[i];
		}
	}

	return pre + post;
}

string encode(string key, string str)
{
	string lower_key_t = generate_new_t(key);
	string upper_key_t;
	for (int i = 0; i < lower_key_t.size(); i++) {
		upper_key_t += toupper(lower_key_t[i]);
	}

	string res;
	for (int i = 0; i < str.size(); i++) {
		if (isupper(str[i])) {
			res += upper_key_t[str[i] - 'A'];
		}
		else {
			res += lower_key_t[str[i] - 'a'];
		}
	}

	return res;
}

int main()
{
	string str;
	string key;
	while (cin >> key>>str) {
		cout << encode(key, str) << endl;
	}

	return 0;
}
