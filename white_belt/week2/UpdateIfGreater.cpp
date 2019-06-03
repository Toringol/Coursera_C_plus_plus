/*
* Напишите функцию UpdateIfGreater, которая принимает два целочисленных аргумента: 
* first и second. Если first оказался больше second, 
* Ваша функция должна записывать в second значение параметра first. 
* При этом изменение параметра second должно быть видно на вызывающей стороне.
*/

#include <iostream>

void UpdateIfGreater(int first, int& second) {
	if (first > second) {
		second = first;
	}
}

int main() {
	int a, b;
	std::cin >> a >> b;

	UpdateIfGreater(a, b);
	std::cout << a << " " << b;
	return 0;
}
