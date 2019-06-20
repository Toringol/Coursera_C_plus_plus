/*
* Вам дан заголовочный файл sum_reverse_sort.h, содержащий объявления трёх функций
*
* #pragma once
* #include <string>
* #include <vector>
* 
* using namespace std;
*
* int Sum(int x, int y);
* string Reverse(string s);
* void Sort(vector<int>& nums);
*
* Вам надо прислать cpp-файл, содержащий определения этих функций.
*/


#include "sum_reverse_sort.h"
#include <algorithm>

int Sum(int x, int y) {
	return x + y;
}

string Reverse(string s) {
	reverse(s.begin(), s.end());
	return s;
}

void Sort(vector<int>& nums) {
	sort(nums.begin(), nums.end());
}

