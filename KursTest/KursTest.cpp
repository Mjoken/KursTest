﻿#include <iostream>
#include <iomanip>
#include <cmath>
#include <conio.h>

/*
Функция userInput
Проверки ввода типа int
Ввод: -
Вывод: переменная типа int
*/
int userInput()
{
	int input = 0;
	std::cin >> input;
	while (!(std::cin.good()))
	{
		std::cout << "Input error! Enter again" << std::endl;
		std::cin.clear();
		std::cin.ignore(32767, '\n');
		std::cin >> input;
	}
	return input;
}

class evaluationFunction
{
public:
	evaluationFunction(unsigned int n); // конструктор класса evaluationFunction| параметры: размер поля n*n
	~evaluationFunction();				// деструктор класса evaluationFunction 
	int evalFunc();						// функция сравнения
	void printField();					// функция вывода игрового поля в консоль поля
	void debuggingInformation();		// функция вывода отладочной информации в консоль
	void randomField();					// функция случайного заполенения поля
	void move();
	bool win();
private:
	int white;							// число белых шашек(счётчик)
	int black;							// число чёрных шашек(счётчик)
	int** field;						// указатель на начала двумерного массива поля
	unsigned int N;						// размера КВАДРАТНОГО поля
	int res;							// результат работы оценочной функции
	bool whiteMove;
	bool whiteWin;
	bool blackWin;
};

evaluationFunction::evaluationFunction(unsigned int n) : N(n), field(), res(NULL), white(0), black(0), whiteMove(true), whiteWin(false), blackWin(false)
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
	std::cout << std::endl;
	std::cout << "     ";
	for (size_t i{}; i < N; i++) {
		std::cout << std::setw(2) << "[" << i << "]";
	}
	std::cout << std::endl;
	std::cout << "     ";
	for (size_t i{}; i < N; i++) {
		std::cout << std::setw(3) << "____";
	}
	std::cout << std::endl;
	for (size_t i{}; i < N; i++) {
		std::cout << std::setw(2) << "[" << i << "]"<<"|";
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
/*



*/
void evaluationFunction::move() {
	unsigned int m{}, n{};
	int chose{}; 
	whiteMove = true;
	if (whiteMove == true) {
		std::cout << "Enter WHITE checker position[i]: ";
		m = userInput();
		std::cout << "[j]";
		n = userInput();
		if (field[m][n] == 1) {
			while (true) {
				chose = _getch();
				if ((chose == 75) || (chose == 72) || (chose == 77) || (chose == 80)) { break; }
			}
				if (chose == 72) {	// вверх
					if (m - 1 < N && field[m - 1][n] != 1 && field[m - 1][n] != -1) {
						field[m - 1][n] = field[m][n];
						field[m][n] = 0;
						whiteMove = false;
						return;
					}
					else if (m - 2 < N && field[m - 2][n] == 0 && (field[m - 1][n] == 1 || field[m - 1][n] == -1)) {
						field[m - 2][n] = field[m][n];
						field[m][n] = 0;
						whiteMove = false;
						return;
					}
					else {
						std::cout << std::endl;
						std::cout << "Whong position";
					}
				}
				if (chose == 80) { //down
					if (m + 1 < N && field[m + 1][n] != 1 && field[m + 1][n] != -1) {
						field[m + 1][n] = field[m][n];
						field[m][n] = 0;
						whiteMove = false;
						return;
					}
					else if (m + 2 < N && field[m + 2][n] ==0 && (field[m + 1][n] == 1 || field[m + 1][n] == -1)) {
						field[m + 2][n] = field[m][n];
						field[m][n] = 0;
						whiteMove = false;
						return;
					}
					else {
						std::cout << std::endl;
						std::cout << "Whong position";
					}
				}
				if (chose == 77) { // right
					if (n + 1 < N && field[m][n + 1] != 1 && field[m][n + 1] != -1) {
						field[m][n + 1] = field[m][n];
						field[m][n] = 0;
						whiteMove = false;
						return;
					}
					else if (n + 2 < N && field[m][n + 2] == 0 && (field[m][n + 1] == 1 || field[m][n + 1] == -1)) {
						field[m][n + 2] = field[m][n];
						field[m][n] = 0;
						whiteMove = false;
						return;
					}
					else {
						std::cout << std::endl;
						std::cout << "Whong position";
					}
				}
				if (chose == 75) {
					if (n - 1 < N && field[m][n - 1] != 1 && field[m][n - 1] != -1) {
						field[m][n - 1] = field[m][n];
						field[m][n] = 0;
						whiteMove = false;
						return;
					}
					else if (n - 2 < N && field[m][n - 2] == 0 && (field[m][n - 1] == 1 || field[m][n - 1] == -1)) {
						field[m][n - 2] = field[m][n];
						field[m][n] = 0;
						whiteMove = false;
						return;
					}
					else {
						std::cout << std::endl;
						std::cout << "Whong position";
					}
				}
			}
		}
		else {
			std::cout << "These no white checker";
	}
}
/*
Проверяет победил ли кто-то
Ввод: -
Вывод: -
*/
bool evaluationFunction::win() {
	if (white == 0) {
		blackWin = true;
		return blackWin;
	}
	if (black == 0) {
		whiteWin = true;
		return whiteWin;
	}
	else {
		return false;
	}
}
	/* Деструктор */
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
	unsigned int n = 8;		// Размер поля
	evaluationFunction first(n);
	first.randomField();
	first.printField();
	first.evalFunc();
	first.debuggingInformation();
	while (!first.win()) {
		first.move();
		first.printField();
	}
	return 0;
}