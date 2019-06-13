/*
* Решите задачу «Средняя температура» в других ограничениях на входные данные.
* 
* Даны значения температуры, наблюдавшиеся в течение N подряд идущих дней. 
* Найдите номера дней (в нумерации с нуля) со значением температуры выше среднего арифметического за все N дней.
*
* Гарантируется, что среднее арифметическое значений температуры является целым числом.
*
* Формат ввода
* Вводится число N, затем N целых чисел — значения температуры в 0-й, 1-й, ... (N−1)-й день. 
* Гарантируется, что N не превышает миллиона (10^6), а значения температуры, 
* измеряющиеся в миллионных долях градусов по Цельсию, лежат в диапазоне от −10^8 до 10^8. 
* Проверять соблюдение этих ограничений не нужно: 
* вы можете ориентироваться на них при выборе наиболее подходящих типов для переменных.
*
* Формат вывода
* Первое число K — количество дней, значение температуры в которых выше среднего арифметического. 
* Затем K целых чисел — номера этих дней.
*/

#include <iostream>
#include <vector>

std::vector<size_t> CheckHighThanAvarageDays(const std::vector<int>& temperature) {
	std::vector<size_t> avarageDays;
	int64_t sumTemperature = 0;
	for (const auto& day : temperature)
		sumTemperature += day;
	int avarageTemperature = sumTemperature / static_cast<int>(temperature.size());
	for (size_t i = 0; i < temperature.size(); ++i) {
		if (temperature[i] > avarageTemperature)
			avarageDays.push_back(i);
	}
	return avarageDays;
}

int main() {
	
	size_t daysNumber = 0;
	std::cin >> daysNumber;
	std::vector<int> temperature(daysNumber);

	for (auto& day : temperature) {
		std::cin >> day;
	}

	std::vector<size_t> avarageDays = CheckHighThanAvarageDays(temperature);

	std::cout << avarageDays.size() << std::endl;
	for (const auto& index : avarageDays) {
		std::cout << index << " ";
	}
	std::cout << std::endl;

	return 0;
}

