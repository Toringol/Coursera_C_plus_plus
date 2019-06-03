/*
* Напишите функцию MoveStrings, которая принимает два вектора строк, source и destination, 
* и дописывает все строки из первого вектора в конец второго. 
* После выполнения функции вектор source должен оказаться пустым.
*/

#include <iostream>
#include <string>
#include <vector>

void MoveStrings(std::vector<std::string>& source, std::vector<std::string>& destination) {
	for (auto str : source)
		destination.push_back(str);
	source.clear();
}

int main() {
	std::vector<std::string> source = { "a", "b", "c" };
	std::vector<std::string> destination = { "z" };

	MoveStrings(source, destination);

	for (auto str : destination)
		std::cout << str << " ";

	return 0;
}
