#pragma once

#include <stdexcept>
using namespace std;

template <typename T, size_t N>
class StackVector {
public:
	explicit StackVector(size_t a_size = 0);

	T& operator[](size_t index);
	const T& operator[](size_t index) const;

	T* begin();
	T* end();
	const T* begin() const;
	const T* end() const;

	size_t Size() const;
	size_t Capacity() const;

	void PushBack(const T& value);
	T PopBack();

private:
	T data[N];
	size_t size = 0;
	size_t capacity = N;
};

template <typename T, size_t N>
StackVector<T, N>::StackVector(size_t a_size) {
	if (a_size > N) {
		throw invalid_argument("");
	}
	size = a_size;
}

template <typename T, size_t N>
T& StackVector<T, N>::operator[](size_t index) {
	return data[index];
}

template <typename T, size_t N>
const T& StackVector<T, N>::operator[](size_t index) const {
	return data[index];
}

template <typename T, size_t N>
T* StackVector<T, N>::begin() {
	return data;
}

template <typename T, size_t N>
T* StackVector<T, N>::end() {
	return data + size;
}

template <typename T, size_t N>
const T* StackVector<T, N>::begin() const {
	return data;
}

template <typename T, size_t N>
const T* StackVector<T, N>::end() const {
	return data + size;
}

template <typename T, size_t N>
size_t StackVector<T, N>::Size() const {
	return size;
}

template <typename T, size_t N>
size_t StackVector<T, N>::Capacity() const {
	return capacity;
}

template <typename T, size_t N>
void StackVector<T, N>::PushBack(const T& value) {
	if (size == capacity) {
		throw overflow_error("");
	}
	data[size] = value;
	++size;
}

template <typename T, size_t N>
T StackVector<T, N>::PopBack() {
	if (size == 0) {
		throw underflow_error("");
	}
	--size;
	return data[size];
}
