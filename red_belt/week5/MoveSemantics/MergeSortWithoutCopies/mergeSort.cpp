/*
* Условие
* Напишите шаблонную функцию MergeSort, 
* принимающую два итератора шаблонного типа RandomIt и сортирующую заданный ими диапазон с помощью сортировки слиянием. 
* Гарантируется, что:
*
* - итераторы типа RandomIt аналогичны по функциональности итераторам вектора и строки, 
* то есть их можно сравнивать с помощью операторов <, <=, > и >=, а также вычитать и складывать с числами;
* - сортируемые объекты можно сравнивать с помощью оператора <.
*
* template <typename RandomIt>
* void MergeSort(RandomIt range_begin, RandomIt range_end);
*
* Алгоритм
* В этой задаче вы должны реализовать точь-в-точь алгоритм, представленный ниже; 
* тестирующая система будет проверять, что вы выполняете с элементами именно эти действия:
*
* 1) Если диапазон содержит меньше 2 элементов, выйти из функции.
* 2) Создать вектор, содержащий все элементы текущего диапазона.
* 3) Разбить вектор на три равные части. (В этой задаче гарантируется, 
* что длина передаваемого диапазона является степенью тройки, 
* так что вектор всегда можно разбить на три равные части.)
* 4) Вызвать функцию MergeSort от каждой части вектора.
* 5) Слить первые две трети вектора с помощью алгоритма merge, сохранив результат во временный вектор с помощью back_inserter.
* 6) Слить временный вектор из предыдущего пункта с последней третью вектора из п. 2, 
* записав полученный отсортированный диапазон вместо исходного.
* В процессе работы вашего алгоритма не должно происходить копирования сортируемых элементов. 
* Если вы используете копирование, при отправке не проверку решение не скомпилируется.
*/

#include "test_runner.h"
#include <algorithm>
#include <memory>
#include <vector>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
	
	int range_length = range_end - range_begin;
	if (range_length < 2) {
		return;
	}

	vector<typename RandomIt::value_type> elements(make_move_iterator(range_begin), 
												   make_move_iterator(range_end));

	auto one_third = elements.begin() + range_length / 3;
	auto two_third = elements.begin() + range_length * 2 / 3;

	MergeSort(elements.begin(), one_third);
	MergeSort(one_third, two_third);
	MergeSort(two_third, elements.end());

	vector<typename RandomIt::value_type> interim_result;
	merge(make_move_iterator(elements.begin()), 
		  make_move_iterator(one_third), 
		  make_move_iterator(one_third), 
		  make_move_iterator(two_third),
		  back_inserter(interim_result));
	merge(make_move_iterator(interim_result.begin()), 
		  make_move_iterator(interim_result.end()), 
		  make_move_iterator(two_third), 
		  make_move_iterator(elements.end()),
		  range_begin);
}

void TestIntVector() {
	vector<int> numbers = { 6, 1, 3, 9, 1, 9, 8, 12, 1 };
	MergeSort(begin(numbers), end(numbers));
	ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestIntVector);
	return 0;
}
