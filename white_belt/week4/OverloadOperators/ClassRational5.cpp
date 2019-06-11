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
* Часть 5
* Наконец, вам нужно реализовать возможность использовать объекты класса Rational 
* в качестве элементов контейнера set и ключей в контейнере map. 
* Пример:
* set<Rational> rationals;
* rationals.insert(Rational(1, 2));
* rationals.insert(Rational(1, 3));
* 
* map<Rational, string> name;
* name[Rational(1, 2)] = "одна вторая";
*/


#include <iostream>
#include <cmath>
#include <set>
#include <vector>
#include <map>


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

bool operator<(const Rational& lhs, const Rational& rhs) {
	return (lhs.Numerator() * rhs.Denominator()) < (lhs.Denominator() * rhs.Numerator());
}


int main() {
	{
		const std::set<Rational> rs = { {1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2} };
		if (rs.size() != 3) {
			std::cout << "Wrong amount of items in the set" << std::endl;
			return 1;
		}

		std::vector<Rational> v;
		for (auto x : rs) {
			v.push_back(x);
		}
		if (v != std::vector<Rational>{ {1, 25}, { 1, 2 }, { 3, 4 }}) {
			std::cout << "Rationals comparison works incorrectly" << std::endl;
			return 2;
		}
	}

	{
		std::map<Rational, int> count;
		++count[{1, 2}];
		++count[{1, 2}];

		++count[{2, 3}];

		if (count.size() != 2) {
			std::cout << "Wrong amount of items in the map" << std::endl;
			return 3;
		}
	}

	std::cout << "OK" << std::endl;
	return 0;
}
