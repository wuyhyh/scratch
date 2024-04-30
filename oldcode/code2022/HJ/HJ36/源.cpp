//有一种技巧可以对数据进行加密，它使用一个单词作为它的密匙。
//下面是它的工作原理：首先，选择一个单词作为密匙，如TRAILBLAZERS。
//如果单词中包含有重复的字母，只保留第1个，将所得结果作为新字母表开头，
//并将新建立的字母表中未出现的字母按照正常字母表顺序加入新字母表。如下所示：
//A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
//T R A I L B Z E S C D F G H J K M N O P Q U V W X Y
//(实际需建立小写字母的字母表，此字母表仅为方便演示）
//上面其他用字母表中剩余的字母填充完整。
//在对信息进行加密时，信息中的每个字母被固定于顶上那行，
//并用下面那行的对应字母一一取代原文的字母(字母字符的大小写状态应该保留)。
//因此，使用这个密匙， Attack AT DAWN(黎明时攻击)就会被加密为Tpptad TP ITVH。

#include<iostream>
#include<string>
#include<cctype>
#include<vector>
#include<utility>
#include<algorithm>
#include<set>
using namespace std;

string Alpha_t = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
string alpha_t = "abcdefghijklmnopqrstuvwxyz";

string unify_key(string str)
{
	for (int i = 0; i < str.size(); i++) {
		str[i] = tolower(str[i]);
	}
	
	string res;
	int is_repeat[26] = { 0 };
	for (int i = 0; i < str.size(); i++) {
		if (is_repeat[str[i] - 'a'] == 0) {
			res += str[i];
			is_repeat[str[i] - 'a'] = 1;
		}
	}

	return res;
}

string generate_new_t(string key) 
{
	string pre = unify_key(key);//全是小写字母
	int is_exsit[26] = { 0 };
	for (int i = 0; i < pre.size(); i++) {
		is_exsit[pre[i] - 'a'] = 1;
	}
	string post;
	for (int i = 0; i < alpha_t.size(); i++) {
		if (is_exsit[alpha_t[i] - 'a'] == 0) {
			post += alpha_t[i];
		}
	}

	return pre + post;
}

string encode(string key, string str)
{
	string lower_key_t = generate_new_t(key);
	string upper_key_t;
	for (int i = 0; i < lower_key_t.size(); i++) {
		upper_key_t += toupper(lower_key_t[i]);
	}

	string res;
	for (int i = 0; i < str.size(); i++) {
		if (isupper(str[i])) {
			res += upper_key_t[str[i] - 'A'];
		}
		else {
			res += lower_key_t[str[i] - 'a'];
		}
	}

	return res;
}

int main()
{
	string str;
	string key;
	while (cin >> key>>str) {
		cout << encode(key, str) << endl;
	}

	return 0;
}
