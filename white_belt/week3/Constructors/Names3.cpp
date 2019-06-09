/*
* Дополните класс Person из задачи «Имена и фамилии — 2» конструктором, 
* позволяющим задать имя и фамилию человека при рождении, а также сам год рождения. 
* Класс не должен иметь конструктора по умолчанию.
* 
* При получении на вход года, который меньше года рождения:
* 
* - методы GetFullName и GetFullNameWithHistory должны отдавать "No person";
* - методы ChangeFirstName и ChangeLastName должны игнорировать запрос.
* Кроме того, необходимо объявить константными все методы, которые по сути ими являются.
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <vector>

std::vector<std::string> CreateVec(const std::map<int, std::string, std::greater<int>>& map,
								   const size_t& year) {
	auto iter = map.lower_bound(year);
	std::vector<std::string> vec;
	while (iter != map.end()) {
		vec.push_back(iter->second);
		++iter;
	}
	return vec;
}

void DeleteDublicatesVec(std::vector<std::string>& vec) {
	auto last = std::unique(vec.begin(), vec.end());
	vec.erase(last, vec.end());
	vec.erase(vec.begin());
}

std::string CreateStringFromVec(std::vector<std::string>& vec) {
	std::string strResult;
	if (!vec.empty()) {
		strResult += " (";
		for (size_t i = 0; i < vec.size(); ++i) {
			strResult += vec[i];
			size_t tempComp = i + 1;
			if (tempComp != (vec.size()))
				strResult += ", ";
		}
		strResult += ")";
	}
	return strResult;
}

class Person {
public:
	Person(const std::string& name, const std::string& secondName, const int& year) {
		birthYear = year;
		ChangeFirstName(year, name);
		ChangeLastName(year, secondName);
	}

	void ChangeFirstName(int year, const std::string& first_name) {
		if (year < birthYear) {
			return;
		}
		yearNameChange[year] = first_name;
	}

	void ChangeLastName(int year, const std::string& last_name) {
		if (year < birthYear) {
			return;
		}
		yearSurnameChange[year] = last_name;
	}

	std::string GetFullName(int year) const {
		if (year < birthYear) {
			return "No person";
		}
		auto itNameChange = yearNameChange.lower_bound(year);
		auto itSurnameChange = yearSurnameChange.lower_bound(year);
		if ((itNameChange == yearNameChange.end()) && (itSurnameChange == yearSurnameChange.end())) {
			std::string result = "Incognito";
			return result;
		}
		else if ((itNameChange == yearNameChange.end()) && !(itSurnameChange == yearSurnameChange.end())) {
			std::string result;
			result += itSurnameChange->second + " with unknown first name";
			return result;
		}
		else if (!(itNameChange == yearNameChange.end()) && (itSurnameChange == yearSurnameChange.end())) {
			std::string result;
			result += itNameChange->second + " with unknown last name";
			return result;
		}
		else {
			std::string result;
			result += itNameChange->second + " " + itSurnameChange->second;
			return result;
		}
	}

	std::string GetFullNameWithHistory(int year) const {
		if (year < birthYear) {
			return "No person";
		}
		auto itNameChange = yearNameChange.lower_bound(year);
		auto itSurnameChange = yearSurnameChange.lower_bound(year);
		if ((itNameChange == yearNameChange.end()) && (itSurnameChange == yearSurnameChange.end())) {
			std::string result = "Incognito";
			return result;
		}
		else if ((itNameChange == yearNameChange.end()) && !(itSurnameChange == yearSurnameChange.end())) {
			std::string result;
			result += itSurnameChange->second;
			std::vector<std::string> prevSurnames = CreateVec(yearSurnameChange, year);
			DeleteDublicatesVec(prevSurnames);
			result += CreateStringFromVec(prevSurnames);
			result += " with unknown first name";
			return result;
		}
		else if (!(itNameChange == yearNameChange.end()) && (itSurnameChange == yearSurnameChange.end())) {
			std::string result;
			result += itNameChange->second;
			std::vector<std::string> prevNamesVec = CreateVec(yearNameChange, year);
			DeleteDublicatesVec(prevNamesVec);
			result += CreateStringFromVec(prevNamesVec);
			result += " with unknown last name";
			return result;
		}
		else {
			std::string result;
			result += itNameChange->second;
			std::vector<std::string> prevNamesVec = CreateVec(yearNameChange, year);
			DeleteDublicatesVec(prevNamesVec);
			result += CreateStringFromVec(prevNamesVec);
			result += " ";
			result += itSurnameChange->second;
			std::vector<std::string> prevSurnames = CreateVec(yearSurnameChange, year);
			DeleteDublicatesVec(prevSurnames);
			result += CreateStringFromVec(prevSurnames);
			return result;
		}
	}

private:
	std::map<int, std::string, std::greater<int>> yearNameChange;
	std::map<int, std::string, std::greater<int>> yearSurnameChange;
	size_t birthYear;
};


int main() {
	Person person("Polina", "Sergeeva", 1960);
	for (int year : {1959, 1960}) {
		std::cout << person.GetFullNameWithHistory(year) << std::endl;
	}

	person.ChangeFirstName(1965, "Appolinaria");
	person.ChangeLastName(1967, "Ivanova");
	for (int year : {1965, 1967}) {
		std::cout << person.GetFullNameWithHistory(year) << std::endl;
	}

	return 0;
}
