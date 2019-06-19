/*
* В первом курсе «Белый пояс по С++» у нас была задача «Имена и фамилии — 1». 
* В ней надо было разработать класс Person, поддерживающий историю изменений человеком своих фамилии и имени. 
* В данной задаче вам надо разработать юнит-тесты на реализацию класса Person. 
* При разработке тестов учитывайте ограничения, которые накладывает на класс Person условие задачи «Имена и фамилии — 1».
*
* Начать работу вы можете с шаблона, который содержит наш фреймворк юнит-тестов и заготовку класса.
*/

#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
	os << "{";
	bool first = true;
	for (const auto& x : s) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << x;
	}
	return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
	os << "{";
	bool first = true;
	for (const auto& x : s) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << x;
	}
	return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
	os << "{";
	bool first = true;
	for (const auto& kv : m) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << kv.first << ": " << kv.second;
	}
	return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
	if (t != u) {
		ostringstream os;
		os << "Assertion failed: " << t << " != " << u;
		if (!hint.empty()) {
			os << " hint: " << hint;
		}
		throw runtime_error(os.str());
	}
}

void Assert(bool b, const string& hint) {
	AssertEqual(b, true, hint);
}

class TestRunner {
public:
	template <class TestFunc>
	void RunTest(TestFunc func, const string& test_name) {
		try {
			func();
			cerr << test_name << " OK" << endl;
		}
		catch (exception& e) {
			++fail_count;
			cerr << test_name << " fail: " << e.what() << endl;
		}
		catch (...) {
			++fail_count;
			cerr << "Unknown exception caught" << endl;
		}
	}

	~TestRunner() {
		if (fail_count > 0) {
			cerr << fail_count << " unit tests failed. Terminate" << endl;
			exit(1);
		}
	}

private:
	int fail_count = 0;
};

class Person {
public:
	void ChangeFirstName(int year, const string& first_name) {
	}
	void ChangeLastName(int year, const string& last_name) {
	}
	string GetFullName(int year) {
	}
};

class Person {
public:
	void ChangeFirstName(int year, const string& first_name) {
		// добавить факт изменения имени на first_name в год year
	}
	void ChangeLastName(int year, const string& last_name) {
		// добавить факт изменения фамилии на last_name в год year
	}
	string GetFullName(int year) {
		// получить имя и фамилию по состоянию на конец года year
	}
private:
	// приватные поля
};


void TestGetFullName() {
	Person person;
	AssertEqual(person.GetFullName(1970), "Incognito", "1");
	person.ChangeFirstName(1960, "Sara");
	AssertEqual(person.GetFullName(1970), "Sara with unknown last name", "2");
	person.ChangeLastName(1950, "Gonnah");
	AssertEqual(person.GetFullName(1955), "Gonnah with unknown first name", "3");
	AssertEqual(person.GetFullName(1970), "Sara Gonnah", "4")
}


int main() {
	TestRunner runner;
	runner.RunTest(TestGetFullName, "Test");
	return 0;
}
