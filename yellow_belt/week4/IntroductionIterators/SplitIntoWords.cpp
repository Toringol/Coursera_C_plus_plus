/*
* Напишите функцию SplitIntoWords, разбивающую строку на слова по пробелам.
* vector<string> SplitIntoWords(const string& s);
* Гарантируется, что:
*
* - строка непуста;
* - строка состоит лишь из латинских букв и пробелов;
* - первый и последний символы строки не являются пробелами;
* - строка не содержит двух пробелов подряд.
* Подсказка
* Рекомендуется следующий способ решения задачи:
*
* - искать очередной пробел с помощью алгоритма find;
* - создавать очередное слово с помощью конструктора строки по двум итераторам.
*
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <string>

std::vector<std::string> SplitIntoWords(const std::string& s) {
	std::vector<std::string> result;
	auto startIt = std::begin(s);
	while (true) {
		auto endIt = std::find_if(startIt, std::end(s), [](const char& ch) {
			return (ch == ' ');
		});
		result.push_back({ startIt, endIt });
		if (endIt == std::end(s))
			break;
		++endIt;
		startIt = endIt;
	}
	return result;
}

int main() {
	std::string s = "C Cpp Java Python";

	std::vector<std::string> words = SplitIntoWords(s);
	std::cout << words.size() << " ";
	for (auto it = begin(words); it != end(words); ++it) {
		if (it != begin(words)) {
			std::cout << "/";
		}
		std::cout << *it;
	}
	std::cout << std::endl;

	return 0;
}
