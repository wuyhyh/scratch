//������Ǳ���

#include <iostream>
using namespace std;

//������ǹ���                                    �к�    ��һ��ż���ڸ��еڼ���
//                    1                           1             -1
//                1   1   1                       2             -1
//            1   2   3   2   1                   3              2
//         1  3   6   7   6   3   1               4              3
//      1  4  10  16  19  16  10  4  1            5              2
//   1  5  15 30  45  51  45  30  15 5  1         6              4
//
//  �׸�ż���ڸ��еڼ����Ĺ��ɣ� -1 -1 ��2 3 2 4����������2 3 2 4��

//����2342����������

int sanjiao(int line)
{
	if (line < 3)
		return -1;
	else if ((line - 2) % 4 == 1)
		return 2;
	else if ((line - 2) % 4 == 2)
		return 3;
	else if ((line - 2) % 4 == 3)
		return 2;
	else//�����else,��������·��ʧ�ܵ����
		return 4;
}

int main()
{
	int line;
	cin >> line;
	cout << sanjiao(line) << endl;

	return 0;
}

