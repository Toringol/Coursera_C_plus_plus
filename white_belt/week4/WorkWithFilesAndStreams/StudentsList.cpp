/*
* Определите структуру «Студент» со следующими полями: имя, фамилия, день, месяц и год рождения. 
* Создайте вектор из таких структур, заполните его из входных данных и затем по запросам выведите нужные поля.
* 
* Формат ввода
* 
* Первая строка содержит одно целое число N от 0 до 10000 — число студентов.
* 
* Далее идут N строк, каждая из которых содержит две строки длиной от 1 до 15 символов — 
* имя и фамилию очередного студента, и три целых числа от 0 до 1000000000 — день, месяц и год рождения.
* 
* Следующая строка содержит одно целое число M от 0 до 10000 — число запросов.
* 
* Следующие M строк содержат строку длиной от 1 до 15 символов — запрос, 
* и целое число от 0 до 1000000000 — номер студента (нумерация начинается с 1).
* 
* Формат вывода
* 
* Для запроса вида name K, где K от 1 до N, выведите через пробел имя и фамилию K-го студента.
* 
* Для запроса вида date K, где K от 1 до N, выведите через точку день, месяц и год рождения K-го студента.
* 
* Для остальных запросов выведите bad request.
*/


#include <iostream>
#include <string>
#include <vector>

struct Student {
	std::string name;
	std::string surname;
	size_t birthDay;
	size_t birthMonth;
	size_t birthYear;
};

void FillVector(std::vector<Student>& students, const size_t& studentsNumber) {
	for (size_t i = 0; i < studentsNumber; ++i) {
		std::string name;
		std::string surname;
		size_t birthDay = 0;
		size_t birthMonth = 0;
		size_t birthYear = 0;
		std::cin >> name >> surname >> birthDay >> birthMonth >> birthYear;
		students.push_back({ name, surname, birthDay, birthMonth, birthYear });
	}
}

std::string MakeOperation(const std::vector<Student>& students, const std::string& operationName,
				   const size_t& studentNumber) {
	if (studentNumber >= students.size() || (operationName != "name" &&
		operationName != "date"))
		return "bad request";
	if (operationName == "name") {
		std::string result;
		result = students[studentNumber].name + " " + students[studentNumber].surname;
		return result;
	}
	else {
		std::string result;
		result += std::to_string(students[studentNumber].birthDay);
		result += ".";
		result += std::to_string(students[studentNumber].birthMonth);
		result += ".";
		result += std::to_string(students[studentNumber].birthYear);
		return result;
	}
}

int main() {
	std::vector<Student> students;

	size_t studentsNumber = 0;
	std::cin >> studentsNumber;

	FillVector(students, studentsNumber);

	size_t operationsNumber = 0;
	std::cin >> operationsNumber;

	for (size_t i = 0; i < operationsNumber; ++i) {
		std::string operationName;
		size_t studentNumber;
		std::cin >> operationName >> studentNumber;
		studentNumber--;
		std::cout << MakeOperation(students, operationName, studentNumber) << std::endl;
	}

	return 0;
}
