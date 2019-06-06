/*
* Два слова называются синонимами друг друга, если они имеют похожие значения. 
* Реализуйте следующие операции над словарём синонимов:
*
* - ADD word1 word2 — добавить в словарь пару синонимов (word1, word2).
* - COUNT word — узнать количество синонимов слова word.
* - CHECK word1 word2 — проверить, являются ли слова word1 и word2 синонимами. 
* Слова word1 и word2 считаются синонимами, если среди запросов ADD 
* был хотя бы один запрос ADD word1 word2 или ADD word2 word1.
* Формат ввода
* Сначала вводится количество запросов Q, затем Q строк с описаниями запросов. 
* Гарантируется, что в каждом запросе CHECK и ADD слова word1 и word2 различны. 
* Все слова состоят лишь из латинских букв, цифр и символов подчёркивания.
*
* Формат вывода
* Для каждого запроса в соответствующей строке выведите ответ на него:
* 
* - В ответ на запрос COUNT word выведите единственное целое число — количество синонимов слова word.
* - В ответ на запрос CHECK word1 word2 выведите строку YES, если word1 и word2 являются синонимами, и NO в противном случае.
*/

#include <iostream>
#include <map>
#include <set>
#include <string>

void Add(std::map<std::string, std::set<std::string>>& dictionary, const std::string& word1, const std::string& word2) {
	dictionary[word1].insert(word2);
	dictionary[word2].insert(word1);
}

size_t Count(std::map<std::string, std::set<std::string>>& dictionary, const std::string word) {
	return dictionary[word].size();
}

void Check(std::map<std::string, std::set<std::string>>& dictionary, const std::string& word1, const std::string& word2) {
	if (dictionary[word1].count(word2) || dictionary[word2].count(word1)) {
		std::cout << "YES" << std::endl;
	}
	else {
		std::cout << "NO" << std::endl;
	}
}

int main() {
	size_t operationsNumber;
	std::cin >> operationsNumber;

	std::map<std::string, std::set<std::string>> dictionary;

	for (size_t i = 0; i < operationsNumber; ++i) {
		std::string operationCode;
		std::cin >> operationCode;
		if (operationCode == "ADD") {
			std::string word1, word2;
			std::cin >> word1 >> word2;
			Add(dictionary, word1, word2);
		}
		else if (operationCode == "COUNT") {
			std::string word;
			std::cin >> word;
			std::cout << Count(dictionary, word) << std::endl;
		}
		else if (operationCode == "CHECK") {
			std::string word1, word2;
			std::cin >> word1 >> word2;
			Check(dictionary, word1, word2);
		}
	}

	return 0;
}
