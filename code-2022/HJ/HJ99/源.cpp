//��������ָһ������ƽ����β�����ڸ����������Ȼ����
//���磺25 ^ 2 = 625��76 ^ 2 = 5776��9376 ^ 2 = 87909376��
//�����n(����n)���ڵ��������ĸ���

#include<string>
#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

bool is_self(int n)
{
	string num_str = to_string(n);
	int squre = n * n;
	string squre_str = to_string(squre);
	string post = squre_str.substr(squre_str.size()- num_str.size(), squre_str.size());
	
	if (post.compare(num_str)==0)//ע��ʹ���ַ����ȽϺ���compare()==0;
		return true;
	else
		return false;
}

int main()
{
	int n;
	while (cin >> n) {
		int count = 0;
		for (int i = 0; i <= n; i++) {
			if (is_self(i)) {
				count++;
			}
		}
		cout << count << endl;
	}

	return 0;
}
