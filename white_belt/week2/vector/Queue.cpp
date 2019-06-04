/*
* Люди стоят в очереди, но никогда не уходят из её начала, зато могут приходить в конец и уходить оттуда. 
* Более того, иногда некоторые люди могут прекращать и начинать беспокоиться из-за того, что очередь не продвигается.
* 
* Реализуйте обработку следующих операций над очередью:
* 
* - WORRY i: пометить i-го человека с начала очереди (в нумерации с 0) как беспокоящегося;
* - QUIET i: пометить i-го человека как успокоившегося;
* - COME k: добавить k спокойных человек в конец очереди;
* - COME -k: убрать k человек из конца очереди;
* - WORRY_COUNT: узнать количество беспокоящихся людей в очереди.
* Изначально очередь пуста.
* 
* Формат ввода
* Количество операций Q, затем описания операций.
* 
* Для каждой операции WORRY i и QUIET i гарантируется, что человек с номером i существует в очереди на момент операции.
* 
* Для каждой операции COME -k гарантируется, что k не больше текущего размера очереди.
* 
* Формат вывода
* Для каждой операции WORRY_COUNT выведите одно целое число — количество беспокоящихся людей в очереди.
*/

#include <iostream>
#include <vector>
#include <string>

void worry(std::vector<bool>& peopleInQueue, size_t i) {
	peopleInQueue[i] = true;
}

void quiet(std::vector<bool>& peopleInQueue, size_t i) {
	peopleInQueue[i] = false;
}

void come(std::vector<bool>& peopleInQueue, int i) {
	if (i > 0) {
		for (int j = 0; j < i; ++j)
			peopleInQueue.push_back(false);
	}
	else {
		for (int j = 0; j > i; --j)
			peopleInQueue.pop_back();
	}
}

size_t worry_count(const std::vector<bool>& peopleInQueue) {
	size_t result = 0;
	for (auto person : peopleInQueue)
		if (person == true)
			result++;
	return result;
}

int main() {
	size_t operationNumber;
	std::cin >> operationNumber;
	std::vector<bool> peopleInQueue;

	for (size_t i = 0; i < operationNumber; ++i) {
		std::string str;
		int value;
		std::cin >> str;
		if (str == "WORRY") {
			std::cin >> value;
			worry(peopleInQueue, value);
		}
		else if (str == "QUIET") {
			std::cin >> value;
			quiet(peopleInQueue, value);
		}
		else if (str == "COME") {
			std::cin >> value;
			come(peopleInQueue, value);
		}
		else if (str == "WORRY_COUNT")
			std::cout << worry_count(peopleInQueue) << std::endl;
	}

	return 0;
}
