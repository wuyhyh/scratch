//��һ��int�������ֶ�Ӧ�Ķ�����������1�������������
//����3�Ķ�����Ϊ00000011���������2��1

#include<iostream>
#include<bitset>
#include<string>
#include<sstream>
using namespace std;

string to32bits_str(int n)
{
	bitset<32> bs(n);
	stringstream ss;
	ss << bs;
	string str;
	ss >> str;
	return str;
}

int continueous_ones(string bit_str)
{
	int max_len = 0;
	string ones;
	for (int i = 0; i < bit_str.size(); i++) {
		if (bit_str[i] == '1') {
			ones += '1';
			max_len = (ones.size() > max_len) ? ones.size() : max_len;
		}
		else {
			ones.clear();
		}
	}

	return max_len;
}

int main()
{
	int n;
	while (cin >> n) {
		string bit = to32bits_str(n);
		cout << continueous_ones(bit) << endl;
	}

	return 0;
}
