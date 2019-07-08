#pragma once

#include <iostream>
#include <set>
#include <string>
#include <map>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <sstream>

#include "date.h"

class Database {
public:
	void Add(const Date& date, const std::string& event);
	std::string Last(const Date& date) const;
	void Print(std::ostream& stream) const;

	template <typename Func1>
	size_t RemoveIf(Func1 predicate) {
		size_t remove_counter = 0;
		std::vector<Date> delDates;

		for (auto& db : dataBase) {
			Date date = db.first;
			auto partitionIt = std::stable_partition(db.second.second.begin(), db.second.second.end(),
				[predicate, date](const std::string& str) {
				return !predicate(date, str);
			});
			
			remove_counter += std::distance(partitionIt, db.second.second.end());

			for (auto it = partitionIt; it != db.second.second.end(); ++it) {
				db.second.first.erase(*it);
			}

			if (db.second.first.empty()) {
				delDates.push_back(date);
			}

			db.second.second.resize(std::distance(db.second.second.begin(), partitionIt));
		}

		for (auto& it : delDates)
			dataBase.erase(it);

		return remove_counter;
	}

	template <typename Func2>
	std::vector<std::string> FindIf(Func2 predicate) const {
		std::vector<std::string> result;
		std::ostringstream ostr;

		for (const auto& db : dataBase) {
			Date date = db.first;
			std::vector<std::string> tmpVec(db.second.second.size());
			auto it = std::copy_if(db.second.second.begin(), db.second.second.end(), tmpVec.begin(),
				[predicate, date](const std::string& str) {
				return predicate(date, str);
			});
			tmpVec.resize(std::distance(tmpVec.begin(), it));
			
			for (const auto& it1 : tmpVec) {
				ostr << db.first << " " << it1;
				result.push_back(ostr.str());
				ostr.str("");
			}
		}

		return result;
	}

private:
	std::map<Date, std::pair<std::set<std::string>, std::vector<std::string>>> dataBase;
};