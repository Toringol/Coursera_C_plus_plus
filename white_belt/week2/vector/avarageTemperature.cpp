/*
* Даны значения температуры, наблюдавшиеся в течение N подряд идущих дней.
* Найдите номера дней (в нумерации с нуля) со значением температуры выше среднего арифметического за все N дней.
*
* Гарантируется, что среднее арифметическое значений температуры является целым числом.

* Формат ввода
* Вводится число N, затем N неотрицательных целых чисел — значения температуры в 0-й, 1-й, ... (N−1)-й день.
*
* Формат вывода
* Первое число K — количество дней, значение температуры в которых выше среднего арифметического.
* Затем K целых чисел — номера этих дней.
*/

#include <iostream>
#include <vector>

std::vector<size_t> avarageTemperature(const std::vector<size_t>& temperature) {
	size_t sum = 0;
	for (auto day : temperature)
		sum += day;
	size_t avarageAriphmetic = sum / temperature.size();
	std::vector<size_t> result;
	for (size_t i = 0; i < temperature.size(); ++i) {
		if (temperature[i] > avarageAriphmetic)
			result.push_back(i);
	}
	return result;
}

int main() {
	size_t daysNumber, sum;
	std::cin >> daysNumber;
	std::vector<size_t> temperature(daysNumber);
	for (auto& day : temperature)
		std::cin >> day;

	std::vector<size_t> result = avarageTemperature(temperature);

	std::cout << result.size() << std::endl;
	for (auto value : result)
		std::cout << value << " ";

	return 0;
}
