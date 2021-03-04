#include <iostream>
#include <climits>
#include "Laba1.h"

namespace Laba1 {
	List* createList(int x) {
		List* newList = new List();
		newList->x = x;
		newList->ptr = nullptr;
		return newList;
	}

	Node* createNode(int y, int value) {
		Node* newNode = new Node();
		newNode->y = y;
		newNode->value = value;
		return newNode;
	}

	void printVector(int* vec, int length) {
		for (int i = 0; i < length; ++i) {
			std::cout << vec[i] << ' ';
		}
		std::cout << std::endl;
	}

	namespace LazyVersion {

		 Node* lowerbound(Node* pixels, int y) {
			Node* prev = nullptr;
			Node* cur = pixels;
			while (cur && cur->y < y) {
				prev = cur;
				cur = cur->next;
			}
			return prev;
		 }

		 List* lowerbound(List* pixels, int x) {
			 List* prev = nullptr;
			 List* cur = pixels;
			 while (cur && cur->x < x) {
				 prev = cur;
				 cur = cur->next;
			 }
			 return prev;
		 }

		Node* addPixel(int x, int y, int value, Node* pixels) {
			Node* lowerYPtr = lowerbound(pixels, y);
			if (lowerYPtr) {
				if (!lowerYPtr->next || lowerYPtr->next->y != y) {
					Node* newNode = createNode(y, value);
					newNode->next = lowerYPtr->next;
					lowerYPtr->next = newNode;
					return pixels;
				}
				lowerYPtr->next->value = value;
			}
			else {
				if (pixels->y != y) {
					lowerYPtr = createNode(y, value);
					lowerYPtr->next = pixels;
					return lowerYPtr;
				}
				pixels->value = value;
			}
			return pixels;
		}

		List* addPixel(int x, int y, int value, Matrix pixels) {
			List* lowerXPtr = lowerbound(pixels, x);
			if (lowerXPtr) {
				if (!lowerXPtr->next || lowerXPtr->next->x != x) {
					List* newList = createList(x);
					newList->ptr = createNode(y, value);
					newList->next = lowerXPtr->next;
					lowerXPtr->next = newList;
					return pixels;
				}
				lowerXPtr->next->ptr = addPixel(x, y, value, lowerXPtr->next->ptr);
			}
			else {
				if (!pixels || pixels->x != x) {
					lowerXPtr = createList(x);
					lowerXPtr->ptr = createNode(y, value);
					lowerXPtr->next = pixels;
					return lowerXPtr;
				}
				pixels->ptr = addPixel(x, y, value, pixels->ptr);
			}
			return pixels;
		}

		Matrix input(int& m, int& n) {
			const char* pr = ""; // будущее сообщение об ошибке
			std::cout << "¬ведите m n: ";
			do {
				std::cout << pr << std::endl;
				pr = "You are wrong. Repeate Please!";
				std::cin >> m >> n;
				std::cin.clear(); // на случай, если предыдущий ввод завершилс€ с ошибкой
				std::cin.ignore(INT_MAX, '\n');
			} while (m < 1 || n < 1);
			
			std::cout << "¬ведите матрицу по €чейкам x y value (¬вод завершите ^Z):" << std::endl;
			Matrix pixelsArr = nullptr;
			int x = -1, y = -1, value = -1;
			while (std::cin >> x >> y >> value) {
				if (x < 0 or y < 0 or x > m - 1 or y > n - 1) {
					continue;
				}
				pixelsArr = addPixel(x, y, value, pixelsArr);
			}
			return pixelsArr;
		}

		void printMatrix(Matrix matrix, int& n, int& m) {
			int prevI = 0;
			int prevJ = 0;
			std::cout << "»сходна€ матрица:" << std::endl;
			for (List* i = matrix; i; i = i->next) {
				for (; prevI < i->x; ++prevI) {
					for (int j = 0; j < n; ++j) {
						std::cout << 0 << ' ';
					}
					std::cout << std::endl;
				}
				for (Node* j = i->ptr; j; j = j->next) {
					for (; prevJ < j->y; ++prevJ) {
						std::cout << 0 << ' ';
					}
					std::cout << j->value << ' ';
					++prevJ;
				}
				for (; prevJ < n; ++prevJ) {
					std::cout << 0 << ' ';
				}
				prevJ = 0;
				++prevI;
				std::cout << std::endl;
			}
			for (; prevI < m; ++prevI) {
				for (int j = 0; j < n; ++j) {
					std::cout << 0 << ' ';
				}
				std::cout << std::endl;
			}
		}
		
		int findDist(List* a, List* b) {
			int res = 0;
			for (Node* i = a->ptr; i; i = i->next, ++res) {
				for (Node* j = (b) ? b->ptr : nullptr; j; j = j->next) {
					if (j->value == i->value) {
						--res;
						break;
					}
				}
			}
			return res;
		}

		int* createVector(Matrix matrix, int& n, int& m) {
			int* b = new int[m];
			for (int i = 0; i < ((matrix) ? matrix->x : m); ++i) {
				b[i] = 0;
			}
			if (!matrix) return b;
			List* ptr = matrix;
			for (; ptr->next; ptr = ptr->next) {
				if (ptr->next->x - ptr->x == 1) {
					b[ptr->x] = findDist(ptr, ptr->next);
				}
				else {
					Node* cur = ptr->ptr;
					for (b[ptr->x] = 0; cur; cur = cur->next, ++b[ptr->x]);
					for (int i = ptr->x + 1; i < ptr->next->x; ++i) {
						b[i] = 0;
					}
				}
			}
			for (int i = m - 1; i > ptr->x; --i) {
				b[i] = 0;
			}
			if (ptr->x == m - 1 && matrix->x == 0) {
				b[m - 1] = findDist(ptr, matrix);
			}
			else {
				b[ptr->x] = findDist(ptr, nullptr);
			}
			return b;
		}
	}



	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



	namespace FullMatrixVersion {
		List* addPixel(int x, int y, int value, List* pixels, int& isEmpty) {
			if (isEmpty) {
				List* newList = createList(x);
				newList->ptr = createNode(y, value);
				newList->ptr->next = nullptr;
				newList->next = pixels;
				return newList;
			}
			else {
				Node* newNode = createNode(y, value);
				newNode->next = pixels->ptr;
				pixels->ptr = newNode;
				return pixels;
			}
		}

		Matrix input(int& m, int& n) {
			const char* pr = ""; // будущее сообщение об ошибке
			std::cout << "¬ведите m n: ";
			do {
				std::cout << pr << std::endl;
				pr = "You are wrong. Repeate Please!";
				std::cin >> m >> n;
				std::cin.clear(); // на случай, если предыдущий ввод завершилс€ с ошибкой
				std::cin.ignore(INT_MAX, '\n');
			} while (m < 1 || n < 1);

			std::cout << "¬ведите матрицу построчно:" << std::endl;
			Matrix pixelsArr = nullptr;
			for (int i = 0; i < m; ++i) {
				for (int j = 0, isEmpty = 1; j < n; ++j) {
					int val;
					std::cin >> val;
					if (val != 0) { 
						pixelsArr = addPixel(i, j, val, pixelsArr, isEmpty);
						isEmpty = false;
					}
				}
			}
			return pixelsArr;
		}

		void printNode(int& prevJ, Node* node, int& n, int& m) {
			if (node->next != nullptr) {
				printNode(prevJ, node->next, n, m);
			}
			for (; prevJ < node->y; ++prevJ) {
				std::cout << 0 << ' ';
			}
			if (node) std::cout << node->value << ' ';
			++prevJ;
		}

		void printRow(int& prevI, int& prevJ, List* row, int& n, int& m) {
			if (row->next != nullptr) {
				printRow(prevI, prevJ, row->next, n, m);
			}
			for (; prevI < row->x; ++prevI) {
				for (int j = 0; j < n; ++j) {
					std::cout << 0 << ' ';
				}
				std::cout << std::endl;
			}
			printNode(prevJ, row->ptr, n, m);
			for (; prevJ < n; ++prevJ) {
				std::cout << 0 << ' ';
			}
			prevJ = 0;
			++prevI;
			std::cout << std::endl;
		}

		void printMatrix(Matrix matrix, int& n, int& m) {
			int prevI = 0;
			int prevJ = 0;
			if (matrix) printRow(prevI, prevJ, matrix, n, m);
			for (; prevI < m; ++prevI) {
				for (int j = 0; j < n; ++j) {
					std::cout << 0 << ' ';
				}
				std::cout << std::endl;
			}
		}

		int findDist(List* a, List* b) {
			int res = 0;
			for (Node* i = a->ptr; i; i = i->next, ++res) {
				for (Node* j =(b) ? b->ptr : nullptr; j; j = j->next) {
					if (j->value == i->value) {
						--res;
						break;
					}
				}
			}
			return res;
		}

		int* createVector(Matrix matrix, int& n, int& m) {
			int* b = new int[m];
			for (int i = m - 1; i >= ((matrix) ? matrix->x : 0); --i) {
				b[i] = 0;
			}
			if (!matrix) return b;
			List* ptr = matrix;
			for (; ptr->next; ptr = ptr->next) {
				if (ptr->x - ptr->next->x == 1) {
					b[ptr->next->x] = findDist(ptr->next, ptr);
				}
				else {
					Node* cur = ptr->next->ptr;
					for (b[ptr->next->x] = 0; cur; cur = cur->next, ++b[ptr->next->x]);
					for (int i = ptr->next->x + 1; i < ptr->x; ++i) {
						b[i] = 0;
					}
				}
			}
			for (int i = 0; i < ptr->x; ++i) {
				b[i] = 0;
			}
			if (matrix->x == m - 1 && ptr->x == 0) {
				b[m - 1] = findDist(matrix, ptr);
			}
			else {
				b[matrix->x] = findDist(matrix, nullptr);
			}
			return b;
		}
	}
}