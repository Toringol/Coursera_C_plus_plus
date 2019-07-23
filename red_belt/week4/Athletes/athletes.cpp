/*
* Условие
* У каждого спортсмена на футболке написан уникальный номер. 
* Спортсмены по очереди выходят из раздевалки и должны построиться на стадионе. 
* Тренер каждому выходящему спортсмену называет номер того спортсмена, перед которым нужно встать. 
* Если спортсмена с названным номером на поле нет, то нужно встать в конец шеренги.
*
* В стандартном вводе сначала задано натуральное число n, не превосходящее 100000, — количество спортсменов. 
* Далее идут n пар неотрицательных целых чисел, не превосходящих 100000. 
* Первое число в паре — номер очередного выходящего спортсмена. 
* Второе число в паре — номер того спортсмена, перед которым должен встать текущий.
*
* Напечатайте в стандартный вывод номера спортсменов в порядке построения на поле.
*
* Ограничение по времени — 0,8 с.
*/

#include <iostream>
#include <list>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_ATHLETES = 100'000;

int main() {
	list<size_t> row_athletes;
	vector<list<size_t>::iterator> athletes_pos(MAX_ATHLETES + 1, row_athletes.end());

	size_t athletes_number;
	cin >> athletes_number;

	for (size_t i = 0; i < athletes_number; ++i) {
		size_t athlete, next_athlet;
		cin >> athlete >> next_athlet;
		athletes_pos[athlete] = row_athletes.insert(athletes_pos[next_athlet], athlete);
	}

	for (const auto& it : row_athletes) {
		cout << it << " ";
	}
	cout << endl;

	return 0;
}
