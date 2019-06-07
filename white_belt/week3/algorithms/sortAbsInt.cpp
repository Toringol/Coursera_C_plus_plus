/*
* Условие
* В стандартном потоке дана одна строка, состоящая из N + 1 целых чисел. 
* Первым числом идёт само число N. Далее следуют ещё N чисел, обозначим их за массив A. 
* Между собой числа разделены пробелом.
*
* Отсортируйте массив А по модулю и выведите его в стандартный поток.
* 
* Ограничения
* 0 <= N <= 1000
* -1000000 <= A[i] <= 1000000
*/

#include <iostream>
#include <vector>
#include <algorithm>

int main() {
	size_t masSize;
	std::cin >> masSize;
	std::vector<int> mas(masSize);

	for (auto& elem : mas) {
		std::cin >> elem;
	}

	std::sort(std::begin(mas), std::end(mas), [](int x, int y) {
		return (abs(x) < abs(y));
	});

	for (const auto& elem : mas) {
		std::cout << elem << " ";
	}
	std::cout << std::endl;

	return 0;
}
