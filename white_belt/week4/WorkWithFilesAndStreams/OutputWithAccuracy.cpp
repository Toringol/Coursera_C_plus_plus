/*
* В файле input.txt записаны вещественные числа, по одному на строчку. 
* На стандартный вывод напечатайте эти числа в том же порядке, по одному на строке, 
* но сделайте так, чтобы у каждого из них было ровно три знака после десятичной точки 
* (округление производится по стандартным правилам, т.е. 0.1234 округляется до 0.123, а 0.1235 до 0.124).
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

void PrintFileWithFix(const std::string& path) {
	std::ifstream input(path);

	if (input) {
		std::string number;
		while (std::getline(input, number)) {
			std::cout << std::fixed << std::setprecision(3) << std::stod(number) << std::endl;
		}
	}
}

int main() {
	const std::string path = "input.txt";

	PrintFileWithFix(path);

	return 0;
}
