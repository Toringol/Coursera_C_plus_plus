/*
* В курсе «Белый пояс по С++» у нас была задача «Автобусные остановки — 1». 
* В этой задаче вам будет дано её правильное решение, целиком содержащееся внутри функции main. 
* Вам надо будет выполнить декомпозицию этого решения на заранее заданные блоки так, 
* чтобы получившаяся программа так же корректно решала задачу. Условие задачи «Автобусные остановки — 1» приведено ниже.
*/

#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

enum class QueryType {
	NewBus,
	BusesForStop,
	StopsForBus,
	AllBuses
};

struct Query {
	QueryType type;
	string bus;
	string stop;
	vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
	string operation_code;
	is >> operation_code;
	if (operation_code == "NEW_BUS") {
		q.type = QueryType::NewBus;
		is >> q.bus;
		int stop_count = 0;
		is >> stop_count;
		q.stops.resize(stop_count);
		for (auto& stop : q.stops) {
			is >> stop;
		}
	}
	else if (operation_code == "BUSES_FOR_STOP") {
		q.type = QueryType::BusesForStop;
		is >> q.stop;
	}
	else if (operation_code == "STOPS_FOR_BUS") {
		q.type = QueryType::StopsForBus;
		is >> q.bus;
	}
	else if (operation_code == "ALL_BUSES") {
		q.type = QueryType::AllBuses;
	}
	return is;
}

struct BusesForStopResponse {
	vector<string> busesForStops;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
	if (r.busesForStops.empty()) {
		os << "No stop";
	}
	else {
		for (const auto& bus : r.busesForStops) {
			os << bus << " ";
		}
	}
	return os;
}

struct StopsForBusResponse {
	string bus;
	vector<string> busesForStops;
	map<string, vector<string>> stopsForBus;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
	if (r.busesForStops.empty())
		os << "No bus";
	else {
		for (const auto& stop : r.busesForStops) {
			os << "Stop " << stop << ": ";
			if (r.stopsForBus.at(stop).size() == 1) {
				os << "no interchange";
			}
			else {
				for (const auto& other_bus : r.stopsForBus.at(stop)) {
					if (other_bus != r.bus) {
						os << other_bus << " ";
					}
				}
			}
			if (&stop != &r.busesForStops.back())
				os << endl;
		}
	}

	return os;
}

struct AllBusesResponse {
	map<string, vector<string>> busesForStops;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
	if (r.busesForStops.empty()) {
		os << "No buses";
	}
	else {
		for (const auto& bus_item : r.busesForStops) {
			os << "Bus " << bus_item.first << ": ";
			for (const string& stop : bus_item.second) {
				os << stop << " ";
			}
			if (bus_item != *(--r.busesForStops.end()))
				os << endl;
		}
	}
	return os;
}

class BusManager {
public:
	void AddBus(const string& bus, const vector<string>& stops) {
		buses_to_stops[bus] = stops;
		for (const auto& stop : stops)
			stops_to_buses[stop].push_back(bus);
	}

	BusesForStopResponse GetBusesForStop(const string& stop) const {
		BusesForStopResponse response;
		if (stops_to_buses.count(stop)) {
			response.busesForStops = stops_to_buses.at(stop);
		}
		return response;
	}

	StopsForBusResponse GetStopsForBus(const string& bus) const {
		StopsForBusResponse response;
		if (buses_to_stops.count(bus)) {
			response.bus = bus;
			response.busesForStops = buses_to_stops.at(bus);
			response.stopsForBus = stops_to_buses;
		}
		return response;
	}

	AllBusesResponse GetAllBuses() const {
		AllBusesResponse response;
		if (!buses_to_stops.empty())
			response.busesForStops = buses_to_stops;
		return response;
	}
private:
	map<string, vector<string>> buses_to_stops;
	map<string, vector<string>> stops_to_buses;
};


int main() {
	int query_count;
	Query q;

	cin >> query_count;

	BusManager bm;
	for (int i = 0; i < query_count; ++i) {
		cin >> q;
		switch (q.type) {
		case QueryType::NewBus:
			bm.AddBus(q.bus, q.stops);
			break;
		case QueryType::BusesForStop:
			cout << bm.GetBusesForStop(q.stop) << endl;
			break;
		case QueryType::StopsForBus:
			cout << bm.GetStopsForBus(q.bus) << endl;
			break;
		case QueryType::AllBuses:
			cout << bm.GetAllBuses() << endl;
			break;
		}
	}

	return 0;
}
