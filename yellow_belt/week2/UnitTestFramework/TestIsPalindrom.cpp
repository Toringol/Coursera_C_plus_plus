/*
* Разработайте набор юнит-тестов, который будет принимать правильные реализации функции IsPalindrom и отвергать неправильные. 
* При этом учитывайте, что правильная реализация функции:
*
* - считает пустую строку палиндромом;
* - считает строку из одного символа палиндромом;
* - осуществляет обычное сравнение символов на равенство, не игнорируя никакие символы, в том числе пробельные.
* При разработке тестов подумайте, какие ошибки можно допустить при реализации функции IsPalindrom. Примеры ошибок:
*
* - игнорируется первый или последний символ;
* - сравнение соответствующих символов завершается не в середине строки, а раньше;
* - игнорируются пробелы
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

bool IsPalindrom(const string& str) {
}

void TestIsPalindrom() {
	Assert(IsPalindrom(""), "1");
	Assert(IsPalindrom("a"), "2");
	Assert(IsPalindrom("ab  ba"), "3");
	Assert(IsPalindrom("aba"), "4");
	Assert(IsPalindrom("abba"), "5");
	Assert(!IsPalindrom("abbc"), "6");
	Assert(!IsPalindrom("ab bbba"), "7");
	Assert(!IsPalindrom(" bbbb"), "8");
	Assert(!IsPalindrom("bbbb "), "9");
	Assert(!IsPalindrom("abaacaba"), "10");
}

int main() {
	TestRunner runner;
	runner.RunTest(TestIsPalindrom, "Test");
	return 0;
}
