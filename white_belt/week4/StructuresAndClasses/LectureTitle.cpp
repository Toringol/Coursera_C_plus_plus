/*
* Дана структура LectureTitle:
* struct LectureTitle {
* string specialization;
* string course;
* string week;
* };
*
* Допишите конструктор и структуры Specialization, Course, Week так, 
* чтобы объект LectureTitle можно было создать с помощью кода
*
* LectureTitle title(
*	Specialization("C++"),
*	Course("White belt"),
*	Week("4th")
* );
*
* но нельзя было с помощью следующих фрагментов кода:
*
* LectureTitle title("C++", "White belt", "4th");
* 
* LectureTitle title(string("C++"), string("White belt"), string("4th"));
* 
* LectureTitle title = {"C++", "White belt", "4th"};
* 
* LectureTitle title = {{"C++"}, {"White belt"}, {"4th"}};
* 
* LectureTitle title(
*   Course("White belt"),
*   Specialization("C++"),
*   Week("4th")
* );
* LectureTitle title(
*   Specialization("C++"),
*   Week("4th"),
*   Course("White belt")
* );
*/

#include <string>

struct Specialization {
	explicit Specialization(const std::string& s) { specialization = s; };
	std::string specialization;
};

struct Course {
	explicit Course(const std::string& c) { course = c; };
	std::string course;
};

struct Week {
	explicit Week(const std::string& w) { week = w; };
	std::string week;
};

struct LectureTitle {
	LectureTitle(const Specialization& s,
		const Course& c,
		const Week& w) {
		specialization = s.specialization;
		course = c.course;
		week = w.week;
	};
	std::string specialization;
	std::string course;
	std::string week;
};


int main() {

	LectureTitle title(
		Specialization("C++"),
		Course("White belt"),
		Week("4th")
	);

	return 0;
}
