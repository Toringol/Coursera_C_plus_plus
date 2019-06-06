/*
* Реализуйте систему хранения автобусных маршрутов. Вам нужно обрабатывать следующие запросы:
*
* - NEW_BUS bus stop_count stop1 stop2 ... — добавить маршрут автобуса с названием bus и 
* stop_count остановками с названиями stop1, stop2, ...
* - BUSES_FOR_STOP stop — вывести названия всех маршрутов автобуса, проходящих через остановку stop.
* - STOPS_FOR_BUS bus — вывести названия всех остановок маршрута bus со списком автобусов, 
* на которые можно пересесть на каждой из остановок.
* - ALL_BUSES — вывести список всех маршрутов с остановками.
* Формат ввода
* В первой строке ввода содержится количество запросов Q, затем в Q строках следуют описания запросов.
*
* Гарантируется, что все названия маршрутов и остановок состоят лишь из латинских букв, цифр и знаков подчёркивания.
* 
* Для каждого запроса NEW_BUS bus stop_count stop1 stop2 ... гарантируется, что маршрут bus отсутствует, 
* количество остановок больше 0, а после числа stop_count следует именно такое количество названий остановок, 
* причём все названия в каждом списке различны.
*
* Формат вывода
* Для каждого запроса, кроме NEW_BUS, выведите соответствующий ответ на него:
* 
* - На запрос BUSES_FOR_STOP stop выведите через пробел список автобусов, проезжающих через эту остановку, 
* в том порядке, в котором они создавались командами NEW_BUS. Если остановка stop не существует, выведите No stop.
* - На запрос STOPS_FOR_BUS bus выведите описания остановок маршрута bus в отдельных строках в том порядке, 
* в котором они были заданы в соответствующей команде NEW_BUS. 
* Описание каждой остановки stop должно иметь вид Stop stop: bus1 bus2 ..., где bus1 bus2 ... — список автобусов, 
* проезжающих через остановку stop, в порядке, в котором они создавались командами NEW_BUS, 
* за исключением исходного маршрута bus. Если через остановку stop не проезжает ни один автобус, 
* кроме bus, вместо списка автобусов для неё выведите no interchange. Если маршрут bus не существует, выведите No bus.
* - На запрос ALL_BUSES выведите описания всех автобусов в алфавитном порядке. 
* Описание каждого маршрута bus должно иметь вид Bus bus: stop1 stop2 ..., 
* где stop1 stop2 ... — список остановок автобуса bus в порядке, 
* в котором они были заданы в соответствующей команде NEW_BUS. Если автобусы отсутствуют, выведите No buses.
* Предупреждение
* Условие задачи выше содержит много важных деталей. Если вы не уверены в том, что не упустили ни одной, перечитайте условие ещё раз.
*/

#include <iostream>
#include <map>
#include <string>
#include <vector>

void NewBus(std::map<std::string, std::vector<std::string>>& busStops, 
			std::map<std::string, std::vector<std::string>>& stopBuses,
			const std::string& bus, const std::vector<std::string>& stops) {
	for (const auto& stop : stops) {
		busStops[bus].push_back(stop);
		stopBuses[stop].push_back(bus);
	}
}

void BusesForStop(const std::map<std::string, std::vector<std::string>>& stopBuses, 
				  const std::string& stop) {
	if (stopBuses.count(stop)) {
		for (const auto& value : stopBuses.find(stop)->second)
			std::cout << value << " ";
		std::cout << std::endl;
	}
	else {
		std::cout << "No stop" << std::endl;
	}
}

void StopsForBus(std::map<std::string, std::vector<std::string>>& busStops,
				 std::map<std::string, std::vector<std::string>>& stopBuses,
				 const std::string& bus) {
	if (busStops.count(bus)) {
		for (const auto& value : busStops.find(bus)->second) {
			std::cout << "Stop " << value << ": ";
			if (stopBuses.find(value)->second.size() == 1) {
				std::cout << "no interchange" << std::endl;
				continue;
			}
			for (const auto& buses : stopBuses.find(value)->second) {
				if (buses != bus)
					std::cout << buses << " ";
			}
			std::cout << std::endl;
		}
	}
	else {
		std::cout << "No bus" << std::endl;
	}
}

void AllBuses(const std::map<std::string, std::vector<std::string>>& busStops) {
	if (busStops.empty()) {
		std::cout << "No buses";
	}
	else {
		for (const auto& item : busStops) {
			std::cout << "Bus " << item.first << ": ";
			for (const auto& str : item.second)
				std::cout << str << " ";
			std::cout << std::endl;
		}
	}
	std::cout << std::endl;
}


int main() {
	std::map<std::string, std::vector<std::string>> busStop;
	std::map<std::string, std::vector<std::string>> stopBus;

	size_t operationsNumber;
	std::cin >> operationsNumber;

	for (size_t i = 0; i < operationsNumber; ++i) {
		std::string operationCode;
		std::cin >> operationCode;
		if (operationCode == "NEW_BUS") {
			std::vector<std::string> strVec;
			std::string bus;
			size_t stopCount;
			std::cin >> bus >> stopCount;
			for (size_t i = 0; i < stopCount; ++i) {
				std::string stop;
				std::cin >> stop;
				strVec.push_back(stop);
			}
			NewBus(busStop, stopBus, bus, strVec);
		}
		else if (operationCode == "BUSES_FOR_STOP") {
			std::string stop;
			std::cin >> stop;
			BusesForStop(stopBus, stop);
		}
		else if (operationCode == "STOPS_FOR_BUS") {
			std::string bus;
			std::cin >> bus;
			StopsForBus(busStop, stopBus, bus);
		}
		else if (operationCode == "ALL_BUSES") {
			AllBuses(busStop);
		}
	}

	return 0;
}
