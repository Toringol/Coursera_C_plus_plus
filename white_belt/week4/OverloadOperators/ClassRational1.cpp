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
* Часть 1
* В первой части вам надо реализовать класс Rational, который представляет собой рациональное число вида p/q, 
* где p целое, а q натуральное. Он должен иметь следующий интерфейс:
* class Rational {
* public:
*   Rational();
*   Rational(int numerator, int denominator);
*
*   int Numerator() const;
*   int Denominator() const;
* };
* Класс Rational должен гарантировать, что p/q — это несократимая дробь. Например, код
* Rational r(4, 6);
* cout << r.Numerator() << '/' << r.Denominator();
* должен выводить «2/3» — именно поэтому мы делаем Rational классом, а не структурой. 
* Структура позволила бы нарушить этот инвариант:
* struct Rational {
*    int numerator, denominator;
* };
* 
* Rational r{2, 3};
* r.numerator = 6; // Нарушен инвариант несократимости
* Список требований, предъявляемых к реализации интерфейса класса Rational:
*
* 1) Конструктор по умолчанию должен создавать дробь с числителем 0 и знаменателем 1.
* 2) При конструировании объека класса Rational с параметрами p и q должно выполняться 
* сокращение дроби p/q (здесь вам может пригодиться решение задачи «Наибольший общий делитель»).
* 3) Если дробь p/q отрицательная, то объект Rational(p, q) должен иметь отрицательный числитель и положительный знаменатель.
* 4) Если дробь p/q положительная, то объект Rational(p, q) должен иметь положительные числитель и знаменатель 
* (обратите внимание на случай Rational(-2, -3)).
* 5) Если числитель дроби равен нулю, то знаменатель должен быть равен 1.
* Гарантируется, что ни в одном из тестов, на которых будет тестироваться ваша реализация, не будет знаменателя, равного нулю.
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

int main() {

	{
		const Rational r(3, 10);
		if (r.Numerator() != 3 || r.Denominator() != 10) {
			std::cout << "Rational(3, 10) != 3/10" << std::endl;
			return 1;
		}
	}

	{
		const Rational r(8, 12);
		if (r.Numerator() != 2 || r.Denominator() != 3) {
			std::cout << "Rational(8, 12) != 2/3" << std::endl;
			return 2;
		}
	}

	{
		const Rational r(-4, 6);
		if (r.Numerator() != -2 || r.Denominator() != 3) {
			std::cout << "Rational(-4, 6) != -2/3" << std::endl;
			return 3;
		}
	}

	{
		const Rational r(4, -6);
		if (r.Numerator() != -2 || r.Denominator() != 3) {
			std::cout << "Rational(4, -6) != -2/3" << std::endl;
			return 3;
		}
	}

	{
		const Rational r(0, 15);
		if (r.Numerator() != 0 || r.Denominator() != 1) {
			std::cout << "Rational(0, 15) != 0/1" << std::endl;
			return 4;
		}
	}

	{
		const Rational defaultConstructed;
		if (defaultConstructed.Numerator() != 0 || defaultConstructed.Denominator() != 1) {
			std::cout << "Rational() != 0/1" << std::endl;
			return 5;
		}
	}

	std::cout << "OK" << std::endl;
	return 0;
}
