/*
* Итак, теперь у нас с вами есть полноценный тип для представления обыкновенных дробей: 
* класс Rational интегрирован в язык с помощью перегрузки операторов и 
* не позволяет выполнять некорректные операции за счёт выбрасывания исключений. 
* Давайте на основе класса Rational создадим простой калькулятор для обыкновенных дробей.
* 
* Вам надо написать программу, которая считывает из стандартного ввода одну строку в формате 
* ДРОБЬ_1 операция ДРОБЬ_2. ДРОБЬ_1 и ДРОБЬ_2 имеют формат X/Y, 
* где X — целое, а Y — целое неотрицательное число. операция — это один из символов '+', '-', '*', '/'.
* 
* Если ДРОБЬ_1 или ДРОБЬ_2 является некорректной обыкновенной дробью, 
* ваша программа должна вывести в стандартный вывод сообщение "Invalid argument". 
* Если считанная операция — это деление на ноль, выведите в стандартный вывод сообщение 
* "Division by zero". В противном случае выведите результат операции.
*/

#include <iostream>
#include <cmath>
#include <string>
#include <sstream>

size_t GCD(int numerator, int demoninator) {
	size_t number1 = std::abs(numerator);
	size_t number2 = std::abs(demoninator);
	while (number1 > 0 && number2 > 0) {
		if (number1 > number2)
			number1 = number1 % number2;
		else
			number2 = number2 % number1;
	}
	return (number1 + number2);
}


class Rational {
public:
	Rational() {
		p = 0;
		q = 1;
	}

	Rational(int numerator, int denominator) {
		if (denominator == 0)
			throw std::invalid_argument("Invalid argument");
		int gcd = GCD(numerator, denominator);
		if (numerator == 0) {
			p = 0;
			q = 1;
		}
		else if (denominator < 0) {
			p = -numerator / gcd;
			q = -denominator / gcd;
		}
		else {
			p = numerator / gcd;
			q = denominator / gcd;
		}
	}

	int Numerator() const {
		return p;
	}

	int Denominator() const {
		return q;
	}

private:
	int p;
	size_t q;
};

Rational operator + (const Rational& lhs, const Rational& rhs) {
	int gcd = GCD(lhs.Denominator(), rhs.Denominator());
	return Rational(lhs.Numerator() * rhs.Denominator() + rhs.Numerator() * lhs.Denominator(),
		lhs.Denominator() * rhs.Denominator());
}

Rational operator - (const Rational& lhs, const Rational& rhs) {
	int gcd = GCD(lhs.Denominator(), rhs.Denominator());
	return Rational(lhs.Numerator() * rhs.Denominator() - rhs.Numerator() * lhs.Denominator(),
		lhs.Denominator() * rhs.Denominator());
}

bool operator == (const Rational& lhs, const Rational& rhs) {
	if ((lhs.Numerator() * rhs.Denominator() - rhs.Numerator() * lhs.Denominator()) == 0) {
		return true;
	}
	return false;
}

Rational operator * (const Rational& lhs, const Rational& rhs) {
	return Rational(lhs.Numerator() * rhs.Numerator(), lhs.Denominator() * rhs.Denominator());
}

Rational operator / (const Rational& lhs, const Rational& rhs) {
	if (lhs.Denominator() * rhs.Numerator() == 0)
		throw std::domain_error("Division by zero");
	return Rational(lhs.Numerator() * rhs.Denominator(), lhs.Denominator() * rhs.Numerator());
}

std::ostream& operator << (std::ostream& stream, const Rational& rational) {
	stream << rational.Numerator() << "/" << rational.Denominator();
	return stream;
}

std::istream& operator >> (std::istream& stream, Rational& rational) {
	char slash;
	int p = 0;
	int q = 0;
	stream >> p;
	stream >> slash;
	stream >> q;
	if (stream && slash == '/')
		rational = { p, q };
	return stream;
}

bool operator < (const Rational& lhs, const Rational& rhs) {
	return (lhs.Numerator() * rhs.Denominator()) < (lhs.Denominator() * rhs.Numerator());
}

Rational Calculation(Rational& first, Rational& second, char operation) {
	if (operation == '+')
		return first + second;
	else if (operation == '-')
		return first - second;
	else if (operation == '*')
		return first * second;
	else if (operation == '/')
		return first / second;
}

int main() {

	try {
		Rational firstFraction, secondFraction;
		char operation;
		std::cin >> firstFraction >> operation >> secondFraction;
		Rational result = Calculation(firstFraction, secondFraction, operation);
		std::cout << result;
	} 
	catch (std::invalid_argument& in) {
		std::cout << in.what() << std::endl;
	}
	catch (std::domain_error& d) {
		std::cout << d.what() << std::endl;
	}

	return 0;
}
