//密码按如下规则进行计分，并根据不同的得分为密码进行安全等级划分。

#include<iostream>
#include<string>
#include<cctype>
using namespace std;

int score(string str)
{
	int score = 0;
	char symbol_tab[20] = "!\"#$%&'()*+,-./";

	//referee1
	if (str.size() <= 4)
		score += 5;
	else if (str.size() <= 7)
		score += 10;
	else
		score += 25;

	//referee2
	string temp = str;
	string upper;
	for (int i = 0; i < temp.size(); i++) {
		if (isalpha(temp[i])) {
			if (isupper(temp[i])) {
				upper += temp[i];
				temp[i] = ' ';
			}
		}
	}
	string lower;
	for (int i = 0; i < temp.size(); i++) {
		if (isalpha(temp[i])) {
			lower += temp[i];
		}
	}
	if ((!upper.empty() && lower.empty()) || (upper.empty() && !lower.empty())) {
		score += 10;
	}
	else if ((!upper.empty() && !lower.empty())) {
		score += 20;
	}
	else {
		score += 0;
	}

	//referee3
	string num;
	for (int i = 0; i < str.size(); i++) {
		if (isdigit(str[i]))
			num += str[i];
	}
	if (num.size() == 1) {
		score += 10;
	}
	else if (num.size() == 0) {
		score += 0;
	}
	else {
		score += 20;
	}

	//referee4
	string symbol;
	for (int i = 0; i < str.size(); i++) {
		if (isalnum(str[i]))
			str[i] = ' ';
	}
	for (int i = 0; i < str.size(); i++) {
		if (str[i] != ' ')
			symbol += '#';
	}
	if (symbol.empty()) {
		score += 0;
	}
	else if (symbol.size() == 1) {
		score += 10;
	}
	else {
		score += 25;
	}

	//referee5
	int a = 0;
	if ((!upper.empty() || !lower.empty()) && !num.empty()) {
		a = 2;
		if (!symbol.empty()) {
			a++;
			if (!upper.empty() && !lower.empty()) {
				a += 2;
			}
		}
	}

	return score + a;
}

string judge(int score)
{
	if (score >= 90)
		return "VERY_SECURE";
	else if (score >= 80)
		return "SECURE";
	else if (score >= 70)
		return "VERY_STRONG";
	else if (score >= 60)
		return "STRONG";
	else if (score >= 50)
		return "AVERAGE";
	else if (score >= 25)
		return "WEAK";
	else
		return "VERY_WEAK";
}

int main()
{
	string line;
	while (getline(cin, line)) {
		int s = score(line);
		cout << judge(s) << endl;
	}

	return 0;
}

