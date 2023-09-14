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
	std::complex<int> complx( 2, 4 );
	std::cout << typeid(complx).name() << std::endl;
	std::cin >> complx;
	std::cout << complx << std::endl;
	return 0;
}
