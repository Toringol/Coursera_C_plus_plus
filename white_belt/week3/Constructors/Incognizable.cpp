/*
* Определите тип Incognizable, для которого следующий код будет корректен:
* - Incognizable a;
* -	Incognizable b = {};
* -	Incognizable c = { 0 };
* -	Incognizable d = { 0, 1 };
*/


class Incognizable {
public:
	Incognizable() {};
	Incognizable(int a) { firstNumber = a; };
	Incognizable(int a, int b) { firstNumber = a, secondNumber = b; };
private:
	int firstNumber;
	int secondNumber;
};


int main() {
	Incognizable a;
	Incognizable b = {};
	Incognizable c = { 0 };
	Incognizable d = { 0, 1 };
	return 0;
}
