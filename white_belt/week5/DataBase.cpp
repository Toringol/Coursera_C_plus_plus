/*
* Необходимо написать программу на С++, которая реализует работу с простой базой данных (сокращённо «БД»). 
* Программа будет общаться с пользователем через стандартный ввод и вывод (потоки stdin и stdout).
*
* Будем хранить в нашей БД пары вида: дата, событие. Определим дату как строку вида Год-Месяц-День, 
* где Год, Месяц и День — целые числа.
* 
* Событие определим как строку из произвольных печатных символов без разделителей внутри (пробелов, табуляций и пр.). 
* Событие не может быть пустой строкой. В одну и ту же дату может произойти много разных событий, 
* БД должна суметь их все сохранить. Одинаковые события, произошедшие в один и тот же день, сохранять не нужно: 
* достаточно сохранить только одно из них.
* 
* Наша БД должна понимать определённые команды, чтобы с ней можно было взаимодействовать:
* - добавление события:                        Add Дата Событие
* - удаление события:                          Del Дата Событие
* - удаление всех событий за конкретную дату:  Del Дата
* - поиск событий за конкретную дату:          Find Дата
* - печать всех событий за все даты:           Print
*
* Все команды, даты и события при вводе разделены пробелами. Команды считываются из стандартного ввода. 
* В одной строке может быть ровно одна команда, но можно ввести несколько команд в несколько строк. 
* На вход также могут поступать пустые строки — их следует игнорировать и продолжать обработку новых команд в последующих строках.
*
* Добавление события (Add Дата Событие)
*
* При добавлении события БД должна его запомнить и затем показывать его при поиске (командой Find) или печати (командой Print). 
* Если указанное событие для данной даты уже существует, повторное его добавление нужно игнорировать. 
* В случае корректного ввода (см. раздел «Обработка ошибок ввода») программа ничего не должна выводить на экран.
*
* Удаление события (Del Дата Событие)
* 
* Команда должна удалить добавленное ранее событие с указанным именем в указанную дату, если оно существует. 
* Если событие найдено и удалено, программа должна вывести строку «Deleted successfully» (без кавычек). 
* Если событие в указанную дату не найдено, программа должна вывести строку «Event not found» (без кавычек).

* Удаление нескольких событий (Del Дата)
* 
* Команда удаляет все ранее добавленные события за указанную дату. 
* Программа всегда должна выводить строку вида «Deleted N events», 
* где N — это количество всех найденных и удалённых событий. N может быть равно нулю, 
* если в указанную дату не было ни одного события.
*
* Поиск событий (Find Дата)
*
* Найти и распечатать ранее добавленные события в указанную дату. 
* Программа должна вывести на печать только сами события, по одному на строке. 
* События должны быть отсортированы по возрастанию в порядке сравнения строк между собой (тип string).
*
* Печать всех событий (Print)
*
* С помощью этой команды можно показать полное содержимое нашей БД. 
* Программа должна вывести на печать все пары Дата Событие по одной на строке. 
* Все пары должны быть отсортированы по дате, а события в рамках одной даты 
* должны быть отсортированы по возрастанию в порядке сравнения строк между собой (тип string). 
* Даты должны быть отформатированы специальным образом: ГГГГ-ММ-ДД, где Г, М, Д — это цифры чисел года, 
* месяца и дня соответственно. Если какое-то число имеет меньше разрядов, 
* то оно должно дополняться нулями, например, 0001-01-01 — первое января первого года. 
* Вам не понадобится выводить дату с отрицательным значением года.
*
* Обработка ошибок ввода
*
* Ввод в этой задаче не всегда корректен: некоторые ошибки ввода ваша программа должна корректно обрабатывать.
* 
* Какие ошибки ввода нужно обрабатывать
* Если пользователь ввёл неизвестную команду, то программа должна об этом сообщить, 
* выведя строку «Unknown command: COMMAND», где COMMAND — это та команда, которую ввёл пользователь. 
* Командой считается первое слово в строке (до пробела).
* 
* Если дата не соответствует формату Год-Месяц-День, где Год, Месяц и День — произвольные целые числа, 
* то программа должна напечатать «Wrong date format: DATE», где DATE — это то, 
* что пользователь ввёл вместо даты (до пробела). Обратите внимание, 
* что части даты разделяются ровно одним дефисом, а сама дата не должна содержать лишних символов ни перед годом, 
* ни после дня. Части даты не могут быть пустыми, но могут быть нулевыми и даже отрицательными.
* 
* Если формат даты верен, необходимо проверить валидность месяца и дня.
* - Если номер месяца не является числом от 1 до 12, выведите «Month value is invalid: MONTH», 
* где MONTH — это неверный номер месяца, например, 13 или -1.
* - Если месяц корректен, а день не лежит в диапазоне от 1 до 31, 
* выведите «Day value is invalid: DAY», где DAY — это неверный номер дня в месяце, например, 39 или 0.
* Обратите внимание, что:
* - Значение года проверять отдельно не нужно.
* - Не нужно проверять календарную корректность даты: количество дней в каждом месяце считается равным 31, 
* високосные года учитывать не нужно.
* - Если неверны как месяц, так и день, то нужно вывести одно сообщение об ошибке в месяце.
* Примеры:
* - 1-1-1 — корректная дата;
* - -1-1-1 — корректная дата (год -1, месяц 1, день 1);
* - 1--1-1 — дата в верном формате, но с некорректным месяцем -1;
* - 1---1-1 — дата в неверном формате: месяц не может начинаться с двух дефисов.
* - 1​-+1-+1 — корректная дата, так как +1 это целое число
* После обработки любой из описанных ошибок ввода и печати сообщения программа должна завершать своё выполнение.
*
* Какие ошибки ввода не нужно обрабатывать
* Мы не ставим своей целью сломать вашу программу всеми возможными способами, поэтому, 
* за исключением описанного в предыдущем пункте, вы можете полагаться на корректность ввода. 
* В частности, мы гарантируем, что:
* - Каждая команда занимает целиком ровно одну строку, хотя во вводе могут быть и пустые строки (их нужно игнорировать).
* - События всегда содержат указанное количество аргументов: после команды Add всегда следуют дата и событие, 
* после команды Find всегда следует дата, после команды Del всегда следует дата и, возможно, 
* событие, а команда Print не содержит дополнительной информации.
* - Все команды, даты и события являются непустыми строками и не содержат пробелов и прочих пробельных символов. 
* (В частности, наши тесты не содержат команды «Add 2018-02-12», потому что в ней после даты отсутствует название события.) 
* С другой стороны, команда Del может не содержать события после даты: 
* в этом случае нужно удалить все события за указанную дату (см. раздел «Удаление нескольких событий»).
* - Несмотря на то, что дата с отрицательным значением года считается корректной, тесты устроены так, 
* что её не понадобится выводить в команде Print.
*/


#include <iostream>
#include <set>
#include <string>
#include <map>
#include <sstream>
#include <iomanip>

#define STARTOFMONTHS 1
#define ENDOFMONTHS 12

#define FIRSTDAYOFMONTH 1
#define LASTDAYOFMONTH 31

class Date {
public:
	Date() {}
	Date(int new_year, int new_month, int new_day) {
		year = new_year;
		month = new_month;
		day = new_day;
	}
	int GetYear() const { return year; }
	int GetMonth() const { return month; }
	int Getday() const { return day; }
private:
	int year;
	int month;
	int day;
};

bool operator < (const Date& lhs, const Date& rhs) {
	if (lhs.GetYear() == rhs.GetYear()) {
		if (lhs.GetMonth() == rhs.GetMonth()) {
			return lhs.Getday() < rhs.Getday();
		}
		return lhs.GetMonth() < rhs.GetMonth();
	}
	return lhs.GetYear() < rhs.GetYear();
}

std::ostream& operator << (std::ostream& stream, const Date& date) {
	stream << std::setw(4) << std::setfill('0') << date.GetYear() << "-" 
		   << std::setw(2) << std::setfill('0') << date.GetMonth() << "-" 
		   << std::setw(2) << std::setfill('0') << date.Getday();
	return stream;
}

class Database {
public:
	void AddEvent(const Date& date, const std::string& event);
	bool DeleteEvent(const Date& date, const std::string& event);
	int DeleteDate(const Date& date);

	std::set<std::string> FindEventsByDay(const Date& date) const;
	void PrintAllEvents() const;

private:
	std::map<Date, std::set<std::string>> dataBase;
};

void Database::AddEvent(const Date& date, const std::string& event) {
	if (dataBase.count(date) && dataBase[date].count(event)) {
		return;
	}
	dataBase[date].insert(event);
}

bool Database::DeleteEvent(const Date& date, const std::string& event) {
	if (dataBase.count(date) && dataBase[date].count(event)) {
		dataBase[date].erase(event);
		return true;
	}
	return false;
}

int Database::DeleteDate(const Date& date) {
	if (dataBase.count(date)) {
		size_t eventsQuantity = dataBase[date].size();
		dataBase.erase(date);
		return eventsQuantity;
	}
	return 0;
}

std::set<std::string> Database::FindEventsByDay(const Date& date) const {
	std::set<std::string> eventsByDay;
	if (dataBase.count(date)) {
		eventsByDay = dataBase.at(date);
	}
	return eventsByDay;
}

void Database::PrintAllEvents() const {
	for (const auto& item : dataBase) {
		for (const auto& value : item.second) {
			std::cout << item.first << " " << value << std::endl;
		}
	}
}

void EnsureNextSymbol(std::stringstream& stream, const std::string& str) {
	char symbol;
	stream >> symbol;
	if (symbol != '-') {
		throw std::runtime_error("Wrong date format: " + str);
	}
}

void CheckValidValue(const int& month, const int& day) {
	if (month < STARTOFMONTHS || month > ENDOFMONTHS)
		throw std::runtime_error("Month value is invalid: " + std::to_string(month));
	if (day < FIRSTDAYOFMONTH || day > LASTDAYOFMONTH)
		throw std::runtime_error("Day value is invalid: " + std::to_string(day));
}

void CheckSymbolBeforeDay(std::stringstream& stream, const std::string& str) {
	if (!stream.rdbuf()->in_avail())
		throw std::runtime_error("Wrong date format: " + str);
}

void CheckLastSymbol(std::stringstream& stream, const std::string& str) {
	if (stream.rdbuf()->in_avail())
		throw std::runtime_error("Wrong date format: " + str);
}

Date ParseDate(const std::string& str) {
	std::stringstream stream(str);
	int year = 0;
	int month = 0;
	int day = 0;
	stream >> year;
	EnsureNextSymbol(stream, str);
	stream >> month;
	EnsureNextSymbol(stream, str);
	CheckSymbolBeforeDay(stream, str);
	stream >> day;
	CheckLastSymbol(stream, str);
	CheckValidValue(month, day);
	return { year, month, day };
}

void ParseString(const std::string& command, std::string& operation, Date& date, std::string& event) {
	std::istringstream ss(command);
	std::string dateStr;
	ss >> operation;
	ss >> dateStr;
	if (dateStr == "")
		return;
	try {
		date = ParseDate(dateStr);
	}
	catch (std::runtime_error& re) {
		throw re;
	}
	ss >> event;
}

int main() {
	Database db;

	std::string command;
	while (std::getline(std::cin, command)) {
		if (command == "")
			continue;
		std::string operation;
		Date date;
		std::string event;
		try {
			ParseString(command, operation, date, event);
		}
		catch (std::runtime_error& re) {
			std::cout << re.what() << std::endl;
			return 0;
		}
		if (operation == "Add") {
			db.AddEvent(date, event);
		}
		else if (operation == "Del" && event != "") {
			if (db.DeleteEvent(date, event))
				std::cout << "Deleted successfully" << std::endl;
			else {
				std::cout << "Event not found" << std::endl;
			}
		}
		else if (operation == "Del" && event == "") {
			std::cout << "Deleted " << db.DeleteDate(date) 
					  << " events" << std::endl;
		}
		else if (operation == "Find") {
			std::set<std::string> events = db.FindEventsByDay(date);
			for (const auto& event : events) {
				std::cout << event << std::endl;
			}
		}
		else if (operation == "Print") {
			db.PrintAllEvents();
		}
		else {
			std::cout << "Unknown command: " << command << std::endl;
		}
	}

	return 0;
}
