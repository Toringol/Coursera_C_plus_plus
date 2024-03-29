/*
* Часть 1. Группировка по символу
* Напишите функцию FindStartsWith:
*
* - принимающую отсортированный набор строк в виде итераторов range_begin, range_end и один символ prefix;
* - возвращающую диапазон строк, начинающихся с символа prefix, в виде пары итераторов.
* template <typename RandomIt>
* pair<RandomIt, RandomIt> FindStartsWith(
*     RandomIt range_begin, RandomIt range_end,
*     char prefix);
* Если итоговый диапазон пуст, его границы должны указывать на то место в контейнере, 
* куда можно без нарушения порядка сортировки вставить любую строку, 
* начинающуюся с символа prefix (подобно алгоритму equal_range). 
* Гарантируется, что строки состоят лишь из строчных латинских букв и символ prefix также является строчной латинской буквой.
*
* Поиск должен осуществляться за логарифмическую сложность — например, с помощью двоичного поиска.
* Подсказка
* К символам (char) можно прибавлять или вычитать числа, 
* получая таким образом следующие или предыдущие буквы в алфавитном порядке. 
* Например, для строки s выражение --s[0] заменит её первую букву на предыдущую.
*
* Обратите внимание, что выражение 'a' + 1 имеет тип int и поэтому может понадобиться привести его к типу char с помощью static_cast.
* Часть 2. Группировка по префиксу
* Напишите более универсальный вариант функции FindStartsWith, 
* принимающий в качестве префикса произвольную строку, состоящую из строчных латинских букв.
*/

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>

template <typename RandomIt>
std::pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, const std::string& prefix) {
	std::string target = prefix;
	RandomIt leftBound = std::lower_bound(range_begin, range_end, target);
	++target[target.size() - 1];
	RandomIt rightBound = std::lower_bound(range_begin, range_end, target);
	return { leftBound, rightBound };
}


int main() {
	const std::vector<std::string> sorted_strings = { "moscow", "motovilikha", "murmansk" };

	const auto mo_result =
		FindStartsWith(begin(sorted_strings), end(sorted_strings), "mo");
	for (auto it = mo_result.first; it != mo_result.second; ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;

	const auto mt_result =
		FindStartsWith(begin(sorted_strings), end(sorted_strings), "mt");
	std::cout << (mt_result.first - begin(sorted_strings)) << " " <<
		(mt_result.second - begin(sorted_strings)) << std::endl;

	const auto na_result =
		FindStartsWith(begin(sorted_strings), end(sorted_strings), "na");
	std::cout << (na_result.first - begin(sorted_strings)) << " " <<
		(na_result.second - begin(sorted_strings)) << std::endl;

	return 0;
}
