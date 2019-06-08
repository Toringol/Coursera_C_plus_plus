/*
* Реализуйте класс для человека, поддерживающий историю изменений человеком своих фамилии и имени.
* class Person {
* public:
*   void ChangeFirstName(int year, const string& first_name) {
*     // добавить факт изменения имени на first_name в год year
*   }
*   void ChangeLastName(int year, const string& last_name) {
*     // добавить факт изменения фамилии на last_name в год year
*   }
*   string GetFullName(int year) {
*     // получить имя и фамилию по состоянию на конец года year
*   }
* private:
*   // приватные поля
* };
* Считайте, что в каждый год может произойти не более одного изменения фамилии 
* и не более одного изменения имени. 
* При этом с течением времени могут открываться всё новые факты из прошлого человека, 
* поэтому года́ в последовательных вызовах методов ChangeLastName и ChangeFirstName не обязаны возрастать.
* 
* Гарантируется, что все имена и фамилии непусты.
* 
* Строка, возвращаемая методом GetFullName, должна содержать разделённые одним пробелом имя и 
* фамилию человека по состоянию на конец данного года.
* 
* - Если к данному году не случилось ни одного изменения фамилии и имени, верните строку "Incognito".
* - Если к данному году случилось изменение фамилии, 
* но не было ни одного изменения имени, верните "last_name with unknown first name".
* - Если к данному году случилось изменение имени, но не было ни одного изменения фамилии, 
* верните "first_name with unknown last name".
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <vector>

std::vector<std::string> CreateVec(std::map<int, std::string>::iterator& iter, 
								   std::map<int, std::string, std::greater<int>>& map) {
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

	void ChangeFirstName(int year, const std::string& first_name) {
		yearNameChange[year] = first_name;
	}
	
	void ChangeLastName(int year, const std::string& last_name) {
		yearSurnameChange[year] = last_name;
	}
	
	std::string GetFullName(int year) {
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

	std::string GetFullNameWithHistory(int year) {
		auto itNameChange = yearNameChange.lower_bound(year);
		auto itSurnameChange = yearSurnameChange.lower_bound(year);
		if ((itNameChange == yearNameChange.end()) && (itSurnameChange == yearSurnameChange.end())) {
			std::string result = "Incognito";
			return result;
		}
		else if ((itNameChange == yearNameChange.end()) && !(itSurnameChange == yearSurnameChange.end())) {
			std::string result;
			result += itSurnameChange->second;
			std::vector<std::string> prevSurnames = CreateVec(itSurnameChange, yearSurnameChange);
			DeleteDublicatesVec(prevSurnames);
			result += CreateStringFromVec(prevSurnames);
			result += " with unknown first name";
			return result;
		}
		else if (!(itNameChange == yearNameChange.end()) && (itSurnameChange == yearSurnameChange.end())) {
			std::string result;
			result += itNameChange->second;
			std::vector<std::string> prevNamesVec = CreateVec(itNameChange, yearNameChange);
			DeleteDublicatesVec(prevNamesVec);
			result += CreateStringFromVec(prevNamesVec);
			result += " with unknown last name";
			return result;
		}
		else {
			std::string result;
			result += itNameChange->second;
			std::vector<std::string> prevNamesVec = CreateVec(itNameChange, yearNameChange);
			DeleteDublicatesVec(prevNamesVec);
			result += CreateStringFromVec(prevNamesVec);
			result += " ";
			result += itSurnameChange->second;
			std::vector<std::string> prevSurnames = CreateVec(itSurnameChange, yearSurnameChange);
			DeleteDublicatesVec(prevSurnames);
			result += CreateStringFromVec(prevSurnames);
			return result;
		}
	}

private:
	std::map<int, std::string, std::greater<int>> yearNameChange;
	std::map<int, std::string, std::greater<int>> yearSurnameChange;
};



int main() {
	Person person;

	person.ChangeFirstName(1965, "Polina");
	person.ChangeLastName(1967, "Sergeeva");
	for (int year : {1900, 1965, 1990}) {
		std::cout << person.GetFullNameWithHistory(year) << std::endl;
	}

	person.ChangeFirstName(1970, "Appolinaria");
	for (int year : {1969, 1970}) {
		std::cout << person.GetFullNameWithHistory(year) << std::endl;
	}

	person.ChangeLastName(1968, "Volkova");
	for (int year : {1969, 1970}) {
		std::cout << person.GetFullNameWithHistory(year) << std::endl;
	}

	person.ChangeFirstName(1990, "Polina");
	person.ChangeLastName(1990, "Volkova-Sergeeva");
	std::cout << person.GetFullNameWithHistory(1990) << std::endl;

	person.ChangeFirstName(1966, "Pauline");
	std::cout << person.GetFullNameWithHistory(1966) << std::endl;

	person.ChangeLastName(1960, "Sergeeva");
	for (int year : {1960, 1967}) {
		std::cout << person.GetFullNameWithHistory(year) << std::endl;
	}

	person.ChangeLastName(1961, "Ivanova");
	std::cout << person.GetFullNameWithHistory(1967) << std::endl;

	return 0;
}
