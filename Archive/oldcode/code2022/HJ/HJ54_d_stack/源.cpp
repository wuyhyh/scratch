#include<iostream>
#include<stack>
#include<string>
#include<cctype>
using namespace std;

void compute(stack<int>& st1, stack<char>& st2) { //����ջ�����������ջ������Ԫ�ؽ�������
    int b = st1.top();
    st1.pop();
    int a = st1.top();
    st1.pop();
    char op = st2.top(); //ջ�������
    st2.pop();
    if (op == '+') a = a + b; //��
    else if (op == '-') a = a - b; //��
    else if (op == '*') a = a * b; //��
    else if (op == '/') a = a / b; //��
    st1.push(a);
}

bool priority(char m, char n) { //�Ƚ���������ȼ�
    if (m == '(') //�������ȼ����
        return false;
    else if ((m == '+' || m == '-') && (n == '*' || n == '/')) //�Ӽ���С�ڳ˳���
        return false;
    return true;
}

int main() {
    string s;
    while (cin >> s) {
        stack<int> st1; //��¼��������
        stack<char> st2; //��¼�����
        st2.push('('); //��������ʽ�������
        s += ')';

        bool flag = false;
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '(') //����������Ŷ��������ջ����(
                st2.push('(');
            else if (s[i] == ')') { //����������
                while (st2.top() != '(') { //������ʼ����ֱ������������
                    compute(st1, st2);
                }
                st2.pop(); //����������
            }
            else if (flag) { //�����
                while (priority(st2.top(), s[i])) { //�Ƚ��������ȼ�,���ջ�е����ȼ����ߣ��ͽ��м���
                    compute(st1, st2); //����ֱ�Ӽ���
                }
                st2.push(s[i]); //��Ҫ���ֽ׶μ���ջ�еȴ�����
                flag = false;
            }
            else { //����
                int j = i; //��¼��ʼ
                if (s[j] == '-' || s[j] == '+') //������
                    i++;
                while (isdigit(s[i])) {
                    i++;
                }
                string temp = s.substr(j, i - j);
                st1.push(stoi(temp)); //��ȡ���ֲ��֣�ת����

                i--;//������һ�����˵Ĳ���

                flag = true; //���ֽ�������һ��flagΪtrue�����������
            }
        }

        cout << st1.top() << endl; //���
    }

    return 0;
}
