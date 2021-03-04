#include <iostream>
#include <cstdlib>
#include <algorithm>
#include "Laba1.h"

#define LAZY_INPUT

#ifdef LAZY_INPUT
using namespace Laba1::LazyVersion;
#else
using namespace Laba1::FullMatrixVersion;
#endif
using namespace Laba1;

bool lessCompare(int x, int y) {
	return x < y;
}

bool greaterCompare(int x, int y) {
	return x > y;
}

int main() {
	int m, n;
	system("chcp 1251 && cls");
	Matrix p = input(m, n);
	printMatrix(p, n, m);
	int* b = createVector(p, n, m);
	std::cout << std::endl << "Полученный вектор b[]:";
	printVector(b, m);
	if (m > 1) {
		std::sort(b, b + m, (b[0] < b[1]) ? lessCompare : greaterCompare);
	}
	std::cout << std::endl << "Упорядоченный вектор b[]: ";
	printVector(b, m);
	return 0;
}