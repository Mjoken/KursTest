#include <iostream>
#include <iomanip>
#include <cmath>

class evaluationFunction
{
public:
	evaluationFunction(unsigned int n); // конструктор класса evaluationFunction| параметры: размер поля n*n
	~evaluationFunction();				// деструктор класса evaluationFunction 
	int evalFunc();						// функция сравнения
	void printField();					// функция вывода игрового поля в консоль поля
	void debuggingInformation();		// функция вывода отладочной информации в консоль
	void randomField();					// функция случайного заполенения поля
private:
	int white;							// число белых шашек(счётчик)
	int black;							// число чёрных шашек(счётчик)
	int** field;						// указатель на начала двумерного массива поля
	unsigned int N;						// размера КВАДРАТНОГО поля
	int res;							// результат работы оценочной функции
};

evaluationFunction::evaluationFunction(unsigned int n) : N(n), field(), res(NULL), white(0), black(0)
{
	field = new int* [N];
	for (size_t i{}; i < N; i++) {
		field[i] = new int[N];			
	}
	for (size_t i{}; i < N; i++) {
		for (size_t j{}; j < N; j++) {
			field[i][j] = 0;
		}
	}

}
/*
Функция оценки игровой ситуации(оценочная функция)
Ввод: -
Вывод: целое, результат
*/
int evaluationFunction::evalFunc() {
	for (size_t i{}; i < N; i++) {
		for (size_t j{}; j < N; j++) {
			if (field[i][j] == 1) white++;
			if (field[i][j] == -1) black++;
		}
	}
	res = white - black;
	return res;
}
/*
Вывод игрового поля в консоль
Ввод: -
Вывод: -
*/
void evaluationFunction::printField() {
	for (size_t i{}; i < N; i++) {
		for (size_t j{}; j < N; j++) {
			std::cout << std::setw(3) << field[i][j] << " ";
		}
		std::cout << std::endl;
	}

}
/*
Вывод отладочной информации в консоль
Ввод: -
Вывод: -
*/
void evaluationFunction::debuggingInformation() {
	std::cout << std::endl << "res = " << res<<std::endl;
	std::cout << "White: " << white << "| Black: " << black << std::endl;
	if (res > 0) std::cout << "White checkers win by a margin of: " << abs(res) << std::endl;
	else if (res < 0) std::cout << "Black checkers win by a margin of: " << abs(res)<< std::endl;
	else if (res == 0) std::cout << "Draw" << std::endl;
	else {
		std::cerr << "Error in evalFunc" << std::endl;
		exit(-1);
	}
}
/*
Случайное заполение поля чёрными и белыми шашками 
Ввод: -
Вывод: -
*/
void evaluationFunction::randomField()
{
	srand(time(0));
	for (size_t i{}; i < N*N; i++) {
		field[rand() % N][rand() % N] = (rand() % 3) - 1;
	}
}

evaluationFunction::~evaluationFunction()
{
	if (field != nullptr) {
		for (size_t i{}; i < N; i++) {
			delete[] field[i];
		}
		delete[] field;
	}
}


int main() {
	unsigned int n = 10;		// Размер поля
	evaluationFunction first(n);
	first.randomField();
	first.printField();
	first.evalFunc();
	first.debuggingInformation();
	return 0;
}