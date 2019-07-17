/*
* Условие
* Разработайте систему стимулирования чтения электронных книг. 
* Для простоты будем считать, что книга всего одна, но её одновременно читают много людей. 
* Необходимо следить за прогрессом чтения у всех пользователей и выводить мотивирующие уведомления. 
* А именно, ваша программа должна обрабатывать следующие события:
*
* - READ user page — сохранить факт того, что пользователь под номером user дочитал книгу до страницы page. 
* Если ранее такой пользователь не встречался, необходимо его добавить. 
* Гарантируется, что в рамках одного пользователя номера страниц в соответствующих ему событиях возрастают.
* - CHEER user — сообщить пользователю user, какая доля существующих пользователей (не считая его самого) 
* прочитала меньшую часть книги, чем он. Если этот пользователь на данный момент единственный, доля считается равной 1. 
* Если для данного пользователя пока не было ни одного события READ, доля считается равной 0, 
* а сам пользователь не учитывается при вычислении долей для других пользователей до тех пор, 
* пока для него не случится событие READ.
*
* Формат входных данных
* В первой строке вводится количество запросов Q — натуральное число, не превосходящее 10^6. 
* В следующих Q строках в соответствии с описанным выше форматом вводятся запросы. 
* Гарантируется, что все вводимые числа целые и положительные, при этом номера пользователей не превосходят 10^5, 
* а номера страниц не превосходят 1000.
*
* Формат выходных данных
* Для каждого запроса CHEER user выведите единственное вещественное число от 0 до 1 — долю пользователей, 
* прочитавших меньше страниц, чем user. Формат вывода этого числа должен быть в точности таким же, 
* как в опубликованном ниже медленном решении.
*
* Ограничения
* 4 секунды на выполнение всех запросов. Все описанные в условии гарантии действительно справедливы для всех тестов, 
* на которых будет запускаться ваша программа. Проверять корректность тестов не нужно.
*/

#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <set>
#include <map>

using namespace std;

class ReadingManager {
public:
	void Read(int user_id, int page_count) {
		if ((users_pages.count(user_id) > 0) &&
			(pages_users[users_pages[user_id]].size() == 1)) {
			pages_users[users_pages[user_id]].erase(user_id);
			pages_users.erase(users_pages[user_id]);
		}
		else if (users_pages.count(user_id) > 0) {
			pages_users[users_pages[user_id]].erase(user_id);
		}
		else {
			++users_number;
		}
		users_pages[user_id] = page_count;
		pages_users[page_count].insert(user_id);

	}

	double Cheer(int user_id) const {
		if (users_pages.count(user_id) < 1) {
			return 0;
		}
		if (users_number == 1) {
			return 1;
		}
		const int page_count = users_pages.at(user_id);
		auto itEnd = pages_users.find(page_count);
		auto itBegin = pages_users.begin();
		int membersLess = GetMemberLessSize(itBegin, itEnd);
		return membersLess * 1.0 / (users_number - 1);
	}

	using it = map<int, set<int>>::const_iterator;	
	int GetMemberLessSize(it begin, it end) const {
		int usersLess = 0;
		for (auto currentIt = begin; currentIt != end; ++currentIt) {
			usersLess += currentIt->second.size();
		}
		return usersLess;
	}

private:
	map<int, int> users_pages;
	map<int, set<int>> pages_users;
	int users_number = 0;
};


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	ReadingManager manager;

	int query_count;
	cin >> query_count;

	for (int query_id = 0; query_id < query_count; ++query_id) {
		string query_type;
		cin >> query_type;
		int user_id;
		cin >> user_id;

		if (query_type == "READ") {
			int page_count;
			cin >> page_count;
			manager.Read(user_id, page_count);
		}
		else if (query_type == "CHEER") {
			cout << setprecision(6) << manager.Cheer(user_id) << "\n";
		}
	}

	return 0;
}
