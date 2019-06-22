/*
* Напишите функцию FindNearestElement, для множества целых чисел numbers и данного числа border 
* возвращающую итератор на элемент множества, ближайший к border. Если ближайших элементов несколько, 
* верните итератор на наименьший из них.
*/

#include <iostream>
#include <set>
#include <algorithm>

std::set<int>::const_iterator FindNearestElement(const std::set<int>& numbers, int border) {
	if (numbers.empty())
		return std::end(numbers);
	std::set<int>::const_iterator it = numbers.lower_bound(border);
	if (it == std::end(numbers))
		it = std::prev(std::end(numbers));
	else if (it != std::begin(numbers) && ((border - *std::prev(it)) <= (*it - border)))
		it = std::prev(it);
	return it;
}


int main() {
	std::set<int> numbers = { 1, 4, 6 };
	std::cout <<
		*FindNearestElement(numbers, 0) << " " <<
		*FindNearestElement(numbers, 3) << " " <<
		*FindNearestElement(numbers, 5) << " " <<
		*FindNearestElement(numbers, 6) << " " <<
		*FindNearestElement(numbers, 100) << std::endl;

	std::set<int> empty_set;

	std::cout << (FindNearestElement(empty_set, 8) == end(empty_set)) << std::endl;
	return 0;
}
