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
