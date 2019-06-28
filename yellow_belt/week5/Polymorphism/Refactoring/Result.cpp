/*
* В данном задании вам предстоит изменить код таким образом, чтобы он соответствовал изложенным в курсе принципам.
*
* Представьте, что этот код вам достался в наследство от коллеги и теперь вам предстоит поддерживать его и улучшать. 
* Первое, что вы решили сделать — это провести рефакторинг.
*
* Конечные цели рефакторинга:
*
* - упростить дальнейшую поддержку кода;
* - уменьшить сложность кода;
* - упростить добавление новых абстракций в программу.
* 
* Задание будет оцениваться по следующим критериям:
*
* - эффективность выполнения кода;
* - задублированность кода;
* - эффективность использования приёмов рефакторинга кода, показанных в лекциях.
* Кроме того, присылаемый вами код должен компилироваться.
*/


#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Person {
public:
	Person(const string& type, const string& name) :
		type_(type), name_(name) {}

	virtual ~Person() = default;

	virtual void Walk(const string& destination) {
		cout << Log() << " walks to: " << destination << endl;
	}

	string Log() const {
		return (type_ + ": " + name_);
	}

	void DoAction(const string& action) const {
		cout << type_ << ": " << name_ << " " << action << endl;
	}

	string name() const { return name_; };
	string type() const { return type_; };

private:
	const string type_;
	const string name_;
};


class Student : public Person {
public:
	Student(const string& name, const string& favouriteSong) : 
		Person("Student", name), FavouriteSong(favouriteSong) {}

	void Learn() {
		DoAction("learns");
	}

	void Walk(const string& destination) override {
		Person::Walk(destination);
		SingSong();
	}

	void SingSong() {
		DoAction("sings a song: " + FavouriteSong);
	}

private:
	const string FavouriteSong;
};


class Teacher : public Person {
public:
	Teacher(const string& name, const string& subject) :
		Person("Teacher", name), Subject(subject) {}

	void Teach() {
		DoAction("teaches: " + Subject);
	}

private:
	const string Subject;
};


class Policeman : public Person {
public:
	Policeman(const string& name) : 
		Person("Policeman", name) {}

	void Check(const Person& p) {
		DoAction("checks " + p.type() + ". "
			+ p.type() + "'s name is: " + p.name());
	}
};

void VisitPlaces(Person& person, const vector<string>& places) {
	for (const auto& p : places) {
		person.Walk(p);
	}
}


int main() {
	Teacher t("Jim", "Math");
	Student s("Ann", "We will rock you");
	Policeman p("Bob");

	VisitPlaces(t, { "Moscow", "London" });
	p.Check(s);
	VisitPlaces(s, { "Moscow", "London" });
	return 0;
}
