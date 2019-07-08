#include "database.h"

void Database::Add(const Date& date, const std::string& event) {
	if ((dataBase.find(date) != dataBase.end()) && 
		(dataBase[date].first.find(event) != dataBase[date].first.end())) {
		return;
	}
	dataBase[date].first.insert(event);
	dataBase[date].second.push_back(event);
}


std::string Database::Last(const Date& date) const {
	ostringstream ostr;
	auto it = dataBase.upper_bound(date);
	if (it == dataBase.begin()) {
		throw std::invalid_argument("");
	}
	--it;
	ostr << it->first << " " << it->second.second.back();
	return ostr.str();
}


void Database::Print(std::ostream& stream) const {
	for (const auto& item : dataBase) {
		for (const auto& value : item.second.second) {
			stream << item.first << " " << value << std::endl;
		}
	}
}

