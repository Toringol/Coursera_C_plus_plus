#pragma once

#include <string>
#include <vector>
#include <sstream>
using namespace std;

struct Date {
	int year, month, day;
};

struct Time {
	int hours, minutes;
};

struct AirlineTicket {
	string from;
	string to;
	string airline;
	Date departure_date;
	Time departure_time;
	Date arrival_date;
	Time arrival_time;
	int price;
};

bool operator < (const Date& lhs, const Date& rhs) {
	return vector<int>{lhs.year, lhs.month, lhs.day} <
		vector<int>{rhs.year, rhs.month, rhs.day};
}

bool operator == (const Date& lhs, const Date& rhs) {
	return vector<int>{lhs.year, lhs.month, lhs.day} ==
		vector<int>{rhs.year, rhs.month, rhs.day};
}

bool operator < (const Time& lhs, const Time& rhs) {
	return vector<int>{lhs.hours, lhs.minutes} <
		vector<int>{rhs.hours, rhs.minutes};
}

bool operator == (const Time& lhs, const Time& rhs) {
	return vector<int>{lhs.hours, lhs.minutes} ==
		vector<int>{rhs.hours, rhs.minutes};
}

ostream& operator << (ostream& stream, const Date& date) {
	stream << date.year << "-" << date.month << "-" << date.day << std::endl;
	return stream;
}

ostream& operator << (ostream& stream, const Time& time) {
	stream << time.hours << "." << time.minutes << std::endl;
	return stream;
}
