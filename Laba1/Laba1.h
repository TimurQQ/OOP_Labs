#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

namespace Laba1 {

	struct Node {
		int y = -1;
		int value = -1;
		struct Node* next = nullptr;
	};

	struct List {
		int x = -1;
		struct Node* ptr = nullptr;
		struct List* next = nullptr;
	};

	typedef List* Matrix;

	void printVector(int* vec, int length);

	namespace FullMatrixVersion {
		Matrix input(int& m, int& n);
		void printMatrix(Matrix matrix, int& n, int& m);
		int* createVector(Matrix matrix, int& n, int& m);
	}
	
	namespace LazyVersion {
		Matrix input(int& m, int& n);
		void printMatrix(Matrix matrix, int& n, int& m);
		int* createVector(Matrix matrix, int& n, int& m);
	}
}

#endif // FUNCTIONS_H_INCLUDED