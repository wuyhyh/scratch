#include<iostream>
#include<stack>
#include<string>
#include<cctype>
using namespace std;

void compute(stack<int>& st1, stack<char>& st2) { //根据栈顶运算符弹出栈顶两个元素进行运算
    int b = st1.top();
    st1.pop();
    int a = st1.top();
    st1.pop();
    char op = st2.top(); //栈顶运算符
    st2.pop();
    if (op == '+') a = a + b; //加
    else if (op == '-') a = a - b; //减
    else if (op == '*') a = a * b; //乘
    else if (op == '/') a = a / b; //除
    st1.push(a);
}

bool priority(char m, char n) { //比较运算符优先级
    if (m == '(') //括号优先级最高
        return false;
    else if ((m == '+' || m == '-') && (n == '*' || n == '/')) //加减法小于乘除法
        return false;
    return true;
}

int main() {
    string s;
    while (cin >> s) {
        stack<int> st1; //记录运算数字
        stack<char> st2; //记录运算符
        st2.push('('); //整个运算式添加括号
        s += ')';

        bool flag = false;
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '(') //如果是左括号都在运算符栈加入(
                st2.push('(');
            else if (s[i] == ')') { //遇到右括号
                while (st2.top() != '(') { //弹出开始计算直到遇到左括号
                    compute(st1, st2);
                }
                st2.pop(); //弹出左括号
            }
            else if (flag) { //运算符
                while (priority(st2.top(), s[i])) { //比较运算优先级,如果栈中的优先级更高，就进行计算
                    compute(st1, st2); //可以直接计算
                }
                st2.push(s[i]); //需要将现阶段加入栈中等待运算
                flag = false;
            }
            else { //数字
                int j = i; //记录起始
                if (s[j] == '-' || s[j] == '+') //正负号
                    i++;
                while (isdigit(s[i])) {
                    i++;
                }
                string temp = s.substr(j, i - j);
                st1.push(stoi(temp)); //截取数字部分，转数字

                i--;//这里有一个回退的操作

                flag = true; //数字结束，下一次flag为true就是运算符了
            }
        }

        cout << st1.top() << endl; //输出
    }

    return 0;
}
