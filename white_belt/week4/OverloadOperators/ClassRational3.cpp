/*
* В этой задаче вам надо разработать класс для представления рациональных чисел и 
* внедрить его в систему типов языка С++ так, чтобы им можно было пользоваться естественным образом. 
* Задание состоит из нескольких частей. К каждой части приложен файл с заготовкой программы, 
* который имеет следующую структуру
* #include <iostream>
* using namespace std;
* 
* // Комментарии, которые говорят, что именно нужно реализовать в этой программе
* 
* int main() {
*   // Набор юнит-тестов для вашей реализации
*   cout << "OK" << endl;
*   return 0;
* }
*
* Вам нужно, не меняя тело функции main, реализовать то, что предложено в комментариях, 
* так, чтобы ваша программа выводила на экран сообщение OK. Функция main содержит ряд юнит-тестов, 
* которые проверяют правильность вашей реализации. Если эти тесты находят ошибку в вашей реализации, 
* то вместо OK программа выведет подсказку о том, что именно работает неправильно.
* 
* Когда ваша программа начнёт выводить OK, можете отправлять свой файл на проверку. 
* Ваша реализация будет тестироваться на другом, более полном наборе тестов. 
* То есть, если ваша программа выводит OK, то это не даёт гарантии, 
* что ваша реализация будет принята тестирующей системой. 
* В случае неудачной посылки тестирующая система также выдаст вам подсказку о том, 
* какая именно часть реализации работает неправильно.
* 
* Внимательно изучите набор юнит-тестов для каждой заготовки решения. 
* Тесты описывают требования, предъявляемые к вашей реализации, 
* которые могут быть не указаны в условии задач
* 
* На проверку можно отправлять весь файл с вашей реализацией: функцию main удалять из него не нужно.
* Часть 3
* Аналогично предыдущей части, реализуйте операторы * и /. 
* Например, следующий код должен быть валидным:
* const Rational r = Rational(1, 2) * Rational(1, 3) / Rational(1, 4);
* if (r == Rational(2, 3)) {
*   cout << "equal";
* }
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

Rational operator+(const Rational& lhs, const Rational& rhs) {
	int gcd = GCD(lhs.Denominator(), rhs.Denominator());
	return Rational(lhs.Numerator() * rhs.Denominator() + rhs.Numerator() * lhs.Denominator(), 
					lhs.Denominator() * rhs.Denominator());
}

Rational operator-(const Rational& lhs, const Rational& rhs) {
	int gcd = GCD(lhs.Denominator(), rhs.Denominator());
	return Rational(lhs.Numerator() * rhs.Denominator() - rhs.Numerator() * lhs.Denominator(),
		lhs.Denominator() * rhs.Denominator());
}

bool operator==(const Rational& lhs, const Rational& rhs) {
	if ((lhs.Numerator() * rhs.Denominator() - rhs.Numerator() * lhs.Denominator()) == 0) {
		return true;
	}
	return false;
}

Rational operator*(const Rational& lhs, const Rational& rhs) {
	return Rational(lhs.Numerator() * rhs.Numerator(), lhs.Denominator() * rhs.Denominator());
}

Rational operator/(const Rational& lhs, const Rational& rhs) {
	return Rational(lhs.Numerator() * rhs.Denominator(), lhs.Denominator() * rhs.Numerator());
}



int main() {
	{
		Rational a(2, 3);
		Rational b(4, 3);
		Rational c = a * b;
		bool equal = c == Rational(8, 9);
		if (!equal) {
			std::cout << "2/3 * 4/3 != 8/9" << std::endl;
			return 1;
		}
	}

	{
		Rational a(5, 4);
		Rational b(15, 8);
		Rational c = a / b;
		bool equal = c == Rational(2, 3);
		if (!equal) {
			std::cout << "5/4 / 15/8 != 2/3" << std::endl;
			return 2;
		}
	}

	std::cout << "OK" << std::endl;
	return 0;
}
