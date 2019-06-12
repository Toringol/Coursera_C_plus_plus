/*
* Вспомним класс Rational, который мы реализовали в задачах, 
* посвящённых перегрузке операторов. Там специально говорилось, 
* что в тестах объекты класса Rational никогда не создаются 
* с нулевым знаменателем и никогда не выполняется деление на ноль. 
* Настало время избавиться от этого ограничения и научиться обрабатывать 
* нулевой знаменатель и деление на ноль. В этой задаче вам предстоит это сделать.
*
* Поменяйте реализацию конструктора класса Rational так, 
* чтобы он выбрасывал исключение invalid_argument, если знаменатель равен нулю. 
* Кроме того, переделайте реализацию оператора деления для класса Rational так, 
* чтобы он выбрасывал исключение domain_error, если делитель равен нулю.
*
* Напомним, что вам надо реализовать интерфейс
* class Rational {
* public:
*   Rational();
*   Rational(int numerator, int denominator);
* 
*   int Numerator() const;
*   int Denominator() const;
* };
* и оператор деления для класса Rational
* Rational operator / (const Rational& lhs, const Rational& rhs);
*/

#include <iostream>
#include <cmath>

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
			throw std::invalid_argument("");
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

Rational operator / (const Rational& lhs, const Rational& rhs) {
	if (lhs.Denominator() * rhs.Numerator() == 0)
		throw std::domain_error("");
	return Rational(lhs.Numerator() * rhs.Denominator(), lhs.Denominator() * rhs.Numerator());
}

int main() {
	try {
		Rational r(1, 0);
		std::cout << "Doesn't throw in case of zero denominator" << std::endl;
		return 1;
	}
	catch (std::invalid_argument&) {
	}

	try {
		auto x = Rational(1, 2) / Rational(0, 1);
		std::cout << "Doesn't throw in case of division by zero" << std::endl;
		return 2;
	}
	catch (std::domain_error&) {
	}

	std::cout << "OK" << std::endl;
	return 0;
}
