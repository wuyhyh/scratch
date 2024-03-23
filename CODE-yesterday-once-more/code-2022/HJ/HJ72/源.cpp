//公元五世纪，我国古代数学家张丘建在《算经》一书中提出了“百鸡问题”：
//鸡翁一值钱五，鸡母一值钱三，鸡雏三值钱一。百钱买百鸡，问鸡翁、鸡母、鸡雏各几何？
//现要求你打印出所有花一百元买一百只鸡的方式。


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