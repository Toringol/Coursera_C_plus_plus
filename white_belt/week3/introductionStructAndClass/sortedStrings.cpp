/*
* Реализуйте класс, поддерживающий набор строк в отсортированном порядке. 
* Класс должен содержать два публичных метода:
* class SortedStrings {
* public:
*   void AddString(const string& s) {
* 	// добавить строку s в набор
*   }
*   vector<string> GetSortedStrings() {
* 	// получить набор из всех добавленных строк в отсортированном порядке
*   }
* private:
*   // приватные поля
* };
*
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class SortedStrings {
public:
	void AddString(const std::string& s) {
		strings.push_back(s);
	}
	std::vector<std::string> GetSortedStrings() {
		std::vector<std::string> sortedStrings(strings);
		std::sort(std::begin(sortedStrings), std::end(sortedStrings));
		return sortedStrings;
	}
private:
	std::vector<std::string> strings;
};


void PrintSortedStrings(SortedStrings& strings) {
	for (const std::string& s : strings.GetSortedStrings()) {
		std::cout << s << " ";
	}
	std::cout << std::endl;
}

int main() {
	SortedStrings strings;

	strings.AddString("first");
	strings.AddString("third");
	strings.AddString("second");
	PrintSortedStrings(strings);

	strings.AddString("second");
	PrintSortedStrings(strings);

	return 0;
}
