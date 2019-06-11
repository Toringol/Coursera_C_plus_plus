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
* Часть 4
* В этой части вам нужно реализовать операторы ввода и вывода для класса Rational. 
* В результате у вас должен работать, например, такой код
* Rational r;
* cin >> r;
* cout << r;
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

std::ostream& operator<<(std::ostream& stream, const Rational& rational) {
	stream << rational.Numerator() << "/" << rational.Denominator();
	return stream;
}

std::istream& operator>>(std::istream& stream, Rational& rational) {
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


int main() {
	{
		std::ostringstream output;
		output << Rational(-6, 8);
		if (output.str() != "-3/4") {
			std::cout << "Rational(-6, 8) should be written as \"-3/4\"" << std::endl;
			return 1;
		}
	}

	{
		std::istringstream input("5/7");
		Rational r;
		input >> r;
		bool equal = r == Rational(5, 7);
		if (!equal) {
			std::cout << "5/7 is incorrectly read as " << r << std::endl;
			return 2;
		}
	}

	{
		std::istringstream input("5/7 10/8");
		Rational r1, r2;
		input >> r1 >> r2;
		bool correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
		if (!correct) {
			std::cout << "Multiple values are read incorrectly: " << r1 << " " << r2 << std::endl;
			return 3;
		}

		input >> r1;
		input >> r2;
		correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
		if (!correct) {
			std::cout << "Read from empty stream shouldn't change arguments: " << r1 << " " << r2 << std::endl;
			return 4;
		}
	}

	std::cout << "OK" << std::endl;
	return 0;
}
