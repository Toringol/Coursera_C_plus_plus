/*
* Напишите функцию PrintVectorPart, принимающую вектор целых чисел numbers, 
* выполняющую поиск первого отрицательного числа в нём и выводящую в стандартный вывод все числа, 
* расположенные левее найденного, в обратном порядке. Если вектор не содержит отрицательных чисел, 
* выведите все числа в обратном порядке.
* void PrintVectorPart(const vector<int>& numbers);
* 
*/

#include <iostream>
#include <vector>
#include <algorithm>

void PrintVectorPart(const std::vector<int>& numbers) {
	auto end = std::find_if(std::begin(numbers), std::end(numbers), 
		[](const int& number) {
		return number < 0;
	});
	while (end != std::begin(numbers)) {
		--end;
		std::cout << *end << " ";
	}
}

int main() {
	PrintVectorPart({ 6, 1, 8, -5, 4 });
	std::cout << std::endl;
	PrintVectorPart({ -6, 1, 8, -5, 4 });  // ничего не выведется
	std::cout << std::endl;
	PrintVectorPart({ 6, 1, 8, 5, 4 });
	std::cout << std::endl;
	return 0;
}

