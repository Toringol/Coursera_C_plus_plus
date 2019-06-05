/*
* Слова называются анаграммами друг друга, если одно из них можно получить перестановкой букв в другом. 
* Например, слово «eat» можно получить перестановкой букв слова «tea», поэтому эти слова являются анаграммами друг друга. 
* Даны пары слов, проверьте для каждой из них, являются ли слова этой пары анаграммами друг друга.
* 
* Указание
* Один из способов проверки того, являются ли слова анаграммами друг друга, заключается в следующем. 
* Для каждого слова с помощью словаря подсчитаем, сколько раз в нём встречается каждая буква. 
* Если для обоих слов эти словари равны (а это проверяется с помощью обычного оператора ==), 
*то слова являются анаграммами друг друга, в противном случае не являются.
*
* При этом построение такого словаря по слову удобно вынести в отдельную функцию BuildCharCounters.
*
* Формат ввода
* Сначала дано число пар слов N, затем в N строках содержатся пары слов, которые необходимо проверить. 
* Гарантируется, что все слова состоят лишь из строчных латинских букв.
*
* Формат вывода
* Выведите N строк: для каждой введённой пары слов YES, если эти слова являются анаграммами, и NO в противном случае.
*/

#include <iostream>
#include <map>
#include <string>

std::map<char, size_t> BuildCharCounters(const std::string& str) {
	std::map<char, size_t> result;
	for (const auto& ch : str)
		++result[ch];
	return result;
}

bool Anagram(const std::string& first, const std::string& second) {
	if (BuildCharCounters(first) == BuildCharCounters(second))
		return true;
	else
		return false;
}

int main() {
	size_t strPairNumber;
	std::cin >> strPairNumber;
	
	for (size_t i = 0; i < strPairNumber; ++i) {
		std::string first, second;
		std::cin >> first >> second;
		if (Anagram(first, second))
			std::cout << "YES" << std::endl;
		else
			std::cout << "NO" << std::endl;
	}

	return 0;
}
