//IPV4地址可以用一个32位无符号整数来表示，一般用点分方式来显示，
//点将IP地址分成4个部分，每个部分为8位，表示成一个无符号整数
//（因此正号不需要出现），如10.137.17.1，是我们非常熟悉的IP地址
//一个IP地址串中没有空格出现（因为要表示成一个32数字）。
//现在需要你用程序来判断IP是否合法。


#include<iostream>
#include<string>
#include<regex>
using namespace std;

int main() {
    string ip;
    regex pattern("((25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]\\d|\\d)\.){4}");//匹配0.0.0.0.-255.255.255.255.的正则表达式
    while (getline(cin, ip)) {
        ip += "."; //正则表达式匹配的四个点，ip地址后面再加一个
        if (regex_match(ip, pattern)) //匹配函数
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
    return 0;
}
