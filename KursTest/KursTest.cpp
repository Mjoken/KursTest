#include <iostream>
#include <iomanip>
int** createField(unsigned int n) {
	int** field = new int* [n];
	for (size_t i{}; i < n; i++) {
		field[i] = new int[n];
	}
	for (size_t i{}; i < n; i++) {
		for (size_t j{}; j < n; j++) {
			field[i][j] = 0;
		}
	}
	return field;
}

int evaluationFunction(int** field, unsigned int n) {
	int white = 0;
	int black = 0;
	for (size_t i{}; i < n; i++) {
		for (size_t j{}; j < n; j++) {
			if (field[i][j] == 1) white++;
			if (field[i][j] == -1) black++;
		}
	}
	return white - black;
}

void printField(int** field, unsigned int n) {
	for (size_t i{}; i < n; i++) {
		for (size_t j{}; j < n; j++) {
			std::cout << std::setw(3)<<field[i][j]<<" ";
		}
		std::cout << std::endl;
	}

}


int main() {
	unsigned int n = 7;
	
	int** field = createField(n);
	srand(time(0));
		for (size_t i{}; i < rand() % n*n; i++) {
			field[rand() % n][rand() % n] = (rand() % 3) - 1;
		}
		printField(field, n);
		std::cout<<evaluationFunction(field, n);

	return 0;
}