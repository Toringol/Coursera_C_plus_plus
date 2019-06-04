/*
* Реализуйте функцию vector<int> Reversed(const vector<int>& v), 
* возвращающую копию вектора v, в которой числа переставлены в обратном порядке.
*/

#include <iostream>
#include <vector>

void Swap(int& first, int& second) {
	int temp = first;
	first = second;
	second = temp;
}

std::vector<int> Reversed(const std::vector<int>& numbers) {
	std::vector<int> tempVector = numbers;
	size_t tempVectorSize = tempVector.size();
	for (size_t i = 0; i < tempVectorSize / 2; ++i)
		Swap(tempVector[i], tempVector[tempVectorSize - i - 1]);
	return tempVector;
}

int main() {
	std::vector<int> numbers = { 1, 5, 3, 4, 2 };
	std::vector<int> newNumbers = Reversed(numbers);

	for (auto value : newNumbers)
		std::cout << value << " ";

	return 0;
}
