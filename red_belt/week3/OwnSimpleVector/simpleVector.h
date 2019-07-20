#pragma once

#include <cstdlib>

template <typename T>
class SimpleVector {
public:
	SimpleVector();
	explicit SimpleVector(size_t size);
	~SimpleVector();

	T& operator[](size_t index);

	T* begin();
	T* end();

	size_t Size() const;
	size_t Capacity() const;

	void PushBack(const T& value);

private:
	T* data;
	size_t size_vec;
	size_t capacity_vec;
};

template <typename T>
SimpleVector<T>::SimpleVector() {
	data = nullptr;
	capacity_vec = 0;
	size_vec = 0;
}

template <typename T>
SimpleVector<T>::SimpleVector(size_t size) {
	data = new T[size];
	capacity_vec = size;
	size_vec = size;
}

template <typename T>
SimpleVector<T>::~SimpleVector() {
	delete[] data;
}

template <typename T>
T& SimpleVector<T>::operator[](size_t index) {
	return data[index];
}

template <typename T>
T* SimpleVector<T>::begin() {
	return data;
}

template <typename T>
T* SimpleVector<T>::end() {
	return data + size_vec;
}

template <typename T>
size_t SimpleVector<T>::Size() const {
	return size_vec;
}

template <typename T>
size_t SimpleVector<T>::Capacity() const {
	return capacity_vec;
}

template <typename T>
void SimpleVector<T>::PushBack(const T& value) {
	if (size_vec == capacity_vec && capacity_vec == 0) {
		capacity_vec = 1;
		data = new T[capacity_vec];
	}
	else if (size_vec == capacity_vec) {
		capacity_vec *= 2;
		T* newData = new T[capacity_vec];
		for (size_t i = 0; i < size_vec; ++i) {
			newData[i] = data[i];
		}
		delete[] data;
		data = newData;
	}
	data[size_vec] = value;
	size_vec++;
}
