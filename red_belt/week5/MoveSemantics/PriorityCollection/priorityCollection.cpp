/*
* Условие задачи
* Реализуйте шаблонный контейнер PriorityCollection, позволяющий хранить объекты некопируемого типа, 
* а также совершать с ними следующие операции:
*
* - добавить элемент с нулевым приоритетом;
* - добавить набор элементов с нулевыми приоритетами;
* - увеличить на 1 приоритет заданного элемента;
* - извлечь из контейнера элемент с максимальным приоритетом.
* Поскольку добавление элемента заключается в его перемещении в контейнер, 
* метод увеличения приоритета не может принимать сам элемент. 
* Поэтому метод, добавляющий элементы, для каждого из них должен вернуть некий идентификатор, 
* который затем можно использовать для вызова других методов.
*
* Тип идентификатора — PriorityCollection::Id — вы должны выбрать самостоятельно. 
* Он должен быть легко копируемым: например, числом, указателем или итератором. 
* Примеры определения и использования типа Id вы можете найти в шаблоне решения.
*
* Структура класса
* template <typename T>
* class PriorityCollection {
* public:
*   using Id = // тип, используемый для идентификаторов ;
*
*   // Добавить объект с нулевым приоритетом
*   // с помощью перемещения и вернуть его идентификатор
*   Id Add(T object);
*
*   // Добавить все элементы диапазона [range_begin, range_end)
*   // с помощью перемещения, записав выданные им идентификаторы
*   // в диапазон [ids_begin, ...)
*   template <typename ObjInputIt, typename IdOutputIt>
*   void Add(ObjInputIt range_begin, ObjInputIt range_end,
* 	  IdOutputIt ids_begin);
*
*   // Определить, принадлежит ли идентификатор какому-либо
*   // хранящемуся в контейнере объекту
*   bool IsValid(Id id) const;
*
*   // Получить объект по идентификатору
*   const T& Get(Id id) const;
*
*   // Увеличить приоритет объекта на 1
*   void Promote(Id id);
*
*   // Получить объект с максимальным приоритетом и его приоритет
*   pair<const T&, int> GetMax() const;
*
*   // Аналогично GetMax, но удаляет элемент из контейнера
*   pair<T, int> PopMax();
*
* private:
* 	// Приватные поля и методы
* };
*
* Гарантии
* - Вы можете полагаться на то, что для элементов типа T определены перемещение и сравнение на ==, != и <. 
* Все операции над элементами имеют константную сложность.
* - Гарантируется, что все добавляемые элементы различны, однако добавленный и затем извлечённый элемент может быть добавлен вновь.
* - Методы Get и Promote всегда вызываются от валидных с точки зрения метода IsValid идентификаторов.
* - Методы GetMax и PopMax вызываются только при наличии элементов в контейнере.
* - При наличии нескольких элементов с одинаковым максимальным приоритетом необходимо выбирать и извлекать тот, 
* который был добавлен позже остальных.
*
* Ограничения
* Контейнер должен обрабатывать 10^6 запросов не более чем за 1 секунду. 
* Гарантируется, что суммарная длина диапазонов, с которыми вызывается вторая версия метода Add, также не превосходит 10^6.
*/

#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <vector>

using namespace std;

template <typename T>
class PriorityCollection {
public:
	using Id = size_t;

	Id Add(T object) {
		object_collection.push_back({ move(object), 0 });
		last_id = object_collection.size() - 1;
		priority_collection.insert({ 0, last_id });
		return last_id;
	}

	template <typename ObjInputIt, typename IdOutputIt>
	void Add(ObjInputIt range_begin, ObjInputIt range_end,
		IdOutputIt ids_begin) {
		while (range_begin != range_end) {
			*ids_begin++ = Add(move(*range_begin++));
		}
	}

	bool IsValid(Id id) const {
		if (id < object_collection.size() &&
			priority_collection.find({ object_collection.at(id).second, id }) !=
			priority_collection.end())
			return true;
		return false;
	}

	const T& Get(Id id) const {
		return object_collection.at(id).first;
	}

	void Promote(Id id) {
		int last_priority = priority_collection.find(
			{ object_collection.at(id).second, id })->first;
		priority_collection.erase({ object_collection.at(id).second, id });
		++last_priority;
		priority_collection.insert({ last_priority, id });
		object_collection.at(id).second++;
	}

	pair<const T&, int> GetMax() const {
		auto max = prev(priority_collection.end());
		return pair<const T&, int>(object_collection[max->second]);
	}

	pair<T, int> PopMax() {
		auto max = prev(priority_collection.end());
		Id id = max->second;
		priority_collection.erase(max);
		return pair<T, int>(move(object_collection[id]));
	}

private:
	vector<pair<T, int>> object_collection;
	set<pair<int, Id>> priority_collection;
	Id last_id = 0;
};


class StringNonCopyable : public string {
public:
	using string::string;
	StringNonCopyable(const StringNonCopyable&) = delete;
	StringNonCopyable(StringNonCopyable&&) = default;
	StringNonCopyable& operator=(const StringNonCopyable&) = delete;
	StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

void TestNoCopy() {
	PriorityCollection<StringNonCopyable> strings;
	const auto white_id = strings.Add("white");
	const auto yellow_id = strings.Add("yellow");
	const auto red_id = strings.Add("red");

	strings.Promote(yellow_id);
	for (int i = 0; i < 2; ++i) {
		strings.Promote(red_id);
	}
	strings.Promote(yellow_id);
	{
		const auto item = strings.PopMax();
		ASSERT_EQUAL(item.first, "red");
		ASSERT_EQUAL(item.second, 2);
	}
	{
		const auto item = strings.PopMax();
		ASSERT_EQUAL(item.first, "yellow");
		ASSERT_EQUAL(item.second, 2);
	}
	{
		const auto item = strings.PopMax();
		ASSERT_EQUAL(item.first, "white");
		ASSERT_EQUAL(item.second, 0);
	}
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestNoCopy);
	return 0;
}
