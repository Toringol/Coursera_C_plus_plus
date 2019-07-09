/*
* Разработать макрос UNIQ_ID, который будет формировать идентификатор, 
* уникальный в пределах данного cpp-файла. 
* Например, следующий код должен компилироваться и работать:
* int UNIQ_ID = 5;
* string UNIQ_ID = "hello!";
*
* В рамках данной задачи допускается, что код
* int UNIQ_ID = 5; string UNIQ_ID = "hello"; // оба определения на одной строке
* не будет компилироваться.
*/


#include <string>
#include <vector>
using namespace std;


#define VARIABLE1(lineCounter) variable_##lineCounter
#define VARIABLE(lineCounter) VARIABLE1(lineCounter)
#define UNIQ_ID VARIABLE(__LINE__)

int main() {
	int UNIQ_ID = 0;
	string UNIQ_ID = "hello";
	vector<string> UNIQ_ID = { "hello", "world" };
	vector<int> UNIQ_ID = { 1, 2, 3, 4 };
}
