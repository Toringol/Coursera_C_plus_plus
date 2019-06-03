/*
* На вход вашей программе в стандартном вводе даны 
* действительные коэффициенты A, B и C уравнения Ax² + Bx + C = 0. 
* Выведите все его различные действительные корни в любом порядке. 
* Гарантируется, что хотя бы один из коэффициентов не равен нулю.
*/

#include <iostream>
#include <cmath>

int main() {
	double A, B, C;
	std::cin >> A >> B >> C;

	double discriminant = B * B - 4 * A * C;

	if (A == 0) {
		if (B != 0) {
			std::cout << -C / B << std::endl;
		}
	}
	else if (discriminant == 0) {
		std::cout << -B / (2 * A) << std::endl;
	}
	else if (discriminant > 0) {

		double x1 = (-B + sqrt(discriminant)) / (2 * A);
		double x2 = (-B - sqrt(discriminant)) / (2 * A);

		std::cout << x1 << " " << x2 << std::endl;

	}

	return 0;
}
