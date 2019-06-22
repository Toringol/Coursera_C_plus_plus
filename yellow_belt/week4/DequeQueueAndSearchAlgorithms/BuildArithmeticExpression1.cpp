/*
* Часть 1
* Реализуйте построение арифметического выражения согласно следующей схеме:
* 
* изначально есть выражение, состоящее из некоторого целого числа x;
* на каждом шаге к текущему выражению применяется некоторая операция: прибавление числа, 
* вычитание числа, умножение на число или деление на число; перед применением операции выражение всегда должно быть заключено в скобки.
*
* Формат ввода
* В первой строке содержится исходное целое число x. 
* Во второй строке содержится целое неотрицательное число N— количество операций. 
* В каждой из следующих N строк содержится очередная операция:
*
* - прибавление числа a: + a;
* - либо вычитание числа b: - b;
* - либо умножение на число c: * c;
* - либо деление на число d: / d.
* Количество операций может быть нулевым — в этом случае необходимо вывести исходное число.
*
* Формат вывода
* Выведите единственную строку — построенное арифметическое выражение.
*
* Обратите внимание на расстановку пробелов вокруг символов:
* 
* - каждый символ бинарной операции (+, -, * или /) должен быть окружён ровно одним пробелом с каждой стороны: (8) * 3;
* - символ унарного минуса (для отрицательных чисел) не нуждается в дополнительном пробеле: -5;
* - скобки и числа не нуждаются в дополнительных пробелах.
* 
*/

#include <iostream>
#include <string>
#include <deque>

void BuildArithmeticExpression(std::deque<std::string>& expression, std::string operation, std::string number) {
	expression.push_front("(");
	expression.push_back(") ");
	expression.push_back(operation);
	expression.push_back(" ");
	expression.push_back(number);
}

int main() {
	
	int x = 0;
	std::cin >> x;

	size_t operationsNumber = 0;
	std::cin >> operationsNumber;

	std::deque<std::string> expression;
	expression.push_back(std::to_string(x));

	for (size_t i = 0; i < operationsNumber; ++i) {
		std::string operation, number;
		std::cin >> operation >> number;
		BuildArithmeticExpression(expression, operation, number);
	}

	for (const auto& value : expression) {
		std::cout << value;
	}

	std::cout << std::endl;

	return 0;
}
