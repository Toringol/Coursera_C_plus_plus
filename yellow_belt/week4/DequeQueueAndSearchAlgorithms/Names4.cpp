/*
* Решите задачу «Имена и фамилии — 1» более эффективно, 
* использовав двоичный поиск в методе Person::GetFullName. 
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <map>

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
private:
	std::map<int, std::string, std::greater<int>> yearNameChange;
	std::map<int, std::string, std::greater<int>> yearSurnameChange;
};

int main() {
	Person person;

	person.ChangeFirstName(1965, "Polina");
	person.ChangeLastName(1967, "Sergeeva");
	for (int year : {1900, 1965, 1990}) {
		std::cout << person.GetFullName(year) << std::endl;
	}

	person.ChangeFirstName(1970, "Appolinaria");
	for (int year : {1969, 1970}) {
		std::cout << person.GetFullName(year) << std::endl;
	}

	person.ChangeLastName(1968, "Volkova");
	for (int year : {1969, 1970}) {
		std::cout << person.GetFullName(year) << std::endl;
	}

	return 0;
}
