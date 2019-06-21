/*
* Напишите шаблонную функцию MergeSort, 
* принимающую два итератора шаблонного типа RandomIt и сортирующую заданный ими диапазон с помощью сортировки слиянием. 
* Гарантируется, что:
*
* - итераторы типа RandomIt аналогичны по функциональности итераторам вектора и строки, 
* то есть их можно сравнивать с помощью операторов <, <=, > и >=, а также вычитать и складывать с числами;
* - сортируемые объекты можно сравнивать с помощью оператора <.
* template <typename RandomIt>
* void MergeSort(RandomIt range_begin, RandomIt range_end);
* Часть 1. Реализация с разбиением на 2 части
* Алгоритм
* Классический алгоритм сортировки слиянием выглядит следующим образом:
*
* 1) Если диапазон содержит меньше 2 элементов, выйти из функции.
* 2) Создать вектор, содержащий все элементы текущего диапазона.
* 3) Разбить вектор на две равные части. (В этой задаче гарантируется, 
* что длина передаваемого диапазона является степенью двойки, так что вектор всегда можно разбить на две равные части.)
* 4) Вызвать функцию MergeSort от каждой половины вектора.
* 5) С помощью алгоритма merge слить отсортированные половины, записав полученный отсортированный диапазон вместо исходного.
* Вы должны реализовать именно этот алгоритм и никакой другой: тестирующая система будет проверять, 
* что вы выполняете с элементами именно эти действия.
*
* Часть 2. Реализация с разбиением на 3 части
* Реализуйте сортировку слиянием, разбивая диапазон на 3 равные части, а не на 2. 
* Гарантируется, что длина исходного диапазона является степенью 3.
*
* Соответственно, пункты 3–5 алгоритма нужно заменить следующими:
*
* - Разбить вектор на 3 равные части.
* - Вызвать функцию MergeSort от каждой части вектора.
* - Слить первые две трети вектора с помощью алгоритма merge, сохранив результат во временный вектор с помощью back_inserter.
* - Слить временный вектор из предыдущего пункта с последней третью вектора из п. 2, 
* записав полученный отсортированный диапазон вместо исходного.
*/

#include <iostream>
#include <vector>
#include <algorithm>

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {

	if (range_end - range_begin < 2)
		return;
	
	std::vector<typename RandomIt::value_type> elements(range_begin, range_end);
	std::vector<typename RandomIt::value_type> tmpElements;

	auto endFirstPartIt = elements.begin() + (elements.end() - elements.begin()) / 3;
	auto endSecondPartIt = elements.begin() + (2 * (elements.end() - elements.begin())) / 3;

	MergeSort(elements.begin(), endFirstPartIt);
	MergeSort(endFirstPartIt, endSecondPartIt);
	MergeSort(endSecondPartIt, elements.end());


	std::merge(elements.begin(), endFirstPartIt, endFirstPartIt, endSecondPartIt, std::back_inserter(tmpElements));
	std::merge(tmpElements.begin(), tmpElements.end(), endSecondPartIt, elements.end(), range_begin);
}


int main() {
	std::vector<int> v = { 6, 4, 7, 6, 4, 4, 0, 1 };
	MergeSort(begin(v), end(v));
	for (int x : v) {
		std::cout << x << " ";
	}
	std::cout << std::endl;
	return 0;
}
