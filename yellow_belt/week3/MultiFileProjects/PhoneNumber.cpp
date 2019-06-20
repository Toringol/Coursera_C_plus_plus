/*
* Вам дан заголовочный файл phone_number.h, содержащий объявление класса PhoneNumber. 
* При этом в комментариях описано поведение, которое ожидается от реализации этого класса.
* Пришлите cpp-файл с определениями методов класса PhoneNumber, которые реализуют описанное поведение.
*/

#pragma once

#include <string>
#include <sstream>
#include <exception>
#include <vector>

using namespace std;

class PhoneNumber {
public:
  /* Принимает строку в формате +XXX-YYY-ZZZZZZ
     Часть от '+' до первого '-' - это код страны.
     Часть между первым и вторым символами '-' - код города
     Всё, что идёт после второго символа '-' - местный номер.
     Код страны, код города и местный номер не должны быть пустыми.
     Если строка не соответствует этому формату, нужно выбросить исключение invalid_argument. 
     Проверять, что номер содержит только цифры, не нужно.

     Примеры:
     * +7-495-111-22-33
     * +7-495-1112233
     * +323-22-460002
     * +1-2-coursera-cpp
     * 1-2-333 - некорректный номер - не начинается на '+'
     * +7-1233 - некорректный номер - есть только код страны и города
  */
	explicit PhoneNumber(const string &international_number);

	string GetCountryCode() const;

	string GetCityCode() const;

	string GetLocalNumber() const;

	string GetInternationalNumber() const;

private:
	string country_code_;
	string city_code_;
	string local_number_;
};

PhoneNumber::PhoneNumber(const string &international_number) {
	if (international_number[0] != '+')
		throw invalid_argument("");
	istringstream stream(international_number);
	char firstSymbol = stream.get();
	getline(stream, country_code_, '-');
	getline(stream, city_code_, '-');
	getline(stream, local_number_);
	if (firstSymbol != '+' || country_code_.empty() || city_code_.empty() || local_number_.empty())
		throw invalid_argument("");
}


string PhoneNumber::GetCountryCode() const {
	return country_code_;
}
string PhoneNumber::GetCityCode() const {
	return city_code_;
}
string PhoneNumber::GetLocalNumber() const {
	return local_number_;
}
string PhoneNumber::GetInternationalNumber() const {
	return ("+" + GetCountryCode() + "-" + GetCityCode() + "-" + GetLocalNumber());
}


int main() {
	PhoneNumber phoneNumber("+--");
	return 0;
}
