//���ݱ��¼����������index����ֵvalue��int��Χ������������
//��Ա�������ͬ�ļ�¼���кϲ���������ͬ��������ֵ����������㣬�������indexֵ������������

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
		if (it != my_map.end()) {    //������ڣ��Լ���ͬ�ĵ�Ԫ��ֵ���ֽ�����ͣ�
			my_map[index] = it->second + value;
		}
		else {        //��������������µļ�ֵ��
			my_map[index] = value;
		}
	}

	for (it = my_map.begin(); it != my_map.end(); it++) {
		cout << it->first << ' ' << it->second << endl;
	}

	return 0;
}