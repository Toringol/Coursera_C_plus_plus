/*
* Напишите функцию, которая
* - называется PalindromFilter
* - возвращает vector<string>
* - принимает vector<string> words и int minLength и возвращает все строки из вектора words, 
*   которые являются палиндромами и имеют длину не меньше minLength
* Входной вектор содержит не более 100 строк, длина каждой строки не больше 100 символов.
*/

#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> PalindromFilter(std::vector<std::string> words, int minLength) {
	std::vector<std::string> result;
	bool flag = true;
	for (auto str : words) {
		if (str.size() >= minLength) {
			for (size_t i = 0; i < str.size() / 2; ++i) {
				if (str[i] != str[str.size() - i - 1]) {
					flag = false;
					break;
				}
			}
			if (flag)
				result.push_back(str);
			flag = true;
		}
	}
	return result;
}

int main() {
	std::vector<std::string> test;
	int vectorSize, minLength;
	std::cin >> vectorSize >> minLength;

	std::string tempStr;
	for (size_t i = 0; i < vectorSize; ++i) {
		std::cin >> tempStr;
		test.push_back(tempStr);
	}
	
	std::vector<std::string> result = PalindromFilter(test, minLength);
	
	for (auto str : result)
		std::cout << str << " ";

	return 0;
}
