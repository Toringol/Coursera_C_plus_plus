/*
* Ваша программа должна считать содержимое файла input.txt и 
* напечатать его на экран без изменений. 
* Гарантируется, что содержимое файла input.txt заканчивается переводом строки.
*/

#include <iostream>
#include <fstream>
#include <string>

void PrintFile(const std::string& path) {
	std::ifstream input(path);
	if (input) {
		std::string line;
		while (std::getline(input, line)) {
			std::cout << line << std::endl;
		}
	}
}

int main() {
	const std::string path = "input.txt";

	PrintFile(path);

	return 0;
}
