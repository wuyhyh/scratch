//��Ԫ�����ͣ��ҹ��Ŵ���ѧ�������ڡ��㾭��һ��������ˡ��ټ����⡱��
//����һֵǮ�壬��ĸһֵǮ����������ֵǮһ����Ǯ��ټ����ʼ��̡���ĸ�����������Σ�
//��Ҫ�����ӡ�����л�һ��Ԫ��һ��ֻ���ķ�ʽ��


#include<iostream>
#include<vector>
using namespace std;

int main() 
{
	vector<int> ji;
	for (int cock = 0; cock < 20; cock++) {
		for (int hen = 0; hen < 33; hen++) {
			for (int chick = 0; chick < 99; chick += 3) {
				if (cock + hen + chick == 100 && (5 * cock + 3 * hen + chick/3==100)) {
					cout << cock << ' ' << hen << ' ' << chick << endl;
				}
			}
		}
	}

	return 0;
}