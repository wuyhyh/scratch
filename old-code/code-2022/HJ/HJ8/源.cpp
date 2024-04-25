//数据表记录包含表索引index和数值value（int范围的正整数），
//请对表索引相同的记录进行合并，即将相同索引的数值进行求和运算，输出按照index值升序进行输出。

#include<iostream>
#include<map>
using namespace std;

int main() 
{
	int count;
	cin >> count;
	map<int, int> my_map;
	map<int, int>::iterator it;

	for (int i = 0; i < count; i++) {
		int index;
		int value;
		cin >> index >> value;

		it = my_map.find(index);
		if (it != my_map.end()) {    //如果存在，对键相同的单元的值部分进行求和；
			my_map[index] = it->second + value;
		}
		else {        //如果不存在生成新的键值对
			my_map[index] = value;
		}
	}

	for (it = my_map.begin(); it != my_map.end(); it++) {
		cout << it->first << ' ' << it->second << endl;
	}

	return 0;
}