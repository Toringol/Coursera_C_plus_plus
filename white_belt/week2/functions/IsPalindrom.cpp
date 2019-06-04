/*
* Напишите функцию, которая
* - называется IsPalindrom
* - возвращает bool
* - принимает параметр типа string и возвращает, является ли переданная строка палиндромом
*
* Палиндром - это слово или фраза, которые одинаково читаются слева направо и справа налево. 
* Пустая строка является палиндромом.
*/

#include <iostream>
#include <string>

bool IsPalindrom(std::string str) {
	for (int i = 0; i < str.size() / 2; ++i) {
		if (str[i] != str[str.size() - i - 1])
			return false;
	}
	return true;
}

int main() {
	std::string str;
	std::cin >> str;

	std::cout << IsPalindrom(str) << std::endl;

	return 0;
}
