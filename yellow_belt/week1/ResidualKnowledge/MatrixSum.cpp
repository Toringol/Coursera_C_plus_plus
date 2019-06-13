/*
* Условие
* В этой задаче вам надо разработать класс Matrix для представления целочисленной матрицы. 
* Более подробно класс Matrix должен иметь:

* - конструктор по умолчанию, который создаёт матрицу с нулём строк и нулём столбцов
* - конструктор от двух целочисленных параметров: num_rows и num_cols, 
* — которые задают количество строк и столбцов матрицы соответственно
* - метод Reset, принимающий два целочисленных параметра, которые задают количество строк и столбцов матрицы соответственно
* - константный метод At, который принимает номер строки и номер столбца (именно в этом порядке; 
* нумерация строк и столбцов начинается с нуля) и возвращает значение в соответствущей ячейке матрицы
* - неконстантный метод At с такими же параметрами, но возвращающий ссылку на значение в соответствущей ячейке матрицы
* - константные методы GetNumRows и GetNumColumns, которые возвращают количество строк и столбцов матрицы соответственно
* - Если количество строк или количество столбцов, переданное в конструктор класса Matrix или метод Reset, 
* оказалось отрицательным, то должно быть выброшено стандартное исключение out_of_range.
*
* Это же исключение должен бросать метод At, если переданная в него ячейка выходит за границы матрицы.
*
* Кроме того для класса Matrix должны быть определены следующие операторы:
*
* - оператор ввода из потока istream; формат ввода простой — сначала задаётся количество строк и столбцов 
* (именно в этом порядке), а затем все элементы матрицы: сначала элемент первой строки и первого столбца, 
* затем элемент первой строки и второго столбца и так далее
* - оператор вывода в поток ostream; он должен выводить матрицу в том же формате, 
* в каком её читает оператор ввода, — в первой строке количество строк и столбцов, 
* во второй — элементы первой строки, в третьей — элементы второй строки и т.д.
* - оператор проверки на равенство (==): он должен возвращать true, 
* если сравниваемые матрицы имеют одинаковый размер и все их соответствующие элементы равны между собой, 
* в противном случае он должен возвращать false.
* - оператор сложения: он должен принимать две матрицы и возвращать новую матрицу, 
* которая является их суммой; если переданные матрицы имеют разные размеры 
* этот оператор должен выбрасывать стандартное исключение invalid_argument.
*/

#include <iostream>
#include <vector>
#include <sstream>

class Matrix {
public:
	Matrix() {
		Reset(0, 0);
	}
	Matrix(const int& num_rows, const int& num_cols) {
		CheckInputMatrixRange(num_rows, num_cols);
		Reset(num_rows, num_cols);
	}

	void Reset(const int& num_rows, const int& num_cols) {
		CheckInputMatrixRange(num_rows, num_cols);
		matrix.assign(num_rows, std::vector<int>(num_cols));
	}

	int At(const int& row, const int& col) const {
		CheckMatrixRange(row, col);
		return matrix[row][col];
	}

	int& At(const int& row, const int& col) {
		CheckMatrixRange(row, col);
		return matrix[row][col];
	}

	size_t GetNumRows() const {
		return matrix.size();
	}

	size_t GetNumColumns() const {
		if (matrix.empty())
			return 0;
		return matrix[0].size();
	}
private:
	void CheckInputMatrixRange(const int& num_rows, const int& num_cols) const {
		if (num_rows < 0 || num_cols < 0)
			throw std::out_of_range("");
	}
	void CheckMatrixRange(const int& row, const int& col) const {
		if (row >= GetNumRows() || col >= GetNumColumns() || row < 0 || col < 0)
			throw std::out_of_range("");
	}
	std::vector<std::vector<int>> matrix;
};


std::istream& operator >> (std::istream& stream, Matrix& matrix) {
	int num_rows;
	int num_cols;
	stream >> num_rows;
	stream >> num_cols;
	matrix.Reset(num_rows, num_cols);
	for (size_t i = 0; i < num_rows; ++i) {
		for (size_t j = 0; j < num_cols; ++j)
			stream >> matrix.At(i, j);
	}
	return stream;
}

std::ostream& operator << (std::ostream& stream, const Matrix& matrix) {
	size_t num_rows = matrix.GetNumRows();
	size_t num_cols = matrix.GetNumColumns();
	stream << num_rows << " " << num_cols << std::endl;
	for (size_t i = 0; i < num_rows; ++i) {
		for (size_t j = 0; j < num_cols; ++j)
			stream << matrix.At(i, j) << " ";
		stream << std::endl;
	}
	return stream;
}

bool operator == (const Matrix& lhs, const Matrix& rhs) {
	size_t num_rows_lhs = lhs.GetNumRows();
	size_t num_rows_rhs = rhs.GetNumRows();
	size_t num_cols_lhs = lhs.GetNumColumns();
	size_t num_cols_rhs = rhs.GetNumColumns();
	if ((num_cols_lhs != num_cols_rhs) || (num_cols_lhs != num_cols_rhs)) {
		return false;
	}
	else {
		for (size_t i = 0; i < num_rows_lhs; ++i) {
			for (size_t j = 0; j < num_cols_lhs; ++j) {
				if (lhs.At(i, j) != rhs.At(i, j))
					return false;
			}
		}
	}
	return true;
}

Matrix operator + (const Matrix& lhs, const Matrix& rhs) {
	size_t num_rows_lhs = lhs.GetNumRows();
	size_t num_rows_rhs = rhs.GetNumRows();
	size_t num_cols_lhs = lhs.GetNumColumns();
	size_t num_cols_rhs = rhs.GetNumColumns();
	if ((num_cols_lhs != num_cols_rhs) || (num_cols_lhs != num_cols_rhs)) {
		throw std::invalid_argument("");
	}
	Matrix result(num_rows_lhs, num_cols_lhs);
	for (size_t i = 0; i < num_rows_lhs; ++i) {
		for (size_t j = 0; j < num_cols_lhs; ++j) {
			result.At(i, j) = lhs.At(i, j) + rhs.At(i, j);
		}
	}
	return result;
}

int main() {

	try {
		Matrix one;
		Matrix two;

		if (one == two)
			std::cout << "TRUE" << std::endl;
		std::cout << one + two << std::endl;

		std::cin >> one >> two;
		std::cout << one + two << std::endl;
	}
	catch (std::out_of_range& ofr) {
		std::cout << ofr.what() << std::endl;
	}

	return 0;
}
