//开发一个坐标计算工具， A表示向左移动，D表示向右移动，
//W表示向上移动，S表示向下移动。从（0, 0）点开始移动，
//从输入字符串里面读取一些坐标，并将最终输入结果输出到输出文件里面。

#include <iostream>
#include <string>
#include <vector>
#include<utility>
#include<sstream>
#include<cctype>
using namespace std;

bool is_legal(string str)//判断是否是合法坐标
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

vector<string> coordinate_str(string str)//把一个长字符串转化为多个合法字符串压入vector
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

pair<int, int> str_trans_coord(string str) //把合法字符串转化为向量
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