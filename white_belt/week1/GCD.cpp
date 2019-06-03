/*
* В stdin даны два натуральных числа. Выведите в stdout их наибольший общий делитель.
* 
* Пример
* 
* stdin	  stdout
* 25 27	  1
* 12 16	  4
* 13 13	  13
* 
* Алгоритм Евклида:
* Пока A > 0 и B > 0:
*   Если A > B:
*     A = A % B
*   иначе:
*     B = B % A
* Вывести A + B
*
*/

#include <iostream>

int main() {
	int a, b;
	std::cin >> a >> b;

	while (a > 0 && b > 0) {
		if (a > b)
			a = a % b;
		else
			b = b % a;
	}

	std::cout << a + b;

	return 0;
}
