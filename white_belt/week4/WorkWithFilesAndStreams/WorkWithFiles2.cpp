/*
* Снова считайте все содержимое файла input.txt, но на этот раз выведите его в файл output.txt. 
* Точно так же гарантируется, что содержимое файла input.txt заканчивается переводом строки.
*/


#include <iostream>
#include <fstream>
#include <string>

void PrintToAnotherFile(const std::string& pathRead, const std::string& pathWrite) {
	std::ifstream input(pathRead);
	std::ofstream output(pathWrite);

	if (input) {
		std::string line;
		while (std::getline(input, line)) {
			output << line << std::endl;
		}
	}
}

int main() {
	const std::string pathRead = "input.txt";
	const std::string pathWrite = "output.txt";

	PrintToAnotherFile(pathRead, pathWrite);

	return 0;
}
