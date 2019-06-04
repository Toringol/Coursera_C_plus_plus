/*
* Напишите функцию, которая
* 
* - называется Factorial
* - возвращает int
* - принимает int и возвращает факториал своего аргумента.
* Гарантируется, что аргумент функции по модулю не превышает 10. 
* Для отрицательных аргументов функция должна возвращать 1.
*/

#include <iostream>

int Factorial(int number) {
	if (number <= 1) {
		return 1;
	}
	else {
		return number * Factorial(number - 1);
	}
}

int main() {
	int number;
	std::cin >> number;

	std::cout << Factorial(number) << std::endl;

	return 0;
}
