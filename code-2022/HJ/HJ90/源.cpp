//IPV4��ַ������һ��32λ�޷�����������ʾ��һ���õ�ַ�ʽ����ʾ��
//�㽫IP��ַ�ֳ�4�����֣�ÿ������Ϊ8λ����ʾ��һ���޷�������
//��������Ų���Ҫ���֣�����10.137.17.1�������Ƿǳ���Ϥ��IP��ַ
//һ��IP��ַ����û�пո���֣���ΪҪ��ʾ��һ��32���֣���
//������Ҫ���ó������ж�IP�Ƿ�Ϸ���


#include<iostream>
#include<string>
#include<regex>
using namespace std;

int main() {
    string ip;
    regex pattern("((25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]\\d|\\d)\.){4}");//ƥ��0.0.0.0.-255.255.255.255.��������ʽ
    while (getline(cin, ip)) {
        ip += "."; //������ʽƥ����ĸ��㣬ip��ַ�����ټ�һ��
        if (regex_match(ip, pattern)) //ƥ�亯��
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
    return 0;
}
