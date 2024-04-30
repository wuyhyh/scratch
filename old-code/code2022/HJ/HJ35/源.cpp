//���ξ�������1��ʼ����Ȼ���������гɵ�һ�������������Ρ�
//
//���磬������5ʱ��Ӧ�������������Ϊ��
//
//1 3 6 10 15
//2 5 9 14
//4 8 13
//7 12
//11


#include <iostream>
#include <vector>
using namespace std;

vector<int> renew_row(vector<int> vec_row)
{
	for (int i = 1; i < vec_row.size(); i++) {
		vec_row[i] = vec_row[i] - 1;
	}
	vec_row.erase(vec_row.begin());
	return vec_row;
}

void print_row(vector<int> vec_row)
{
	for (int i = 0; i < vec_row.size(); i++)
		cout << vec_row[i] << ' ';
	cout << endl;
}

int main() 
{
	//���ݹ��ɣ���һ��Ԫ�����ұ���(N^2+N)/2,�ڶ����ǵ�һ��Ԫ�����μ���1����ȥ������ߵ�Ԫ��
	int N;
	cin >> N;
	vector<int> first_row;
	for (int i = 1; i <= N; i++) {
		first_row.push_back((i * i + i) / 2);
	}

	for (int row = 1; row <= N; row++) {
		print_row(first_row);
		first_row = renew_row(first_row);
	}

	return 0;
}