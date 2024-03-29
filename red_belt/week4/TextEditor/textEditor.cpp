/*
* Рассмотрим упрощённый текстовый редактор, поддерживающий следующий набор команд:
* 1) Перемещение курсора влево (Left) и вправо (Right) на одну позицию.
* 2) Ввод символа в текущую позицию курсора (Insert).
* 3) Копирование фрагмента текста, начинающегося в текущей позиции курсора, в буфер обмена (Copy).
* 4) Вырезание фрагмента текста аналогично копированию с последующим удалением скопированных символов из текста (Cut).
* 5) Вставка содержимого буфера обмена в текущую позицию курсора (Paste).
*
* Эти команды действительно поддерживаются практически любым текстовым редактором. 
* Также для команд действуют стандартные правила, определяющие их эффект:
* Если редактор содержит текст длиной n символов, то курсор может находиться в одной из (n + 1) возможных позиций. 
* - Например, обозначим курсор вертикальной чертой | (это обозначение мы будем использовать в дальнейшем), 
* тогда в тексте abc курсор может располагаться в 4 позициях: |abc, a|bc, ab|c, abc|. 
* Поэтому команда Left не имеет эффекта, когда курсор расположен в начале текста, а Right не имеет эффекта, 
* когда курсор находится в конце. В частности, ни Left, ни Right не имеют эффекта, когда редактор не содержит текста.
* - Введённый символ располагается в позиции курсора, сдвигая курсор и весь текст справа от него на одну позицию вправо. 
* Аналогично, при вставке фрагмента длиной n курсор и текст справа от него смещаются на n позиций вправо. 
* В таблице ниже приведены примеры, демонстрирующие данное правило.
*
* До вставки	Вводимый символ/вставляемый фрагмент	После вставки
*	  |							a							 a|
*	 ab|						c							abc|
*	 |bc						a							a|bc
*	|world					  hello_					hello_|world
*	hello_|					  world						hello_world|
*	123|78					   456						 123456|78
*
* Буфер обмена изначально пуст. Вставка пустого фрагмента не имеет эффекта. 
* Содержимое буфера не сбрасывается после вставки, а остается неизменным до следующей команды Copy или Cut. 
* Копирование или вырезание фрагмента нулевой длины не оказывает влияния на текст, но опустошает буфер обмена. 
* Курсор не смещается ни при копировании, ни при вырезании текста. 
* Например, после вырезания из текста ab|cdef фрагмента из трёх символов, получим текст ab|f.
*
* Вам предстоит реализовать «ядро» текстового редактора, 
* поддерживающего все описанные операции, в виде класса Editor, имеющего следующий интерфейс:
*
* class Editor {
* public:
*   Editor();
*   void Left();   // сдвинуть курсор влево
*   void Right();  // сдвинуть курсор вправо
*   void Insert(char token);   // вставить символ token
*   void Copy(size_t tokens);  // cкопировать
*                              // не более tokens символов,
*                              // начиная с текущей позиции курсора
*   void Cut(size_t tokens);  // вырезать не более tokens символов,
*                             // начиная с текущей позиции курсора
*   void Paste();  // вставить содержимое буфера
*                  // в текущую позицию курсора
*   string GetText() const;  // получить текущее содержимое
*                            // текстового редактора
* };
*
* Как можно заметить, каждой описанной команде сопоставлен метод класса Editor. 
* Также введён метод GetText(), позволяющий получить текущее содержимое редактора в виде строки. 
* В комментариях к методам Cut(size_t tokens) и Copy(size_t tokens) указано, 
* что в буфер обмена попадает фрагмент длиной не более tokens символов — это означает, 
* что, если справа от курсора располагается менее, чем tokens символов, 
* методы Cut() и Copy() должны вырезать/скопировать все символы справа.
*
* Ограничения
* Реализация класса Editor должна обрабатывать 10^6 запросов не более чем за 1 секунду. При этом гарантируется, что:
*
* - длина текста никогда не превышает 10^6 символов;
* - методы Copy() и Cut() суммарно копируют/вырезают не более 10^6 символов;
* - метод GetText() вызывается один раз в каждом из тестов.
*/

#include <string>
#include <list>
#include "test_runner.h"

using namespace std;

class Editor {
public:
	Editor() : cursor_(text_.end()) {}
	void Left() {
		if (cursor_ != text_.begin())
			--cursor_;
	}
	void Right() {
		if (cursor_ != text_.end())
			++cursor_;
	}
	void Insert(char token) {
		text_.insert(cursor_, token);
	}
	void Cut(size_t tokens = 1) {
		buffer.resize(0);
		while (tokens != 0) {
			if (cursor_ == text_.end())
				break;
			buffer.push_back(*cursor_);
			cursor_ = text_.erase(cursor_);
			--tokens;
		}
	}
	void Copy(size_t tokens = 1) {
		buffer.resize(0);
		auto it = cursor_;
		while (tokens != 0) {
			if (it == text_.end())
				break;
			buffer.push_back(*it);
			++it;
			--tokens;
		}
	}
	void Paste() {
		for (const auto& value : buffer) {
			text_.insert(cursor_, value);
		}
	}
	string GetText() const {
		string result;
		for (const auto& it : text_) {
			result.push_back(it);
		}
		return result;
	}
private:
	list<char> text_;
	list<char>::iterator cursor_;
	vector<char> buffer;
};

void TypeText(Editor& editor, const string& text) {
	for (char c : text) {
		editor.Insert(c);
	}
}

void TestEditing() {
	{
		Editor editor;

		const size_t text_len = 12;
		const size_t first_part_len = 7;
		TypeText(editor, "hello, world");
		for (size_t i = 0; i < text_len; ++i) {
			editor.Left();
		}
		editor.Cut(first_part_len);
		for (size_t i = 0; i < text_len - first_part_len; ++i) {
			editor.Right();
		}
		TypeText(editor, ", ");
		editor.Paste();
		editor.Left();
		editor.Left();
		editor.Cut(3);

		ASSERT_EQUAL(editor.GetText(), "world, hello");
	}
	{
		Editor editor;

		TypeText(editor, "misprnit");
		editor.Left();
		editor.Left();
		editor.Left();
		editor.Cut(1);
		editor.Right();
		editor.Paste();

		ASSERT_EQUAL(editor.GetText(), "misprint");
	}
}

void TestReverse() {
	Editor editor;

	const string text = "esreveR";
	for (char c : text) {
		editor.Insert(c);
		editor.Left();
	}

	ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText() {
	Editor editor;
	ASSERT_EQUAL(editor.GetText(), "");

	editor.Left();
	editor.Left();
	editor.Right();
	editor.Right();
	editor.Copy(0);
	editor.Cut(0);
	editor.Paste();

	ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer() {
	Editor editor;

	editor.Paste();
	TypeText(editor, "example");
	editor.Left();
	editor.Left();
	editor.Paste();
	editor.Right();
	editor.Paste();
	editor.Copy(0);
	editor.Paste();
	editor.Left();
	editor.Cut(0);
	editor.Paste();

	ASSERT_EQUAL(editor.GetText(), "example");
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestEditing);
	RUN_TEST(tr, TestReverse);
	RUN_TEST(tr, TestNoText);
	RUN_TEST(tr, TestEmptyBuffer);
	return 0;
}
