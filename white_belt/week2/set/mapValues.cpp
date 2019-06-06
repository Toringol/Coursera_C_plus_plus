/*
* Напишите функцию BuildMapValuesSet, принимающую на вход словарь map<int, string> 
* и возвращающую множество значений этого словаря:
* set<string> BuildMapValuesSet(const map<int, string>& m) {
*   // ...
* }
*/

#include <iostream>
#include <map>
#include <set>
#include <string>

std::set<std::string> BuildMapValuesSet(const std::map<int, std::string>& m) {
	std::set<std::string> resultSet;
	for (const auto& item : sourceMap) {
		resultSet.insert(item.second);
	}
	return resultSet;
}

int main() {
	std::set<std::string> values = BuildMapValuesSet({
	{1, "odd"},
	{2, "even"},
	{3, "odd"},
	{4, "even"},
	{5, "odd"}
		});

	for (const std::string& value : values) {
		std::cout << value << std::endl;
	}

	return 0;
}
