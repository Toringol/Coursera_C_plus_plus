/*
* Условие
* В стандартном потоке дана одна строка, состоящая из числа N и следующих за ним N строк S. 
* Между собой число и строки разделены пробелом.
*
* Отсортируйте строки S в лексикографическом порядке по возрастанию, игнорируя регистр букв, 
* и выведите их в стандартный поток вывода.
*
* Ограничения
* 0 <= N <= 1000
* 1 <= |S| <= 15
* Каждая строка S[i] может состоять из следующих символов: [0-9,a-z,A-Z]
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

bool compareFunc(std::string firstStr, std::string secondStr) {
	if (firstStr.size() == secondStr.size()) {
		for (size_t i = 0; i < firstStr.size(); ++i) {
			if (tolower(firstStr[i]) == tolower(secondStr[i]))
				continue;
			else {
				return (tolower(firstStr[i]) < tolower(secondStr[i]));
			}
		}
		return false;
	}
	else {
		return (firstStr.size() < secondStr.size());
	}
}

int main() {
	size_t masSize;
	std::cin >> masSize;
	std::vector<std::string> mas(masSize);

	for (auto& elem : mas) {
		std::cin >> elem;
	}

	std::sort(std::begin(mas), std::end(mas), compareFunc);

	for (const auto& elem : mas) {
		std::cout << elem << " ";
	}
	std::cout << std::endl;

	return 0;
}
