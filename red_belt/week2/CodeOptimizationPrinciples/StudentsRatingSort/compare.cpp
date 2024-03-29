/*
* В данной задаче необходимо оптимизировать код, использующийся для сортировки студентов по рейтингу. 
* Данные каждого студента находятся в структуре Student, объявленной в файле student.h. 
* Рейтинг студента записан в поле rating:
* struct Student {
*   string first_name;
*   string last_name;
*   map<string, double> marks;
*   double rating;
* 
*   bool operator < (const Student& other) const {
*     return GetName() < other.GetName();
*   }
* 
*   bool Less(const Student& other) const {
*     return rating > other.rating;
*   }
*
*   string GetName() const {
*     return first_name + " " + last_name;
*   }
* };
*
* Для сортировки студентов по рейтингу используется функция сравнения, возвращающая true, 
* если рейтинг студента first выше рейтинга студента second.
* bool Compare(Student first, Student second) {
*   return first.Less(second);
* }
* Было выявлено, что эта функция является узким местом процесса сортировки, и именно её нужно оптимизировать.
*/

#include "student.h"
#include "test_runner.h"

#include <algorithm>

using namespace std;

bool Compare(const Student& first, const Student& second) {
	return first.Less(second);
}

void TestComparison() {
	Student newbie{
	  "Ivan", "Ivanov", {
		{"c++", 1.0},
		{"algorithms", 3.0}
	  },
	  2.0
	};

	Student cpp_expert{
	  "Petr", "Petrov", {
		{"c++", 9.5},
		{"algorithms", 6.0}
	  },
	  7.75
	};

	Student guru{
	  "Sidor", "Sidorov", {
		{"c++", 10.0},
		{"algorithms", 10.0}
	  },
	  10.0
	};
	ASSERT(Compare(guru, newbie));
	ASSERT(Compare(guru, cpp_expert));
	ASSERT(!Compare(newbie, cpp_expert));
}

void TestSorting() {
	vector<Student> students{
	  {"Sidor", "Sidorov", {{"maths", 2.}}, 2.},
	  {"Semen", "Semenov", {{"maths", 4.}}, 4.},
	  {"Ivan", "Ivanov", {{"maths", 5.}}, 5.},
	  {"Petr", "Petrov", {{"maths", 3.}}, 3.},
	  {"Alexander", "Alexandrov", {{"maths", 1.}}, 1.}
	};
	sort(students.begin(), students.end(), Compare);
	ASSERT(is_sorted(students.begin(), students.end(),
		[](Student first, Student second) {
		return first.Less(second);
	})
	);
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestComparison);
	RUN_TEST(tr, TestSorting);
	return 0;
}
