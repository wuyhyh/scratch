//原理：ip地址的每段可以看成是一个0 - 255的整数，
//把每段拆分成一个二进制形式组合起来，然后把这个二进制数转变成一个长整数。

#include<iostream>
#include<sstream>
#include<vector>
#include<bitset>
#include<cctype>
#include<cmath>
using namespace std;

string ip_to_32bits(string ip)
{
	for (int i = 0; i < ip.size(); i++) {
		if (ip[i] == '.') {
			ip[i] = ' ';
		}
	}
	stringstream ss;
	ss << ip;
	vector<string> ip_part;
	string str;
	while (ss >> str) {
		ip_part.push_back(str);
	}
	string res;
	for (int i = 0; i < 4; i++) {
		stringstream int_str;
		int_str << ip_part[i];
		int a;
		int_str >> a;
		bitset<8> s(a);
		stringstream bits;
		bits << s;
		string b;
		bits >> b;
		res += b;
	}

	return res;
}

double to_int(string binary_str)
{
	double res = 0;
	for (int i = 0; i <= binary_str.size()-1; i++) {
		if(binary_str[i] != '0')
			res += pow(2, binary_str.size() - 1-i);
	}
	return res;
}

string to_ip(string binary_str)
{
	int res = 0;
	for (int i = 0; i <= binary_str.size() - 1; i++) {
		if (binary_str[i] != '0')
			res += pow(2, binary_str.size() - 1 - i);
	}

	return to_string(res);
}

string int_to_ip(long long integer)
{
	bitset<32> bits(integer);
	stringstream ss;
	ss << bits;
	string str_bits;
	ss >> str_bits;
	string num_str[4];
	num_str[0] = str_bits.substr(0, 8);
	num_str[1] = str_bits.substr(8, 8);
	num_str[2] = str_bits.substr(16, 8);
	num_str[3] = str_bits.substr(24, 8);
	string ip[4];
	for (int i = 0; i < 4; i++) {
		ip[i] = to_ip(num_str[i]);
	}

	return ip[0] + '.' + ip[1] + '.' + ip[2] + '.' + ip[3];
}

bool is_ip(string str)
{
	for (int i = 0; i < str.size(); i++) {
		if (!isdigit(str[i]))
			return true;
	}
	return false;
}

int main()
{
	string ip_or_int;
	while (cin >> ip_or_int) {
		if (is_ip(ip_or_int)) {
			double res = to_int(ip_to_32bits(ip_or_int));
			printf("%.0f\n", res);
		}
		else {
			stringstream ss;
			ss << ip_or_int;
			long long integer;
			ss >> integer;
			cout << int_to_ip(integer) << endl;
		}
	}
	
	return 0;
}