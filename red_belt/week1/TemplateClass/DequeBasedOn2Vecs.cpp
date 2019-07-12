/*
* Условие
* Напишите шаблонный класс Deque, содержащий следующий набор методов:
* - конструктор по умолчанию;
* - константный метод Empty, возвращающий true, если дек не содержит ни одного элемента;
* - константный метод Size, возвращающий количество элементов в деке;
* - T& operator[](size_t index) и const T& operator[](size_t index) const;
* - константный и неконстантный метод At(size_t index), генерирующий стандартное исключение out_of_range, 
* если индекс больше или равен количеству элементов в деке;;
* - константные и неконстантные версии методов Front и Back, возвращающих ссылки на первый и последний элемент дека соответственно;
* - методы PushFront и PushBack.
*
* Неконстантные версии методов должны позволять изменять соответствующий элемент дека.
*
* Для реализации заведите внутри класса Deque два вектора: в один осуществляйте вставку в методе PushFront, 
* а в другой — в методе PushBack.
* 
* Замечание
* Заголовочный файл, который вы пришлёте на проверку, не должен подключать файлы <list>, <deque>, <set>, <map>. 
* Если у вас будет подключен один из этих файлов, вы получите ошибку компиляции.
*/


#include <vector>
#include <stdexcept>

using namespace std;

template <typename T>
class Deque {
public:
	Deque() {}
	
	bool Empty() const {
		if (frontVec.empty() && backVec.empty())
			return true;
		return false;
	}
	size_t Size() const {
		if (Empty())
			return 0;
		return (frontVec.size() + backVec.size());
	}

	T& operator[] (size_t index) {
		return At(index);
	}
	const T& operator[] (size_t index) const {
		return At(index);
	}

	T& At(size_t index) {
		if (index >= Size())
			throw out_of_range("");
		if (index >= frontVec.size())
			return backVec[index - frontVec.size()];
		return frontVec[frontVec.size() - 1 - index];
	}
	const T& At(size_t index) const {
		if (index >= Size())
			throw out_of_range("");
		if (index >= frontVec.size())
			return backVec.at(index - frontVec.size());
		return frontVec.at(frontVec.size() - 1 - index);
	}

	T& Front() {
		if (Empty())
			throw out_of_range("");
		return At(0);
	}
	T& Back() {
		if (Empty())
			throw out_of_range("");
		return At(Size() - 1);
	}
	const T& Front() const {
		if (Empty())
			throw out_of_range("");
		return At(0);
	}
	const T& Back() const {
		if (Empty())
			throw out_of_range("");
		return At(Size() - 1);
	}

	void PushFront(T value) {
		frontVec.push_back(value);
	}
	void PushBack(T value) {
		backVec.push_back(value);
	}

private:
	std::vector<T> frontVec;
	std::vector<T> backVec;
};

int main() {
	
	return 0;
}
