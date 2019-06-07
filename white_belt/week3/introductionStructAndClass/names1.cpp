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
