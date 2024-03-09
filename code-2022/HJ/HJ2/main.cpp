//计算某字符串中指定字符的出现次数，不区分大小写

#include<iostream>
#include<string>

int main()
{
	std::string str;
	std::getline(std::cin, str);
	int ch = tolower(getchar());

	uint16_t count = 0;
	for (auto i : str) {
		if (tolower(i) == ch)
			count++;
	}

	std::cout << count << std::endl;

	return 0;
}