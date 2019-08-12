/*
* Крупная IT-компания Янгл проводит исследование упоминаемости своего бренда в блогах и социальных сетях.
* Аналитики компании уже выгрузили интересующие их публикации и сформировали набор ключевых слов.
* Их интересует, сколько раз каждое ключевое слово входит в набор публикаций.
*
* Помогите им это сделать — напишите функцию Stats ExploreKeyWords(const set<string>& key_words, istream& input).
* Её параметры:
* - key_words — множество ключевых слов
* - input — входной поток, содержащий исследуемые публикации в блогах и соц. сетях, одна строка — одна публикация.
*
* Функция ExploreKeyWords должна возвращать структуру Stats, в которой хранится,
* сколько раз каждое слово из key_words суммарно встретилось в потоке input:
* struct Stats {
*   map<string, int> word_frequences;
*
*   void operator += (const Stats& other);
* };
*
* При подсчёте вхождения ключевых слов в текст нужно учитывать только вхождения в виде отдельных слов.
* Слова друг от друга отделяются одним или несколькими пробелами.
* В качестве примера допустим, что key_words = {"yangle", "rocks", "sucks", "all"}
* и у нас есть публикация из соц. сети Switter: "Goondex really sucks, but yangle rocks ! Use yangle".
* Слово «yangle» входит в неё 2 раза, «rocks» — один раз, а слова «all» и «sucks» — ни разу.
* Слово «sucks» не входит ни разу, потому что в данном примере оно является префиксом слова «sucks,»
* (по условию, слова друг от друга отделяются только пробелами).
* Несмотря на то, что слово «all» является частью слова «really»,
* его вхождение тоже нельзя засчитывать, так как это не отдельное слово.
*
* Чтобы уложиться в Time Limit, подумайте, можно ли эту задачу распараллелить.
*
* Замечание
* До этого в лекциях мы показывали, как использовать функцию async для асинхронного запуска лямбда-функций без параметров.
* Однако её можно использовать и для запуска функций, у которых есть параметры. Например,
* string Join(string s, string t) {
*  return s + t;
* }
*
* string a = "Hello";
* string b = " world";
* future<int> f = async(Join, a, b);
*
* Как видите, чтобы передать параметры в функцию, запускаемую асинхронно,
* их надо указать в качестве параметров функции async после самой функции.
* Важно отметить, что при таком вызове будут созданы копии фактических параметров
* (т.е. в нашем примере выше строки a и b будут скопированы).
* Это не всегда желательно. Например, если у нас есть константный объект,
* который потоки только читают, у нас нет необходимости создавать его копию,
* и можно передать его по ссылке.
* Для этого надо воспользоваться функцией ref из заголовочного файла <functional>.
*
* Stats ExploreKeyWordsSingleThread(const set<string>& key_words, istream& input);
*
* Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
*   // key_words и input будут переданы по ссылке, а не скопированы
*   return async(ExploreKeyWordsSingleThread, ref(key_words), ref(input)).get();
* }
*/

#include "test_runner.h"
#include "profile.h"

#include <map>
#include <string>
#include <future>
#include <functional>
#include <sstream>
#include <iostream>

using namespace std;

template <typename Iterator>
class IteratorRange {
public:
	IteratorRange(Iterator begin, Iterator end)
		: first(begin)
		, last(end)
		, size_(distance(first, last))
	{
	}

	Iterator begin() const {
		return first;
	}

	Iterator end() const {
		return last;
	}

	size_t size() const {
		return size_;
	}

private:
	Iterator first, last;
	size_t size_;
};

template <typename Iterator>
class Paginator {
private:
	vector<IteratorRange<Iterator>> pages;

public:
	Paginator(Iterator begin, Iterator end, size_t page_size) {
		for (size_t left = distance(begin, end); left > 0; ) {
			size_t current_page_size = min(page_size, left);
			Iterator current_page_end = next(begin, current_page_size);
			pages.push_back({ begin, current_page_end });

			left -= current_page_size;
			begin = current_page_end;
		}
	}

	auto begin() const {
		return pages.begin();
	}

	auto end() const {
		return pages.end();
	}

	size_t size() const {
		return pages.size();
	}
};

template <typename C>
auto Paginate(C& c, size_t page_size) {
	return Paginator(begin(c), end(c), page_size);
}

struct Stats {
	map<string, int> word_frequences;

	void operator += (const Stats& other) {
		for (const auto& item : other.word_frequences) {
			word_frequences[item.first] += item.second;
		}
	}
};


template <typename Container>
Stats ExploreLine(const set<string>& key_words, const Container& lines) {
	Stats result;

	for (const auto& line : lines) {
		stringstream ss(line);
		string word;

		while (ss >> word) {
			if (key_words.find(word) != key_words.end()) {
				++result.word_frequences[word];
			}
		}
	}

	return result;
}

Stats ExploreKeyWordsMultiThread(const set<string>& key_words, istream& input) {

	vector<future<Stats>> stats;
	vector<string> streams;

	for (string line; getline(input, line); ) {
		streams.push_back(line);
	}

	size_t page_size = streams.size() / 4 + 1;

	for (const auto& page : Paginate(streams, page_size)) {
		stats.push_back(async([&page, &key_words] {
			return ExploreLine(key_words, page);
		}));
	}

	Stats result;
	for (auto& stat : stats) {
		result += stat.get();
	}

	return result;
}

Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
	return ExploreKeyWordsMultiThread(key_words, input);
}

void TestBasic() {
	const set<string> key_words = { "yangle", "rocks", "sucks", "all" };

	stringstream ss;
	ss << "this new yangle service really rocks\n";
	ss << "It sucks when yangle isn't available\n";
	ss << "10 reasons why yangle is the best IT company\n";
	ss << "yangle rocks others suck\n";
	ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

	const auto stats = ExploreKeyWords(key_words, ss);
	const map<string, int> expected = {
	  {"yangle", 6},
	  {"rocks", 2},
	  {"sucks", 1}
	};
	ASSERT_EQUAL(stats.word_frequences, expected);
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestBasic);
}
