/*
* Имеется база регионов, представленная вектором структур Region:
* struct Region {
*   string std_name;
*   string parent_std_name;
*   map<Lang, string> names;
*   int64_t population;
* };
* Здесь Lang — идентификатор языка:
* enum class Lang {
*   DE, FR, IT
* };
* Напишите функцию FindMaxRepetitionCount, принимающую базу регионов и определяющую, 
* какое максимальное количество повторов она содержит. Две записи (объекты типа Region) считаются различными, 
* если они отличаются хотя бы одним полем.
* int FindMaxRepetitionCount(const vector<Region>& regions);
* Если все записи уникальны, считайте максимальное количество повторов равным 1. 
* Если записи отсутствуют, верните 0. Гарантируется, что типа int достаточно для хранения ответа.
*/

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <tuple>
#include <algorithm>

enum class Lang {
	DE, FR, IT
};

struct Region {
	std::string std_name;
	std::string parent_std_name;
	std::map<Lang, std::string> names;
	int64_t population;
};

auto GetRank(const Region& region) {
	return tie(region.std_name, region.parent_std_name, region.names, region.population);
}

bool operator < (const Region& lhs, const Region& rhs) {
	return GetRank(lhs) < GetRank(rhs);
}

int FindMaxRepetitionCount(const std::vector<Region>& regions) {
	int result = 0;
	std::map<Region, int> repCount;
	for (const auto& region : regions) {
		result = std::max(result, ++repCount[region]);
	}
	return result;
}


int main() {
	std::cout << FindMaxRepetitionCount({
		{
			"Moscow",
			"Russia",
			{{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
			89
		}, {
			"Russia",
			"Eurasia",
			{{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
			89
		}, {
			"Moscow",
			"Russia",
			{{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
			89
		}, {
			"Moscow",
			"Russia",
			{{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
			89
		}, {
			"Russia",
			"Eurasia",
			{{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
			89
		},
		}) << std::endl;

	std::cout << FindMaxRepetitionCount({
		{
			"Moscow",
			"Russia",
			{{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
			89
		}, {
			"Russia",
			"Eurasia",
			{{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
			89
		}, {
			"Moscow",
			"Russia",
			{{Lang::DE, "Moskau"}, {Lang::FR, "Moscou deux"}, {Lang::IT, "Mosca"}},
			89
		}, {
			"Moscow",
			"Toulouse",
			{{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
			89
		}, {
			"Moscow",
			"Russia",
			{{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
			31
		},
		}) << std::endl;

	return 0;
}


