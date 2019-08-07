/*
* Дан вектор токенов. Напишите функцию, разбивающую токены на предложения:
* template <typename Token>
* vector<Sentence<Token>> SplitIntoSentences(vector<Token> tokens);
*
* Token — шаблонный тип, про который известно лишь то, 
* что он имеет константный метод IsEndSentencePunctuation, возвращающий true, 
* если токен является знаком пунктуации, заканчивающим предложение, и false в противном случае. 
* Объекты этого типа запрещено копировать. При наличии копирования этих объектов вы получите ошибку компиляции.
* 
* Sentence — синоним для типа vector, объявленный следующим образом:
*
* // Объявляем Sentence<Token> для произвольного типа Token
* // синонимом vector<Token>.
* // Благодаря этому в качестве возвращаемого значения
* // функции можно указать не малопонятный вектор векторов,
* // а вектор предложений — vector<Sentence<Token>>.
* template <typename Token>
* using Sentence = vector<Token>;
*
* Предложением считается последовательность токенов, заканчивающаяся подряд идущими токенами, 
* являющимися знаками пунктуации конца предложения. Иными словами, любое предложение должно состоять из двух частей:
* - токены, для которых IsEndSentencePunctuation возвращает false 
* (такие токены обязаны присутствовать в предложении за исключением, возможно, первого предложения);
* - токены, для которых IsEndSentencePunctuation возвращает true 
* (такие токены обязаны присутствовать в предложении за исключением, возможно, последнего предложения).
* 
* Ограничения
* Максимальное количество токенов — 10^6. Время выполнения одного вызова функции ограничено 1 секундой.
*/

#include "test_runner.h"

#include <vector>

using namespace std;

template <typename Token>
using Sentence = vector<Token>;

template <typename Token>
vector<Sentence<Token>> SplitIntoSentences(vector<Token> tokens) {
	vector<Sentence<Token>> sentences;
	Sentence<Token> sentence;
	bool flag_punctuation = false;
	for (auto& token : tokens) {
		if (!token.IsEndSentencePunctuation() && !flag_punctuation) {
			sentence.push_back(move(token));
		}
		else if (token.IsEndSentencePunctuation() && flag_punctuation) {
			sentence.push_back(move(token));
		}
		else if (token.IsEndSentencePunctuation() && !flag_punctuation) {
			sentence.push_back(move(token));
			flag_punctuation = true;
		}
		else if (!token.IsEndSentencePunctuation() && flag_punctuation) {
			sentences.push_back(move(sentence));
			sentence.resize(0);
			sentence.push_back(move(token));
			flag_punctuation = false;
		}

	}
	if (!sentence.empty()) {
		sentences.push_back(move(sentence));
		sentence.resize(0);
	}
	return sentences;
}


struct TestToken {
	string data;
	bool is_end_sentence_punctuation = false;

	bool IsEndSentencePunctuation() const {
		return is_end_sentence_punctuation;
	}
	bool operator==(const TestToken& other) const {
		return data == other.data && is_end_sentence_punctuation == other.is_end_sentence_punctuation;
	}
};

ostream& operator<<(ostream& stream, const TestToken& token) {
	return stream << token.data;
}


void TestSplitting() {
	ASSERT_EQUAL(
		SplitIntoSentences(vector<TestToken>({ {"Split"}, {"into"}, {"sentences"}, {"!"} })),
		vector<Sentence<TestToken>>({
			{{"Split"}, {"into"}, {"sentences"}, {"!"}}
			})
	);

	ASSERT_EQUAL(
		SplitIntoSentences(vector<TestToken>({ {"Split"}, {"into"}, {"sentences"}, {"!", true} })),
		vector<Sentence<TestToken>>({
			{{"Split"}, {"into"}, {"sentences"}, {"!", true}}
			})
	);

	ASSERT_EQUAL(
		SplitIntoSentences(vector<TestToken>({ {"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}, {"Without"}, {"copies"}, {".", true} })),
		vector<Sentence<TestToken>>({
			{{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}},
			{{"Without"}, {"copies"}, {".", true}},
			})
			);
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestSplitting);
	return 0;
}
