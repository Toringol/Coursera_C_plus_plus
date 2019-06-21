/*
* Напишите шаблонную функцию FindGreaterElements, принимающую множество elements объектов типа T 
* и ещё один объект border типа T и возвращающую вектор из всех элементов множества, 
* бо́льших border, в возрастающем порядке.
* template <typename T>
* vector<T> FindGreaterElements(const set<T>& elements, const T& border);
*
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <string>

template <typename T>
std::vector<T> FindGreaterElements(const std::set<T>& elements, const T& border) {
	std::vector<T> result;
	auto startIt = std::find_if(std::begin(elements), std::end(elements), 
		[border](const T& element) {
		return element > border;
	});
	for (auto it = startIt; it != std::end(elements); ++it)
		result.push_back(*it);
	return result;
}

int main() {
	for (int x : FindGreaterElements(std::set<int>{1, 5, 7, 8}, 5)) {
		std::cout << x << " ";
	}
	std::cout << std::endl;

	std::string to_find = "Python";
	std::cout << FindGreaterElements(std::set<std::string>{"C", "C++"}, to_find).size() << std::endl;
	return 0;
}

