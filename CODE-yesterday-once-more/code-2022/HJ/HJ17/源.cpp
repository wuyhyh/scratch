//����һ��������㹤�ߣ� A��ʾ�����ƶ���D��ʾ�����ƶ���
//W��ʾ�����ƶ���S��ʾ�����ƶ����ӣ�0, 0���㿪ʼ�ƶ���
//�������ַ��������ȡһЩ���꣬�����������������������ļ����档

#include <iostream>
#include <string>
#include <vector>
#include<utility>
#include<sstream>
#include<cctype>
using namespace std;

bool is_legal(string str)//�ж��Ƿ��ǺϷ�����
{
	if (str.size() == 3) {
		if (str[0] == 'A' || str[0] == 'S' || str[0] == 'D' || str[0] == 'W') {
			if (isdigit(str[1]) && isdigit(str[2]))
				return true;
			else
				return false;
		}
		else {
			return false;
		}
	}
	else if (str.size() == 2) {
		if (str[0] == 'A' || str[0] == 'S' || str[0] == 'D' || str[0] == 'W' && isdigit(str[1])) {
			return true;
		}
		else
			return false;
	}
	else {
		return false;
	}
}

vector<string> coordinate_str(string str)//��һ�����ַ���ת��Ϊ����Ϸ��ַ���ѹ��vector
{
	for (int i = 0; i < str.size(); i++) {
		if (str[i] == ';') {
			str[i] = ' ';
		}
	}
	stringstream ss;
	ss << str;

	vector<string> vec_str;
	string s;
	while (ss >> s) {
		if(is_legal(s))
			vec_str.push_back(s);
	}
	return vec_str;
}

pair<int, int> str_trans_coord(string str) //�ѺϷ��ַ���ת��Ϊ����
{
	pair<int, int> coord;
	if (str[0] == 'A') {
		int dis = 0-stoi(str.substr(1));
		coord = make_pair(dis, 0);
	}
	else if (str[0] == 'D') {
		int dis = stoi(str.substr(1));
		coord = make_pair(dis, 0);
	}
	else if (str[0] == 'W') {
		int dis = stoi(str.substr(1));
		coord = make_pair(0, dis);
	}
	else {
		int dis = 0 - stoi(str.substr(1));
		coord = make_pair(0, dis);
	}

	return coord;
}

pair<int, int> compute(vector<string>& vec)
{
	vector < pair<int, int>> coor;
	for (int i = 0; i < vec.size(); i++) {
		coor.push_back(str_trans_coord(vec[i]));
	}
	pair<int, int> result = make_pair(0, 0);
	for (int i = 0; i < coor.size(); i++) {
		result.first += coor[i].first;
		result.second += coor[i].second;
	}
	return result;
}

int main() 
{
	string line;
	while (cin >> line){
		vector<string> vec_str = coordinate_str(line);
		pair<int, int> res = compute(vec_str);
		cout << res.first << ',' << res.second << endl;
	}

	return 0;
}