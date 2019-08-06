/*
* В видеолекции мы с вами познакомились с конструктором копирования и оператором присваивания, 
* а также написали конструктор копирования для SimpleVector. 
* В этой задаче вам нужно реализовать оператор присваивания для SimpleVector.
*
* Напомним, что следующий код вызывает конструктор копирования:
* SimpleVector<int> source(5);
* SimpleVector<int> dest = source; // Конструктор копирования
*
* А код ниже — оператор присваивания:
* SimpleVector<int> source(5);
* SimpleVector<int> dest;
* dest = source; // Оператор присваивания
*/

#include "simple_vector.h"
#include "test_runner.h"

#include <numeric>
#include <vector>
#include <tuple>

using namespace std;

void TestCopyAssignment() {
	SimpleVector<int> numbers(10);
	iota(numbers.begin(), numbers.end(), 1);

	SimpleVector<int> dest;
	ASSERT_EQUAL(dest.Size(), 0u);

	dest = numbers;
	ASSERT_EQUAL(dest.Size(), numbers.Size());
	ASSERT(dest.Capacity() >= dest.Size());
	ASSERT(equal(dest.begin(), dest.end(), numbers.begin()));
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestCopyAssignment);
}
