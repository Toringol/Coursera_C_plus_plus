/*
* Реализуйте шаблонную функцию Sqr, которая работает не только для чисел, но и для контейнеров. 
* Функция должна возвращать копию исходного контейнера, модифицировав его следующим образом:
*
* - для vector элементы нужно возвести в квадрат;
* - для map в квадрат нужно возвести только значения, но не ключи;
* - для pair в квадрат нужно возвести каждый элемент пары.
* Функция должна корректно работать не только для контейнеров, состоящих из чисел, 
* но и для составных объектов, например, векторов словарей пар чисел.
*
* Для успешной сдачи решения необходимо сделать предварительное объявление шаблонных функций перед всеми шаблонными функциями.
*/

#include <iostream>
#include <vector>
#include <map>

template <class T> T Sqr(const T& t);
template <class First, class Second> std::pair<First, Second> Sqr(const std::pair<First, Second>& t);
template <class T> std::vector<T> Sqr(const std::vector<T>& t);
template <class Key, class Value> std::map<Key, Value> Sqr(const std::map<Key, Value>& t);
template <class First, class Second> std::pair<First, Second> operator* (const std::pair<First, Second>& lhs, 
																		 const std::pair<First, Second>& rhs);
template <class T> std::vector<T> operator* (const std::vector<T>& lhs, const std::vector<T>& rhs);
template <class Key, class Value> std::map<Key, Value> operator * (const std::map<Key, Value>& lhs, const std::map<Key, Value>& rhs);

template <class T>
T Sqr(const T& t) {
	return t * t;
}

template <typename T>
std::vector<T> operator * (const std::vector<T>& lhs, const std::vector<T>& rhs) {
	std::vector<T> result;
	for (const auto& value : lhs)
		result.push_back(Sqr(value));
	return result;
}

template <typename First, typename Second>
std::pair<First, Second> operator * (const std::pair<First, Second>& lhs, const std::pair<First, Second>& rhs) {
	First f = lhs.first * rhs.first;
	Second s = lhs.second * rhs.second;
	return std::make_pair(f, s);
}

template <typename Key, typename Value>
std::map<Key, Value> operator * (const std::map<Key, Value>& lhs, const std::map<Key, Value>& rhs) {
	std::map<Key, Value> result;
	for (const auto& item : lhs) {
		result[item.first] = (item.second * item.second);
	}
	return result;
}

template <typename T>
std::vector<T> Sqr(const std::vector<T>& t) {
	return t * t;
}

template <typename Key, typename Value>
std::map<Key, Value> Sqr(const std::map<Key, Value>& t) {
	return t * t;
}

template <typename First, typename Second>
std::pair<First, Second> Sqr(const std::pair<First, Second>& t) {
	return t * t;
}

template <typename Key, typename ValueFirst, typename ValueSecond>
std::map<Key, std::pair<ValueFirst, ValueSecond>> Sqr(const std::map<Key, std::pair<ValueFirst, ValueSecond>>& t) {
	return t * t;
}

int main() {
	std::vector<double> v = { 1.5, 2.4, 3.0 };
	std::cout << "vector:";
	for (double x : Sqr(v)) {
		std::cout << ' ' << x;
	}
	std::cout << std::endl;

	std::map<int, std::pair<int, int>> map_of_pairs = {
	  {4, {2, 2}},
	  {7, {4, 3}}
	};
	std::cout << "map of pairs:" << std::endl;
	for (const auto& x : Sqr(map_of_pairs)) {
		std::cout << x.first << ' ' << x.second.first << ' ' << x.second.second << std::endl;
	}

	return 0;
}
