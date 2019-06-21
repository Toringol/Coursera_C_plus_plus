/*
* Дано целое положительное число N, не превышающее 9. 
* Выведите все перестановки чисел от 1 до N в обратном лексикографическом порядке (см. пример).
*/

#include <iostream>
#include <vector>
#include <algorithm>

void PrintPermulations(size_t number) {
	std::vector<size_t> vec;
	for (size_t i = number; i != 0; --i) {
		vec.push_back(i);
	}
	do {
		for (size_t i = 0; i < vec.size(); ++i) {
			std::cout << vec[i];
			if (i != (vec.size() - 1))
				std::cout << " ";
		}
		std::cout << std::endl;
	} while (std::prev_permutation(std::begin(vec), std::end(vec)));
}


int main() {
	size_t number = 0;
	std::cin >> number;

	PrintPermulations(number);

	return 0;
}
