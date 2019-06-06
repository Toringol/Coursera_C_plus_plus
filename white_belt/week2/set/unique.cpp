/*
* Дан набор строк. Найдите количество уникальных строк в этом наборе.
*
* Формат ввода
* Сначала вводится количество строк N, затем — сами N строк, разделённые пробелом. 
* Все строки состоят лишь из латинских букв, цифр и символов подчёркивания.
* 
* Формат вывода
* Выведите единственное целое число — количество уникальных строк в данном наборе.
*/

#include <iostream>
#include <set>
#include <string>

int main() {
	std::set<std::string> strSet;

	size_t strNumber;
	std::cin >> strNumber;
	
	for (size_t i = 0; i < strNumber; ++i) {
		std::string str;
		std::cin >> str;
		strSet.insert(str);
	}

	std::cout << strSet.size() << std::endl;

	return 0;
}
