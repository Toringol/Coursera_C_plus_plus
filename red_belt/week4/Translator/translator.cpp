/*
* Разработайте класс Translator, позволяющий сохранять двуязычные пары слов и  
* затем переводить слова с одного языка на другой с использованием уже добавленных пар:
* class Translator {
* public:
*   void Add(string_view source, string_view target);
*   string_view TranslateForward(string_view source) const;
*   string_view TranslateBackward(string_view target) const;
*
* private:
*   // ...
* };
*
* Более конкретно, объект t типа Translator должен допускать следующие действия:
* 1) Создание с помощью конструктора по умолчанию. В этом случае база переводов пуста.
* 2) Добавление двуязычной пары: t.Add(source, target). После такого вызова считается, 
* что слово source на языке 1 соответствует слову target на языке 2. 
* Переданные в метод Add строки могут быть уничтожены раньше объекта t.
* 3) Перевод с языка 1 на язык 2: t.TranslateForward(source). 
* Если ранее уже был вызов t.Add(source_copy, target) для некоторой строки target и строки source_copy, 
* равной source (или являющейся ей), нужно вернуть target. 
* Если такого вызова не было, нужно вернуть пустую строку. 
* Если таких вызовов было несколько, нужно вернуть target для последнего из них.
* 4) Перевод с языка 2 на язык 1: t.TranslateBackward(target). 
* Если ранее уже был вызов t.Add(source, target_copy) для некоторой строки source и строки target_copy, 
* равной target (или являющейся ей), нужно вернуть source. Если такого вызова не было, нужно вернуть пустую строку. 
* Если таких вызовов было несколько, нужно вернуть source для последнего из них.
*
* Ограничения
* Каждая строка должна храниться в экземпляре класса Translator не более одного раза. 
* При нарушении этого ограничения вы получите ошибку «Memory limit exceeded».
*/

#include "test_runner.h"
#include <string>
#include <vector>
#include <map>

using namespace std;

class Translator {
public:
	void Add(string_view source, string_view target) {
		if (source != nullptr && target != nullptr) {
			first_language[source].push_back(target);
			second_language[target].push_back(source);
		}
	}
	string_view TranslateForward(string_view source) const {
		if (first_language.count(source) < 1)
			return "";
		return first_language.at(source).back();
	}
	string_view TranslateBackward(string_view target) const {
		if (second_language.count(target) < 1)
			return "";
		return second_language.at(target).back();
	}

private:
	map<string_view, vector<string_view>> first_language;
	map<string_view, vector<string_view>> second_language;
};

void TestSimple() {
	Translator translator;
	translator.Add(string("okno"), string("window"));
	translator.Add(string("stol"), string("table"));

	ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
	ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
	ASSERT_EQUAL(translator.TranslateBackward("stol"), "");
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestSimple);
	return 0;
}
