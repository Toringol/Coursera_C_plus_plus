/*
* Напишите шаблонную функцию RemoveDuplicates, 
* принимающую по ссылке вектор elements объектов типа T и удаляющую из него все дубликаты элементов. 
* Порядок оставшихся элементов может быть любым.
*
* Гарантируется, что объекты типа T можно сравнивать с помощью операторов ==, !=, < и >.
* template <typename T>
* void RemoveDuplicates(vector<T>& elements);
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

template <typename T>
void RemoveDuplicates(std::vector<T>& elements) {
	std::sort(std::begin(elements), std::end(elements));
	auto startEraseIt = std::unique(std::begin(elements), std::end(elements));
	elements.erase(startEraseIt, std::end(elements));
}

int main() {
	std::vector<int> v1 = { 6, 4, 7, 6, 4, 4, 0, 1 };
	RemoveDuplicates(v1);
	for (int x : v1) {
		std::cout << x << " ";
	}
	std::cout << std::endl;

	std::vector<std::string> v2 = { "C", "C++", "C++", "C", "C++" };
	RemoveDuplicates(v2);
	for (const std::string& s : v2) {
		std::cout << s << " ";
	}
	std::cout << std::endl;
	return 0;
}
