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
	//std::cout << FuncInt1.getMaxDegree()<< std::endl;
	FuncInt1.solutionOfEquation();
	std::cout << "Решение 1: ";
	FuncInt1.printSolution();


	function_class::Function<float> FuncInt2(3, true);
	std::cout << "2. " << FuncInt2 << std::endl;
	FuncInt2.solutionOfEquation();
	std::cout << "Решение 2: ";
	FuncInt2.printSolution();


	std::cout << "Сумма двух многочленов:\n";
	std::cout << FuncInt1 + FuncInt2 << std::endl;

	std::cout << "Разность двух многочленов:\n";
	std::cout << FuncInt1 - FuncInt2 << std::endl;

	std::cout << "Умножение на скаляр (func * 5)\n";
	std::cout << FuncInt2 * 5 << std::endl;

	std::cout << "Правило коммутативности (5 * func)\n";
	std::cout << 5 * FuncInt2 << std::endl;

	function_class::Function<float> FuncFloat1(3, true);
	std::cout << "2. " << FuncFloat1 << std::endl;
	FuncFloat1.solutionOfEquation();
	std::cout << "Решение 2: ";
	FuncFloat1.printSolution();
	
	function_class::Function<double> FuncDouble1(3, true);
	std::cout << "3. " << FuncDouble1 << std::endl;
	FuncDouble1.solutionOfEquation();
	std::cout << "Решение 3: ";
	FuncDouble1.printSolution();
	
	
	function_class::Function<std::complex<int>> FuncComplInt1(3, true);
	std::cout << "4. " << FuncComplInt1 << std::endl;
	function_class::Function<std::complex<float>> FuncComplFloat1(3, true);
	std::cout << "5. " << FuncComplFloat1 << std::endl;
	function_class::Function<std::complex<double>> FuncComplDouble1(3, true);
	std::cout << "6. " << FuncComplDouble1 << std::endl;
	return 0;
}
