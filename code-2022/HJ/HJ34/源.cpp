//ͼƬ����
//Lily�Ͽ�ʱʹ����ĸ����ͼƬ��С������ѧϰӢ�ﵥ�ʣ�ÿ�ζ���Ҫ����ЩͼƬ���մ�С
//��ASCII��ֵ��С���������պá����Ҹ�Lily��æ��ͨ����������
//Lilyʹ�õ�ͼƬʹ���ַ�"A"��"Z"��"a"��"z"��"0"��"9"��ʾ��


#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using  namespace std;

int main()
{
	string line;
	getline(cin, line);
	vector<char> ch_vec;
	for (int i = 0; i < line.size(); i++) {
		ch_vec.push_back(line[i]);
	}
	sort(ch_vec.begin(), ch_vec.end());
	for (int i = 0; i < ch_vec.size(); i++) {
		cout<<ch_vec[i];
	}

	return 0;
}