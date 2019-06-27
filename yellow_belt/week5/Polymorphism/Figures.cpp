/*
* Вам дана функция main, которая считывает из стандартного ввода команды по работе с набором геометрических фигур:
* int main() {
*   vector<shared_ptr<Figure>> figures;
*   for (string line; getline(cin, line); ) {
*     istringstream is(line);
*
*     string command;
*     is >> command;
*     if (command == "ADD") {
*       figures.push_back(CreateFigure(is));
*     } else if (command == "PRINT") {
*       for (const auto& current_figure : figures) {
*         cout << fixed << setprecision(3)
*              << current_figure->Name() << " "
*              << current_figure->Perimeter() << " "
*              << current_figure->Area() << endl;
*       }
*     }
*   }
*   return 0;
* }
* 
* Как видно из кода, есть два вида команд:
*
* - ADD — добавить фигуру в набор;
* - PRINT — для каждой фигуры в наборе распечатать название, периметр и площадь.
*
* Программа поддерживает три вида фигур: прямоугольник, треугольник и круг. Их добавление описывается так:
* 1) ADD RECT width height — добавить прямоугольник с размерами width и height (например, ADD RECT 2 3).
* 2) ADD TRIANGLE a b c — добавить треугольник со сторонами a, b и c (например, ADD TRIANGLE 3 4 5).
* 3) ADD CIRCLE r — добавить круг радиуса r (например, ADD CIRCLE 5).
* 
* Не меняя функцию main, реализуйте недостающие функции и классы:
*
* - базовый класс Figure с чисто виртуальными методами Name, Perimeter и Area;
* - классы Triangle, Rect и Circle, которые являются наследниками класса Figure и переопределяют его виртуальные методы;
* - функцию CreateFigure, которая в зависимости от содержимого входного потока создаёт shared_ptr<Rect>, 
* shared_ptr<Triangle> или shared_ptr<Circle>.
* Гарантируется, что все команды ADD корректны; размеры всех фигур — это натуральные числа не больше 1000. 
* В качестве значения π используйте 3,14.
*/


#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <sstream>
#include <iomanip>
#include <cmath>

using namespace std;

class Figure {
public:
	virtual string Name() const = 0;
	virtual double Perimeter() const = 0;
	virtual double Area() const = 0;
};

class Triangle : public Figure {
public:
	Triangle(const size_t& a, const size_t& b, const size_t& c) : a_(a), b_(b), c_(c) {}

	string Name() const override {
		return "TRIANGLE";
	}
	double Perimeter() const override {
		return (a_ + b_ + c_);
	}
	double Area() const override {
		double p = Perimeter() / 2;
		return sqrt(p * (p - a_) * (p - b_) * (p - c_));
	}

private:
	size_t a_, b_, c_;
};

class Rect : public Figure {
public:
	Rect(const size_t& width, const size_t& height) : width_(width), height_(height) {}

	string Name() const override {
		return "RECT";
	}
	double Perimeter() const override {
		return (2 * (width_ + height_));
	}
	double Area() const override {
		return (width_ * height_);
	}

private:
	size_t width_, height_;
};

class Circle : public Figure {
public:
	Circle(const size_t& radius) : radius_(radius) {}

	string Name() const override {
		return "CIRCLE";
	}
	double Perimeter() const override {
		double pi = 3.14;
		return (2 * pi * radius_);
	}
	double Area() const override {
		double pi = 3.14;
		return (pi * radius_ * radius_);
	}

private:
	size_t radius_;
};

shared_ptr<Figure> CreateFigure(istringstream& is) {
	string str;
	is >> str;
	if (str == "TRIANGLE") {
		size_t a = 0, b = 0, c = 0;
		is >> a;
		is >> b;
		is >> c;
		return make_shared<Triangle>(a, b, c);
	}
	else if (str == "RECT") {
		size_t width = 0, height = 0;
		is >> width;
		is >> height;
		return make_shared<Rect>(width, height);
	}
	else if (str == "CIRCLE") {
		size_t radius = 0;
		is >> radius;
		return make_shared<Circle>(radius);
	}
}


int main() {
	vector<shared_ptr<Figure>> figures;
	for (string line; getline(cin, line); ) {
		istringstream is(line);

		string command;
		is >> command;
		if (command == "ADD") {
			figures.push_back(CreateFigure(is));
		}
		else if (command == "PRINT") {
			for (const auto& current_figure : figures) {
				cout << fixed << setprecision(3)
					<< current_figure->Name() << " "
					<< current_figure->Perimeter() << " "
					<< current_figure->Area() << endl;
			}
		}
	}
	return 0;
}
