/*
* На вход программе через стандартный ввод передаются два целых числа, 
* по модулю не превышающие 100000. 
* Выведите в стандартный вывод их сумму.
*
* stdin	 stdout
* 2 3	   5
* -4 -9	 -13
* -1 2	 1
*
*/

#include <iostream>

int main() {
	int a, b;
	std::cin >> a >> b;

	std::cout << a + b << std::endl;

	return 0;
}
