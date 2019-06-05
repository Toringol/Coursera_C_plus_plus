/*
* У каждого из нас есть ежемесячные дела, каждое из которых нужно выполнять в конкретный день каждого месяца: 
* оплата счетов за электричество, абонентская плата за связь и пр. Вам нужно реализовать работу со списком таких дел, 
* а именно, обработку следующих операций:
* 
* ADD is
* Добавить дело с названием s в день i.
* 
* NEXT
* Закончить текущий месяц и начать новый. Если новый месяц имеет больше дней, чем текущий, 
* добавленные дни изначально не будут содержать дел. Если же в новом месяце меньше дней, 
* дела со всех удаляемых дней необходимо будет переместить на последний день нового месяца.
* 
* Обратите внимание, что количество команд этого типа может превышать 11.
* 
* DUMP i
* Вывести все дела в день i.
* 
* Изначально текущим месяцем считается январь. 
* Количества дней в месяцах соответствуют Григорианскому календарю с той лишь разницей, 
* что в феврале всегда 28 дней.
* 
* Формат ввода
* Сначала число операций Q, затем описания операций.
* 
* Названия дел s уникальны и состоят только из латинских букв, цифр и символов подчёркивания. 
* Номера дней i являются целыми числами и нумеруются от 1 до размера текущего месяца.
* 
* Формат вывода
* Для каждой операции типа DUMP в отдельной строке выведите количество дел в соответствующий день, 
* а затем их названия, разделяя их пробелом. Порядок вывода дел в рамках каждой операции значения не имеет.
*/

#include <iostream>
#include <vector>
#include <string>


void Add(std::vector<std::vector<std::string>>& monthAffairs, std::string affair, size_t day) {
	monthAffairs[day - 1].push_back(affair);
}

void Next(std::vector<std::vector<std::string>>& monthAffairs, const std::vector<size_t>& dayInMonth, size_t& monthNumber) {
	if (monthNumber == 11)
		monthNumber = 0;
	else {
		monthNumber++;
	}
	if (dayInMonth[monthNumber] > monthAffairs.size()) {
		monthAffairs.resize(dayInMonth[monthNumber]);
	}
	else if (dayInMonth[monthNumber] < monthAffairs.size()) {
		std::vector<std::string> deletedDays;
		while (dayInMonth[monthNumber] != monthAffairs.size()) {
			while (!(monthAffairs[monthAffairs.size() - 1].empty())) {
				deletedDays.push_back(monthAffairs[monthAffairs.size() - 1].back());
				monthAffairs[monthAffairs.size() - 1].pop_back();
			}
			monthAffairs.pop_back();
		}
		monthAffairs[monthAffairs.size() - 1].insert(monthAffairs[monthAffairs.size() - 1].end(), 
													 deletedDays.begin(), deletedDays.end());
	}
}

void Dump(const std::vector<std::vector<std::string>>& monthAffairs, size_t day) {
	std::cout << monthAffairs[day - 1].size() << " ";
	for (auto str : monthAffairs[day - 1])
		std::cout << str << " ";
	std::cout << std::endl;
}

int main() {
	size_t monthNumber = 0;
	std::vector<size_t> dayInMonth = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	std::vector<std::vector<std::string>> monthAffairs(dayInMonth[monthNumber]);
	
	size_t operationNumber;
	std::cin >> operationNumber;
	for (size_t i = 0; i < operationNumber; ++i) {
		std::string command;
		std::cin >> command;
		if (command == "ADD") {
			size_t day;
			std::string affair;
			std::cin >> day >> affair;
			Add(monthAffairs, affair, day);
		}
		else if (command == "NEXT") {
			Next(monthAffairs, dayInMonth, monthNumber);
		}
		else if (command == "DUMP") {
			size_t day;
			std::cin >> day;
			Dump(monthAffairs, day);
		}
	}

	return 0;
}
