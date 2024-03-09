#include<string>
#include<vector>
#include<iostream>
#include<algorithm>
using namespace std;

bool is_symetry(string str)
{
	if (str.size() == 1)//�����ַ�����Ϊ�Գ�
		return 0;

	int cut = str.size() / 2;
	if (str.size() % 2 == 0) {//ż��
		string subA = str.substr(0, cut);
		string subB = str.substr(cut, cut);
		reverse(subB.begin(), subB.end());
		if (subA.compare(subB)==0) {
			return true;
		}
		else
			return false;
	}
	else {//����
		string subA = str.substr(0, cut);
		string subB = str.substr(cut+1, cut);
		reverse(subB.begin(), subB.end());
		if (subA.compare(subB) == 0) {
			return true;
		}
		else
			return false;
	}
}

int  main()
{
	string str;
	while (cin >> str) {
		int max_len = 0;
		for (int i = 0; i < str.size(); i++) {
			for (int j = str.size()-i; j > 0; j--) {
				string temp = str.substr(i, j);
				if (is_symetry(temp)) {
					max_len = (temp.size() > max_len) ? temp.size() : max_len;
				}
			}
		}
		cout << max_len << endl;
	}

	return 0;
}