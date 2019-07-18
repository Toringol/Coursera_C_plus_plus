/*
* Условие
* Разработайте систему бронирования отелей, 
* позволяющую бронировать номера клиентами и контролировать спрос владельцами отелей. 
* Ваша программа должна обрабатывать следующие события:
*
* - BOOK time hotel_name client_id room_count — 
* забронировать клиентом client_id room_count номеров в отеле hotel_name в момент времени time. 
* Время измеряется в секундах, отсчитываемых от некоторого момента.
* - CLIENTS hotel_name — вывести количество различных клиентов, 
* бронировавших номера в отеле hotel_name за последние сутки. 
* Более формально интересующий диапазон времени описывается следующим образом: 
* пусть current_time — время последнего события BOOK, 
* тогда в данном запросе нужно учесть все события с current_time − 86400 < time ⩽ current_time, 
* где 86400 — количество секунд в сутках. Обратите внимание, что последнее бронирование должно учитываться, 
* а бронирование, случившееся ровно за сутки до него, учитываться не должно.
* - ROOMS hotel_name — вывести количество номеров, забронированных за последние сутки в отеле hotel_name.
*
* Формат входных данных
* В первой строке вводится количество запросов Q — натуральное число, не превосходящее 10^5. 
* В следующих Q строках в соответствии с описанным выше форматом вводятся запросы. 
* Гарантируется, что:
*
* - time — целое число в диапазоне от −10^18 до 10^18 и не убывает от события к событию.
* - hotel_name — строка из латинских букв и цифр, имеющая длину не более 12 символов.
* - client_id — натуральное число, не превосходящее 10^9.
* - room_count — целое положительное число, не превосходящее 1000.
* 
* Формат выходных данных
* Для каждого запроса CLIENTS и ROOMS выведите единственное целое число — ответ на запрос. 
* Если указанный в запросе отель пока не имеет ни одного бронирования, выведите 0.
*
* Ограничения
* 1 секунда на выполнение всех запросов. Все описанные в условии гарантии действительно справедливы для всех тестов, 
* на которых будет запускаться ваша программа. Проверять корректность тестов не нужно.
*/

#include <iostream>
#include <queue>
#include <string>
#include <map>
#include <set>

using namespace std;

struct BookEvents {
	int64_t time;
	string hotelName;
	size_t client_id, room_count;
};

class BookEventManager {
public:
	void Add(const int64_t& time, const string& hotelName, 
			 const size_t& client_id, const size_t& room_count) {
		Adjust(time);
		bookEvents.push({ time, hotelName, client_id, room_count });
		hotelName_ClientID_roomsCount[hotelName][client_id] += room_count;
		hotelName_roomsCount[hotelName] += room_count;
	}

	size_t CountClients(const string& hotelName) const {
		if (hotelName_ClientID_roomsCount.count(hotelName) < 1) {
			return 0;
		}
		return hotelName_ClientID_roomsCount.at(hotelName).size();
	}

	size_t CountRooms(const string& hotelName) const {
		if (hotelName_roomsCount.count(hotelName) < 1) {
			return 0;
		}
		return hotelName_roomsCount.at(hotelName);
	}

private:
	queue<BookEvents> bookEvents;
	map<string, map<size_t, size_t>> hotelName_ClientID_roomsCount;
	map<string, size_t> hotelName_roomsCount;

	void Adjust(int64_t time) {
		while (!bookEvents.empty() && bookEvents.front().time <= time - 86400) {
			hotelName_ClientID_roomsCount[bookEvents.front().hotelName][bookEvents.front().client_id] 
				-= bookEvents.front().room_count;
			if (hotelName_ClientID_roomsCount[bookEvents.front().hotelName][bookEvents.front().client_id] == 0) {
				hotelName_ClientID_roomsCount[bookEvents.front().hotelName].erase(bookEvents.front().client_id);
			}
			if (hotelName_ClientID_roomsCount[bookEvents.front().hotelName].size() == 0) {
				hotelName_ClientID_roomsCount.erase(bookEvents.front().hotelName);
			}
			hotelName_roomsCount[bookEvents.front().hotelName] -= bookEvents.front().room_count;
			if (hotelName_roomsCount[bookEvents.front().hotelName] == 0) {
				hotelName_roomsCount.erase(bookEvents.front().hotelName);
			}
			bookEvents.pop();
		}
	}
};


class Booking {
public:
	void Book(int64_t time, const string& hotel_name,
		const size_t& client_id, const size_t room_count) {
		bookEvent.Add(time, hotel_name, client_id, room_count);
	}

	size_t Clients(const string& hotel_name) const {
		return bookEvent.CountClients(hotel_name);
	}

	size_t Rooms(const string& hotel_name) const {
		return bookEvent.CountRooms(hotel_name);
	}

private:
	BookEventManager bookEvent;
};


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	Booking booking;

	size_t query_count;
	cin >> query_count;

	for (size_t query_id = 0; query_id < query_count; ++query_id) {
		string query_type;
		cin >> query_type;
		
		if (query_type == "BOOK") {
			int64_t time;
			string hotel_name;
			size_t client_id, room_count;
			cin >> time >> hotel_name >> client_id >> room_count;
			booking.Book(time, hotel_name, client_id, room_count);
		}
		else if (query_type == "CLIENTS") {
			string hotel_name;
			cin >> hotel_name;
			cout << booking.Clients(hotel_name) << endl;
		}
		else if (query_type == "ROOMS") {
			string hotel_name;
			cin >> hotel_name;
			cout << booking.Rooms(hotel_name) << endl;
		}
	}

	return 0;
}
