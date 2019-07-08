#pragma once

#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <stdio.h>
#include <set>

using namespace std;

class Date {
public:
	Date() {}
	Date(const int& new_year, const int& new_month, const int& new_day);
	int GetYear() const;
	int GetMonth() const;
	int GetDay() const;
private:
	int year;
	int month;
	int day;
};

bool operator < (const Date& lhs, const Date& rhs);

bool operator > (const Date& lhs, const Date& rhs);

bool operator == (const Date& lhs, const Date& rhs);

bool operator <= (const Date& lhs, const Date& rhs);

bool operator >= (const Date& lhs, const Date& rhs);

bool operator != (const Date& lhs, const Date& rhs);

std::ostream& operator << (std::ostream& stream, const Date& date);

Date ParseDate(std::istream& stream);