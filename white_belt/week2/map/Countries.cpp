/*
* Реализуйте справочник столиц стран.
*
* На вход программе поступают следующие запросы:
*
* CHANGE_CAPITAL country new_capital — изменение столицы страны country на new_capital, 
* либо добавление такой страны с такой столицей, если раньше её не было.
* RENAME old_country_name new_country_name — переименование страны из old_country_name в new_country_name.
* ABOUT country — вывод столицы страны country.
* DUMP — вывод столиц всех стран.
* Формат ввода
* В первой строке содержится количество запросов Q, в следующих Q строках — описания запросов. 
* Все названия стран и столиц состоят лишь из латинских букв, цифр и символов подчёркивания.
* 
* Формат вывода
* Выведите результат обработки каждого запроса:

* В ответ на запрос CHANGE_CAPITAL country new_capital выведите
* - Introduce new country country with capital new_capital, если страны country раньше не существовало;
* - Country country hasn't changed its capital, если страна country до текущего момента имела столицу new_capital;
* - Country country has changed its capital from old_capital to new_capital, если страна country 
* до текущего момента имела столицу old_capital, название которой не совпадает с названием new_capital.
* В ответ на запрос RENAME old_country_name new_country_name выведите
* - Incorrect rename, skip, если новое название страны совпадает со старым, 
* страна old_country_name не существует или страна new_country_name уже существует;
* - Country old_country_name with capital capital has been renamed to new_country_name, 
* если запрос корректен и страна имеет столицу capital.
* В ответ на запрос ABOUT country выведите
* - Country country doesn't exist, если страны с названием country не существует;
* - Country country has capital capital, если страна country существует и имеет столицу capital.
* В ответ на запрос DUMP выведите
* - There are no countries in the world, если пока не было добавлено ни одной страны;
* разделённые пробелами пары country/capital, описывающие столицы всех стран и упорядоченные по названию страны, 
* если в мире уже есть хотя бы одна страна.
*/

#include <iostream>
#include <map>
#include <string>

void ChangeCapital(std::map<std::string, std::string>& countryCapitals, const std::string& country, const std::string& newCapital) {
	if (!countryCapitals.count(country)) {
		countryCapitals[country] = newCapital;
		std::cout << "Introduce new country " << country << " with capital " << newCapital << std::endl;
	}
	else if (countryCapitals.count(country) && (countryCapitals.find(country)->second == newCapital)) {
		std::cout << "Country " << country << " hasn't changed its capital" << std::endl;
	}
	else if (countryCapitals.count(country) && (!(countryCapitals.find(country)->second == newCapital))) {
		std::string oldCapital = countryCapitals.find(country)->second;
		countryCapitals.erase(country);
		countryCapitals[country] = newCapital;
		std::cout << "Country " << country << " has changed its capital from " << oldCapital << " to " << newCapital << std::endl;
	}
}

void Rename(std::map<std::string, std::string>& countryCapitals, const std::string& oldCountryName, const std::string& newCountryName) {
	if ((oldCountryName == newCountryName) || !(countryCapitals.count(oldCountryName))
		|| countryCapitals.count(newCountryName)) {
		std::cout << "Incorrect rename, skip" << std::endl;
	}
	else {
		countryCapitals[newCountryName] = countryCapitals.find(oldCountryName)->second;
		countryCapitals.erase(oldCountryName);
		std::cout << "Country " << oldCountryName << " with capital " << countryCapitals.find(newCountryName)->second
				  << " has been renamed to " << newCountryName << std::endl;
	}
}

void About(const std::map<std::string, std::string>& countryCapitals, const std::string& country) {
	if (countryCapitals.count(country)) {
		std::cout << "Country " << country << " has capital "  << countryCapitals.find(country)->second << std::endl;
	}
	else {
		std::cout << "Country " << country << " doesn't exist" << std::endl;
	}
}

void Dump(const std::map<std::string, std::string>& countryCapitals) {
	if (countryCapitals.empty())
		std::cout << "There are no countries in the world";
	else {
		for (const auto& item : countryCapitals) {
			std::cout << item.first << "/" << item.second << " ";
		}
	}
	std::cout << std::endl;
}

int main() {
	std::map<std::string, std::string> countryCapitals;

	size_t operationsNumber;
	std::cin >> operationsNumber;

	for (size_t i = 0; i < operationsNumber; ++i) {
		std::string operationCode;
		std::cin >> operationCode;
		if (operationCode == "CHANGE_CAPITAL") {
			std::string country, newCapital;
			std::cin >> country >> newCapital;
			ChangeCapital(countryCapitals, country, newCapital);
		}
		else if (operationCode == "RENAME") {
			std::string oldCountryName, newCountryName;
			std::cin >> oldCountryName >> newCountryName;
			Rename(countryCapitals, oldCountryName, newCountryName);
		}
		else if (operationCode == "ABOUT") {
			std::string country;
			std::cin >> country;
			About(countryCapitals, country);
		}
		else if (operationCode == "DUMP") {
			Dump(countryCapitals);
		}
	}

	return 0;
}
