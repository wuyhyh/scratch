//编写一个程序，将输入字符串中的字符按如下规则排序。
//规则 1 ：英文字母从 A 到 Z 排列，不区分大小写。
//如，输入： Type 输出： epTy
//规则 2 ：同一个英文字母的大小写同时存在时，按照输入顺序排列。
//如，输入： BabA 输出： aABb
//规则 3 ：非英文字母的其它字符保持原来的位置。
//如，输入： By ? e 输出： Be ? y

//相同单词大小写按照出现顺序来, 原理忽略大小写排序就行了

#include <iostream>
#include <string>
#include <vector>
#include<algorithm>
#include<utility>
using namespace std;

bool cmp(pair<char, int> a, pair<char, int> b)
{
    if (tolower(a.first) == tolower(b.first)){
        return a.second - b.second < 0;//按时间排
    }
    else {
        return tolower(a.first) - tolower(b.first) < 0;//按字母表牌
    }
}

string str_sort3(string str)
{
    vector<pair<char, int>> vec_pair;
    for (int i = 0; i < str.size(); i++) {//抽取字母并把所有字母出现过的位置标记成A
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
