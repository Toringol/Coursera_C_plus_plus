/*
* Условие
* Разработайте простейшую систему маршрутизации экспрессов, курсирующих по одному железнодорожному направлению, 
* представляющему собой прямую. Ваша программа должна уметь обрабатывать запросы двух типов:
*
* - ADD start finish — добавить в систему маршрутов экспресс, 
* следующий со станции start до станции finish и обратно. 
* Экспресс не делает промежуточных остановок. Станции задаются целыми числами, 
* равными их расстоянию от вокзала (он имеет номер 0).
* 
* - GO start finish — попытаться проложить беспересадочный маршрут от станции start до станции finish. 
* Если существует экспресс между этими двумя станциями, в ответ на данный запрос выведите 0. 
* В противном случае выведите положительное число — минимальное расстояние, 
* на которое можно приблизиться к станции finish, стартовав строго на станции start и использовав не более одного экспресса.
* 
* Формат входных данных
* В первой строке вводится количество запросов Q — натуральное число, не превосходящее 10^5. 
* В следующих Q строках в соответствии с описанным выше форматом вводятся запросы. 
* Гарантируется, что номера станций являются целыми числами, по модулю не превосходящими 10^9.
*
* Формат выходных данных
* Для каждого запроса GO выведите единственное целое неотрицательное число — 
* минимальное расстояние до конечной станции маршрута, вычисляемое в соответствии с описанными выше правилами.
*
* Ограничения
* 1 секунда на выполнение всех запросов. Все описанные в условии гарантии действительно справедливы для всех тестов, 
* на которых будет запускаться ваша программа. Проверять корректность тестов не нужно.
*/

#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <set>

using namespace std;

class RouteManager {
public:
	void AddRoute(int start, int finish) {
		reachable_lists_[start].insert(finish);
		reachable_lists_[finish].insert(start);
	}
	int FindNearestFinish(int start, int finish) const {
		int result = abs(start - finish);
		if (reachable_lists_.count(start) < 1) {
			return result;
		}
		const set<int>& reachable_stations = reachable_lists_.at(start);
		if (!reachable_stations.empty()) {
			if (reachable_stations.count(finish) > 0)
				return 0;
			auto itFinish = reachable_stations.lower_bound(finish);
			if (itFinish != reachable_stations.end()) {
				result = min(result, abs(finish - *(itFinish)));
			}
			if (itFinish != reachable_stations.begin()) {
				result = min(result, abs(finish - *prev(itFinish)));
			}
		}
		return result;
	}
private:
	map<int, set<int>> reachable_lists_;
};


int main() {
	RouteManager routes;

	int query_count;
	cin >> query_count;

	for (int query_id = 0; query_id < query_count; ++query_id) {
		string query_type;
		cin >> query_type;
		int start, finish;
		cin >> start >> finish;
		if (query_type == "ADD") {
			routes.AddRoute(start, finish);
		}
		else if (query_type == "GO") {
			cout << routes.FindNearestFinish(start, finish) << "\n";
		}
	}

	return 0;
}
