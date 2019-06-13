/*
* Вычислите суммарную массу имеющих форму прямоугольного параллелепипеда бетонных блоков одинаковой плотности, 
* но разного размера.
*
* Указание
* Считайте, что размеры блоков измеряются в сантиметрах, плотность — в граммах на кубический сантиметр, 
* а итоговая масса — в граммах. Таким образом, массу блока можно вычислять как простое произведение плотности на объём.
*
* Формат ввода
* В первой строке вводятся два целых положительных числа: количество блоков N и плотность каждого блока R. 
* Каждая из следующих N строк содержит три целых положительных числа W, H, D — размеры очередного блока.
*
* Гарантируется, что:
*
* - количество блоков N не превосходит 10^5;
* - плотность блоков R не превосходит 100;
* - размеры блоков W, H, D не превосходят 10^4.
*/

#include <iostream>

int main() {
	
	size_t blocksNumber = 0;
	std::cin >> blocksNumber;
	uint16_t blocksDensity = 0;
	std::cin >> blocksDensity;
	uint64_t blockVolume = 0;
	uint64_t blocksWeight = 0;

	for (size_t i = 0; i < blocksNumber; ++i) {
		uint16_t width = 0, height = 0, depth = 0;
		std::cin >> width >> height >> depth;
		blockVolume = static_cast<uint64_t>(width) * height * depth;
		blocksWeight += blockVolume * blocksDensity;
	}

	std::cout << blocksWeight << std::endl;

	return 0;
}

