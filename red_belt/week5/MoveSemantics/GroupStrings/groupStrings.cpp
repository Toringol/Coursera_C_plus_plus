/*
* Дан набор строк. Необходимо разбить их на группы, в каждой из которых все строки имеют одинаковый набор символов.
*
* Например, если даны строки law, port, top, laptop, pot, paloalto, wall, awl, нужно разбить их на 4 группы:
* - строки, состоящие только из букв a, l и w: law, wall, awl;
* - строки, состоящие только из букв o, p, r и t: port;
* - строки, состоящие только из букв o, p и t: top, pot;
* - строки, состоящие только из букв a, l, o, p, t: laptop, paloalto.
*
* Разбиение на группы должно быть реализовано в виде функции
*
* template <typename String>
* vector<Group<String>> GroupHeavyStrings(vector<String> strings);
*
* Здесь Group<String> — синоним для vector<String>:
*
* template <typename String>
* using Group = vector<String>;
*
* Наличие такого синонима позволяет записать возвращаемый тип функции GroupHeavyString
* в виде vector<Group<String>>, что читается понятнее, чем vector<vector<String>>.
*
* Слова в каждой группе должны располагаться в том же порядке, что и в исходном наборе.
* При этом порядок самих групп значения не имеет.
*
* Строка типа String не обязана состоять из символов типа char.
* Тип символа можно получить с помощью выражения typename String::value_type или Char<String>,
* если определить соответствующий синоним:
*
* template <typename String>
* using Char = typename String::value_type;
*
* Сам тип String может быть, например, обычной строкой (string) или вектором символов.
* Про тип Char<String> известно следующее:
* - Объекты этого типа можно сравнивать с помощью операторов == и <.
* - «Тяжёлыми» могут быть не только сами строки, но и отдельные символы.
* Поэтому их можно свободно перемещать,
* но скопировать каждый символ в функции можно не более одного раза
* (без учёта копирования при передаче аргумента strings по значению).
* В противном случае вы получите вердикт «неправильный ответ» с соответствующим комментарием.
*
* Ограничения
* За 1 секунду функция должна обработать максимум 100000 строк длины не более 100.
* При оценке сложности можете считать, что копирование каждого символа стоит порядка 100 элементарных операций.
*/

#include "test_runner.h"

#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <map>

using namespace std;

template <typename String>
using Group = vector<String>;

template <typename String>
using Char = typename String::value_type;

template <typename String>
vector<Group<String>> GroupHeavyStrings(vector<String> strings) {
	
	map<set<Char<String>>, vector<String>> data;
	for (auto& word : strings) {
		set<Char<String>> temp;
		for (auto& ch : word) {
			temp.insert(move(ch));
		}
		data[move(temp)].push_back(move(word));
	}

	vector<Group<String>> result_strings;
	for (auto& vector_word : data) {
		result_strings.push_back(move(vector_word.second));
	}

	return result_strings;
}


void TestGroupingABC() {
	vector<string> strings = { "caab", "abc", "cccc", "bacc", "c" };
	auto groups = GroupHeavyStrings(strings);
	ASSERT_EQUAL(groups.size(), 2);
	sort(begin(groups), end(groups));
	ASSERT_EQUAL(groups[0], vector<string>({ "caab", "abc", "bacc" }));
	ASSERT_EQUAL(groups[1], vector<string>({ "cccc", "c" }));
}

void TestGroupingReal() {
	vector<string> strings = { "law", "port", "top", "laptop", "pot", "paloalto", "wall", "awl" };
	auto groups = GroupHeavyStrings(strings);
	ASSERT_EQUAL(groups.size(), 4);
	sort(begin(groups), end(groups));
	ASSERT_EQUAL(groups[0], vector<string>({ "laptop", "paloalto" }));
	ASSERT_EQUAL(groups[1], vector<string>({ "law", "wall", "awl" }));
	ASSERT_EQUAL(groups[2], vector<string>({ "port" }));
	ASSERT_EQUAL(groups[3], vector<string>({ "top", "pot" }));
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestGroupingABC);
	RUN_TEST(tr, TestGroupingReal);
	return 0;
}
