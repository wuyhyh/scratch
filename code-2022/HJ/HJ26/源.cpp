//��дһ�����򣬽������ַ����е��ַ������¹�������
//���� 1 ��Ӣ����ĸ�� A �� Z ���У������ִ�Сд��
//�磬���룺 Type ����� epTy
//���� 2 ��ͬһ��Ӣ����ĸ�Ĵ�Сдͬʱ����ʱ����������˳�����С�
//�磬���룺 BabA ����� aABb
//���� 3 ����Ӣ����ĸ�������ַ�����ԭ����λ�á�
//�磬���룺 By ? e ����� Be ? y

//��ͬ���ʴ�Сд���ճ���˳����, ԭ����Դ�Сд���������

#include <iostream>
#include <string>
#include <vector>
#include<algorithm>
#include<utility>
using namespace std;

bool cmp(pair<char, int> a, pair<char, int> b)
{
    if (tolower(a.first) == tolower(b.first)){
        return a.second - b.second < 0;//��ʱ����
    }
    else {
        return tolower(a.first) - tolower(b.first) < 0;//����ĸ����
    }
}

string str_sort3(string str)
{
    vector<pair<char, int>> vec_pair;
    for (int i = 0; i < str.size(); i++) {//��ȡ��ĸ����������ĸ���ֹ���λ�ñ�ǳ�A
        if (isalpha(str[i])) {
            pair<char, int> temp = make_pair(str[i], i);
            vec_pair.push_back(temp);
            str[i] = 'A';
        }
    }

    sort(vec_pair.begin(), vec_pair.end(),cmp);

    for (int i = 0,j=0; i < str.size(); i++) {
        if (str[i] == 'A') {
            str[i] = vec_pair[j++].first;
        }
    }

    return str;
}

int main()
{
    string str;
    while (getline(cin,str)) {
        cout << str_sort3(str) << endl;
    }

    return 0;
}
