// Lab1.cpp: определяет точку входа для приложения.
//

#include "Lab1.h"
#include <iostream>
#include <random>
#include <complex>

//random_device rd;   // non-deterministic generator
//mt19937 gen(rd());  // to seed mersenne twister.
//uniform_int_distribution<> dist(1, 6);




int main()
{
	setlocale(LC_ALL, "ru");
	function_class::Function<int> FuncInt1(3, false);
	std::cout << "1. " << FuncInt1 << std::endl;
	FuncInt1.solutionOfEquation();
	std::cout << "Решение 1: ";
	FuncInt1.printSolution();
	function_class::Function<float> FuncInt2(3, true);
	std::cout << "2. " << FuncInt2 << std::endl;
	function_class::Function<double> FuncInt3(3, true);
	std::cout << "3. " << FuncInt3 << std::endl;
	function_class::Function<std::complex<int>> FuncInt4(3, true);
	std::cout << "4. " << FuncInt4 << std::endl;
	function_class::Function<std::complex<float>> FuncInt5(3, true);
	std::cout << "5. " << FuncInt5 << std::endl;
	function_class::Function<std::complex<double>> FuncInt6(3, true);
	std::cout << "6. " << FuncInt6 << std::endl;
	return 0;
}
