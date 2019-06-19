/*
* Разработайте набор юнит-тестов, которые будут проверять корректность реализации класса Rational. 
* Тестировать случай, когда знаменатель равен нулю, не надо.
*
* Начать работу вы можете с шаблона, который содержит наш фреймворк юнит-тестов и заготовку класса Rational.
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

class Rational {
public:

	Rational();
	Rational(int numerator, int denominator) {
	}

	int Numerator() const {
	}

	int Denominator() const {
	}
};

void TestRational() {
	Rational r1;
	Rational r2(4, 6);
	Rational r3(-4, 6);
	Rational r4(-4, -6);
	Rational r5(4, -6);
	Rational r6(0, 6);
	AssertEqual(r1.Numerator(), 0, "1");
	AssertEqual(r1.Denominator(), 1, "1.1");
	AssertEqual(r2.Numerator(), 2, "2");
	AssertEqual(r2.Denominator(), 3, "2.1");
	AssertEqual(r3.Numerator(), -2, "3");
	AssertEqual(r3.Denominator(), 3, "3.1");
	AssertEqual(r4.Numerator(), 2, "4");
	AssertEqual(r4.Denominator(), 3, "4.1");
	AssertEqual(r5.Numerator(), -2, "5");
	AssertEqual(r5.Denominator(), 3, "5.1");
	AssertEqual(r6.Numerator(), 0, "6");
	AssertEqual(r6.Denominator(), 1, "6.1");
}

int main() {
	TestRunner runner;
	runner.RunTest(TestRational, "Test");
	return 0;
}
