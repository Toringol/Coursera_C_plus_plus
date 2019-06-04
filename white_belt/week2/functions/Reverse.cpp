/*
* Реализуйте функцию void Reverse(vector<int>& v), 
* которая переставляет элементы вектора в обратном порядке.
*/

#include <iostream>
#include <vector>

void Swap(int& first, int& second) {
	int temp = first;
	first = second;
	second = temp;
}

void Reverse(std::vector<int>& numbers) {
	for (size_t i = 0; i < numbers.size() / 2; ++i)
		Swap(numbers[i], numbers[numbers.size() - i - 1]);
}

int main() {
	std::vector<int> numbers = { 1, 5, 3, 4, 2 };
	Reverse(numbers);

	for (auto value : numbers)
		std::cout << value << " ";

	return 0;
}
