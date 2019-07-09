/*
* Вам дан класс Logger и макрос LOG
* class Logger {
* public:
*   explicit Logger(ostream& output_stream) : os(output_stream) {
* }
*
*  void SetLogLine(bool value) { log_line = value; }
*  void SetLogFile(bool value) { log_file = value; }
*
*  void Log(const string& message);
*
* private:
*   ostream& os;
*   bool log_line = false;
*   bool log_file = false;
* };
*
* #define LOG(logger, message) ...
* 
* Параметры макроса LOG — объект класса Logger и строковое сообщение, 
* которое должно быть передано в метод Log. 
* В зависимости от настроек объекта класса Logger логируемое сообщение должно предваряться именем файла или номером строки. 
* Смотрите юнит-тесты в заготовке решения для более подробного описания поведения.
*
* Реализуйте макрос LOG так, 
* чтобы он добавлял в логируемое сообщение имя файла и номер строки в зависимости от настроек объекта logger. 
* Пришлите на проверку cpp-файл, содержащий
* - реализацию макроса LOG
* - объявление класса Logger, при этом вы можете при необходимости добавлять в него дополнительные поля и методы
* - определения всех методов класса Logger
*
* Замечание
* Если вы используете Visual Studio, у вас могут не проходить юнит-тесты из заготовки, 
* потому что в этой среде макрос __FILE__ раскрывается в абсолютный путь до файла. 
* Учитывайте это при отладке своего решения.
*/

#include <sstream>
#include <string>
using namespace std;

class Logger {
public:
	explicit Logger(ostream& output_stream) : os(output_stream) {
	}

	void SetLogLine(bool value) { log_line = value; }
	void SetLogFile(bool value) { log_file = value; }

	void Log(const string& message);

	void SetFile(const string& filename) {
		file_name_ = filename;
	}

	void SetLine(int line_number) {
		line_number_ = line_number;
	}

private:
	ostream& os;
	bool log_line = false;
	bool log_file = false;
	string file_name_;
	int line_number_;
};

void Logger::Log(const string& message) {
	if (log_file && log_line) {
		os << file_name_ << ":" << line_number_ << " ";
	}
	else if (log_file) {
		os << file_name_ << " ";
	}
	else if (log_line) {
		os << "Line " << line_number_ << " ";
	}
	os << message << "\n";
}

#define LOG(logger, message)		  \
			logger.SetFile(__FILE__); \
			logger.SetLine(__LINE__); \
			logger.Log(message)
