/*
* Реализуйте шаблонную функцию GetRefStrict, которая на вход принимает: map и значение ключа k. 
* Если элемент по ключу k в коллекции отсутствует, то функция должна бросить исключение runtime_error, 
* иначе вернуть ссылку на элемент в коллекции.
*
* Пример использования функции
*/

#include <iostream>
#include <map>
#include <string>

template <typename Key, typename Value>
Value& GetRefStrict(std::map<Key, Value>& m, Key key) {
	if (m.count(key))
		return m[key];
	else {
		throw std::runtime_error("");
	}
}

int main() {

	try {
		std::map<int, std::string> m = { {0, "value"} };
		std::string& item = GetRefStrict(m, 0);
		item = "newvalue";
		std::cout << m[0] << std::endl; // выведет newvalue
	}
	catch (std::runtime_error& re) {
		std::cout << re.what() << std::endl;
	}

	return 0;
}
