/*
* Дана строка. Найдите в этой строке второе вхождение буквы f и выведите индекс этого вхождения. 
* Если буква f в данной строке встречается только один раз, 
* выведите число -1, а если не встречается ни разу, выведите число -2. Индексы нумеруются с нуля.
*/

#include <iostream>
#include <string>

int main() {
	std::string str;
	std::cin >> str;

	int check = 0;
	for (int i = 0; i < str.size(); ++i) {
		if (str[i] == 'f') {
			check++;
		}
		if (check == 2) {
			std::cout << i << std::endl;
			break;
		}
	}

	if (check == 1)
		std::cout << -1 << std::endl;
	if (check == 0)
		std::cout << -2 << std::endl;

	return 0;
}
