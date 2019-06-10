/*
* В первой строке файла input.txt записаны два числа N и M. 
* Далее в файле находится таблица из N строк и M столбцов, 
* представленная в формате CSV (comma-separated values). 
* Такой формат часто используется для текстового представления таблиц с данными: 
* в файле несколько строк, значения из разных ячеек внутри строки отделены друг от друга запятыми. 
* Ваша задача — вывести данные на экран в виде таблицы. Формат таблицы:
* 
* 1) размер ячейки равен 10,
* 
* 2) соседние ячейки отделены друг от друга пробелом,
* 
* 3) последняя ячейка в строке НЕ оканчивается пробелом,
* 
* 4) последняя строка НЕ оканчивается символом перевода строки. 
* Гарантируется, что в таблице будет ровно N строк и M столбцов, 
* значение каждой из ячеек — целое число. Пример ввода
* 2 3
* 1,2,3
* 4,5,6
* Пример вывода
*          1          2          3
*          4          5          6
*/


#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

void PrintTableFromFile(const std::string& path) {
	std::ifstream input(path);

	size_t a = 0, b = 0;

	if (input) {
		input >> a;
		input >> b;
		input.ignore(1);
		std::string number;
		for (size_t i = 0; i < a; ++i) {
			for (size_t j = 0; j < b - 1; ++j) {
				std::getline(input, number, ',');	
				std::cout << std::setw(10) << number << " ";
			}
			std::getline(input, number, '\n');
			std::cout << std::setw(10) << number;
			if (i != a - 1) {
				std::cout << std::endl;
			}
		}
	}
}

int main() {
	const std::string path = "input.txt";

	PrintTableFromFile(path);

	return 0;
}
