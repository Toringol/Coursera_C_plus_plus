/*
* Односвязный список — классический пример структуры данных, 
* для реализации которой нужно пользоваться памятью в куче. 
* В этой задаче вам нужно реализовать шаблон класса LinkedList, 
* который представляет собой односвязный список и обладает следующим интерфейсом:
* - Метод GetHead возвращает указатель на голову списка, 
* он используется для перебора элементов списка (см. шаблон ToVector в заготовке решения)
* - Метод PushFront добавляет новый элемент в голову списка.
* - Метод InsertAfter вставляет новый элемент в список так, чтобы он шёл после узла node. 
* Если node == nullptr, метод эквивалентен PushFront
* - Метод PopFront удаляет элемент из головы списка и освобождает выделенную под него память. 
* Если список пуст, метод завершается корректно. Если после выполнения метода список стал пустым, 
* метод GetHead должен возвращать nullptr
* - Метод RemoveAfter должен удалять из списка элемент, который следует за узлом node, 
* и освобождать выделенную под него память. Если node == nullptr, метод эквивалентен PopFront. 
* Если node->next == nullptr, то метод должен корректно завершаться.
* - Все методы, перечисленные выше, должны работать за O(1)
* - Деструктор класса LinkedList освобождает всю память, выделенную для хранения элементов списка.
*/

#include "test_runner.h"

#include <vector>
using namespace std;

template <typename T>
class LinkedList {
public:
	struct Node {
		T value;
		Node* next = nullptr;
	};

	~LinkedList() {
		while (head) {
			PopFront();
		}
	}

	void PushFront(const T& value) {
		Node* newNode = new Node;
		newNode->next = head;
		newNode->value = value;
		head = newNode;
	}

	void InsertAfter(Node* node, const T& value) {
		if (node == nullptr) {
			PushFront(value);
		}
		else {
			Node* Current = node;
			if (Current->next == nullptr) {
				Node* newNode = new Node;
				Current->next = newNode;
				newNode->value = value;
			}
			else {
				Node* newNode = new Node;
				newNode->next = Current->next;
				Current->next = newNode;
				newNode->value = value;
			}
		}
	}
	void RemoveAfter(Node* node) {
		if (node == nullptr) {
			PopFront();
		}
		else {
			Node* Current = node;
			if (Current->next != nullptr && Current->next->next == nullptr) {
				Node* oldNode = Current->next;
				delete oldNode;
				Current->next = nullptr;
			}
			else if (Current->next != nullptr && Current->next->next != nullptr) {
				Node* oldNode = Current->next;
				Current->next = oldNode->next;
				delete oldNode;
			}
		}
	}

	void PopFront() {
		if (head) {
			Node* newHead = head->next;
			delete head;
			head = newHead;
		}
	}

	Node* GetHead() { return head; }
	const Node* GetHead() const { return head; }

private:
	Node* head = nullptr;
};

template <typename T>
vector<T> ToVector(const LinkedList<T>& list) {
	vector<T> result;
	for (auto node = list.GetHead(); node; node = node->next) {
		result.push_back(node->value);
	}
	return result;
}

void TestPushFront() {
	LinkedList<int> list;

	list.PushFront(1);
	ASSERT_EQUAL(list.GetHead()->value, 1);
	list.PushFront(2);
	ASSERT_EQUAL(list.GetHead()->value, 2);
	list.PushFront(3);
	ASSERT_EQUAL(list.GetHead()->value, 3);

	const vector<int> expected = { 3, 2, 1 };
	ASSERT_EQUAL(ToVector(list), expected);
}

void TestInsertAfter() {
	LinkedList<string> list;

	list.PushFront("a");
	auto head = list.GetHead();
	ASSERT(head);
	ASSERT_EQUAL(head->value, "a");

	list.InsertAfter(head, "b");
	const vector<string> expected1 = { "a", "b" };
	ASSERT_EQUAL(ToVector(list), expected1);

	list.InsertAfter(head, "c");
	const vector<string> expected2 = { "a", "c", "b" };
	ASSERT_EQUAL(ToVector(list), expected2);
}

void TestRemoveAfter() {
	LinkedList<int> list;
	for (int i = 1; i <= 5; ++i) {
		list.PushFront(i);
	}

	const vector<int> expected = { 5, 4, 3, 2, 1 };
	ASSERT_EQUAL(ToVector(list), expected);

	auto next_to_head = list.GetHead()->next;
	list.RemoveAfter(next_to_head);
	list.RemoveAfter(next_to_head); 

	const vector<int> expected1 = { 5, 4, 1 };
	ASSERT_EQUAL(ToVector(list), expected1);

	while (list.GetHead()->next) {
		list.RemoveAfter(list.GetHead());
	}
	ASSERT_EQUAL(list.GetHead()->value, 5);
}

void TestPopFront() {
	LinkedList<int> list;

	for (int i = 1; i <= 5; ++i) {
		list.PushFront(i);
	}
	for (int i = 1; i <= 5; ++i) {
		list.PopFront();
	}
	ASSERT(list.GetHead() == nullptr);
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestPushFront);
	RUN_TEST(tr, TestInsertAfter);
	RUN_TEST(tr, TestRemoveAfter);
	RUN_TEST(tr, TestPopFront);
	return 0;
}
