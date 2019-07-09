/*
* Предисловие
* Если вы не уверены, стоит ли вам сначала пройти более ранние наши курсы, 
* или у вас достаточно знаний, чтобы начать с «Красного пояса», 
* попробуйте решить эту задачу.Если вы не понимаете её условие или не можете быстро решить, 
* скорее всего, вам надо сначала пройти «Жёлтый пояс»
*
* Условие задачи
* Реализуйте шаблонную функцию
*
* template<typename ForwardIterator, typename UnaryPredicate>
* ForwardIterator max_element_if(
* ForwardIterator first, ForwardIterator last, UnaryPredicate pred);
*
* возвращающую итератор на максимальный элемент в диапазоне [first, last), 
* для которого предикат pred возвращает true. 
* Если диапазон содержит несколько подходящих элементов с максимальным значением, 
* то результатом будет первое вхождение такого элемента. Если диапазон не содержит подходящих элементов, 
* то функция должна вернуть last.
*
* Гарантируется, что:
* - pred принимает аргумент того типа, который имеют элементы диапазона
* - для ForwardIterator определены операторы ++, ==, !=, * (разыменование)
* - для типа, на который указывает итератор, определён оператор < («меньше»)
*
*/

#include <string>
#include <vector>
#include <list>
#include <forward_list>
#include <numeric>
#include <iterator>
#include <algorithm>

#include "test_runner.h"

using namespace std;

template<typename ForwardIterator, typename UnaryPredicate>
ForwardIterator max_element_if(ForwardIterator first, ForwardIterator last, UnaryPredicate pred) {
	auto maxElemIt = std::find_if(first, last, pred);
	if (maxElemIt == last) {
		return maxElemIt;
	}
	auto startIt = maxElemIt;
	for (ForwardIterator currentElemIt = ++startIt; currentElemIt != last; ++currentElemIt) {
		if ((*maxElemIt) < (*currentElemIt) && pred(*currentElemIt)) {
			maxElemIt = currentElemIt;
		}
	}
	return maxElemIt;
}

void TestUniqueMax() {
	auto IsEven = [](int x) {
		return x % 2 == 0;
	};

	const list<int> hill{ 2, 4, 8, 9, 6, 4, 2 };
	auto max_iterator = hill.begin();
	advance(max_iterator, 2);

	vector<int> numbers(10);
	iota(numbers.begin(), numbers.end(), 1);

	Assert(
		max_element_if(numbers.begin(), numbers.end(), IsEven) == --numbers.end(),
		"Expect the last element"
	);
	Assert(
		max_element_if(hill.begin(), hill.end(), IsEven) == max_iterator,
		"Expect the maximal even number"
	);
}

void TestSeveralMax() {
	struct IsCapitalized {
		bool operator()(const string &s) {
			return !s.empty() && isupper(s.front());
		}
	};

	const forward_list<string> text{ "One", "two", "Three", "One", "Two",
	  "Three", "one", "Two", "three" };
	auto max_iterator = text.begin();
	advance(max_iterator, 4);

	Assert(
		max_element_if(text.begin(), text.end(), IsCapitalized()) == max_iterator,
		"Expect thr first \"Two\""
	);
}

void TestNoMax() {
	const vector<int> empty;
	const string str = "Non-empty string";

	auto AlwaysTrue = [](int) {
		return true;
	};
	Assert(
		max_element_if(empty.begin(), empty.end(), AlwaysTrue) == empty.end(),
		"Expect end for empty container"
	);

	auto AlwaysFalse = [](char) {
		return false;
	};
	Assert(
		max_element_if(str.begin(), str.end(), AlwaysFalse) == str.end(),
		"Expect end for AlwaysFalse predicate"
	);
}

int main() {
	TestRunner tr;
	tr.RunTest(TestUniqueMax, "TestUniqueMax");
	tr.RunTest(TestSeveralMax, "TestSeveralMax");
	tr.RunTest(TestNoMax, "TestNoMax");
	return 0;
}
