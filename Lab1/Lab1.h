// Lab1.h : включаемый файл для стандартных системных включаемых файлов
// или включаемые файлы для конкретного проекта.

#pragma once
#define _USE_MATH_DEFINES

#include <string>
#include <iostream>
#include <random>
#include <complex>
#include <cmath>
#include <typeinfo>


namespace function_class {
	template <typename T>
	class StartFunction {
	protected:
		std::string typeOfT;
		T* coefficients;
		T param;
		int maxDegree;
		double solution;
		virtual void fillngCoefficientsNotRandom(int maxDegree) { };
		virtual void fillngCoefficientsRandom(int maxDegree) { }
	public:
		int getMaxDegree() { return this->maxDegree; }
		T getCoef(int index) { return this->coefficients[index]; }
		double solutionOfEquation() {};
		~StartFunction() = default;
	};


	template <typename T>
	class Function : public StartFunction<T> {
	protected:
		void fillngCoefficientsNotRandom(int maxDegree) {
			for (size_t i = 0; i <= maxDegree; ++i)
			{
				std::cout << "Введите коэффициент для \'x\' со степенью " << i << std::endl;
				std::cin >> this->coefficients[i];
				std::cout << std::endl;
			}
		}
		void fillngCoefficientsRandom(int maxDegree) {
			if (!strcmp(this->typeOfT.c_str(), "float") ||
				!strcmp(this->typeOfT.c_str(), "double"))
			{
				std::random_device rd;   // non-deterministic generator
				std::mt19937 gen(rd());  // to seed mersenne twister.
				std::uniform_real_distribution<> dist(0, 20);
				for (size_t i = 0; i <= maxDegree; ++i)
				{
					this->coefficients[i] = dist(gen);
				}
			}
			else {
				std::random_device rd;   // non-deterministic generator
				std::mt19937 gen(rd());  // to seed mersenne twister.
				std::uniform_int_distribution<> dist(0, 20);
				for (size_t i = 0; i <= maxDegree; ++i)
				{
					this->coefficients[i] = dist(gen);
				}
			}
		}
	public:
		Function() {
			this->typeOfT = typeid(T).name();
		};
		Function(int maxDegree, bool random) {
			this->typeOfT = typeid(T).name();
			this->coefficients = new T[maxDegree + 1];
			this->maxDegree = maxDegree;
			if (random)
				fillngCoefficientsRandom(maxDegree);
			else
				fillngCoefficientsNotRandom(maxDegree);
		};
		
		void solutionOfEquation() {
			T	a = this->coefficients[3],
				b = this->coefficients[2],
				c = this->coefficients[1],
				d = this->coefficients[0];
			// Решение правильное по формуле из википедии
			long double p = ( ( 3 * a * c - pow((long double)b, 2) ) / ( 3 * pow((long double)a, 2) ) );
			long double q = (2 * pow((long double)b, 3) - 9 * a * b * c + 27 * pow((long double)a, 2) * d) / 27 * pow((long double)a, 3);
			long double Q = pow((long double)p / 3, 3) + pow((long double)q / 2, 2);
			long double alpha = cbrt(-(q / 2) + sqrt(Q));
			long double beta = cbrt(-(q / 2) - sqrt(Q));
			this->solution[0] = (alpha + beta) - ((long double)b / 3 * (long double)a);
		};
		void printSolution() {
			std::cout << this->solution[0] << std::endl;
		};

		~Function() {
			delete[] this->coefficients;
		}
	};

	template<typename T>
	class Function<std::complex<T>> : public StartFunction<std::complex<T>> {
		void fillngCoefficientsNotRandom(int maxDegree) {
			for (size_t i = 0; i <= maxDegree; i++)
			{
				double real;
				double image;
				std::cout << "Введите коэффициент для \'x\' со степенью " << i << std::endl;
				std::cout << "Real ";
				std::cin >> real;
				std::cout << " Image ";
				std::cin >> image;
				std::cout << std::endl;
				this->coefficients[i] = *(new std::complex<T>(real, image));
			}
		}
		void fillngCoefficientsRandom(int maxDegree) {
			if (!strcmp(this->typeOfT.c_str(), "class std::complex<float>") ||
				!strcmp(this->typeOfT.c_str(), "class std::complex<double>"))
			{
				for (size_t i = 0; i <= maxDegree; i++)
				{
					double real;
					double image;
					std::random_device rd;   // non-deterministic generator
					std::mt19937 gen(rd());  // to seed mersenne twister.
					std::uniform_real_distribution<> dist(0, 100);
					real = dist(gen);
					image = dist(gen);
					this->coefficients[i] = *(new std::complex<T>(real, image));
				}
			}
			else {
				for (size_t i = 0; i <= maxDegree; i++)
				{
					int real;
					int image;
					std::random_device rd;   // non-deterministic generator
					std::mt19937 gen(rd());  // to seed mersenne twister.
					std::uniform_real_distribution<> dist(0, 50);
					real = dist(gen);
					image = dist(gen);
					this->coefficients[i] = *(new std::complex<T>(real, image));
				}
			}
			
		}
	public:
		Function() {
			this->typeOfT = typeid(std::complex<T>).name();
		};
		Function(int maxDegree, bool random) {
			this->typeOfT = typeid(std::complex<T>).name();
			this->coefficients = new std::complex<T>[maxDegree + 1];
			this->maxDegree = maxDegree;
			if (random)
				fillngCoefficientsRandom(maxDegree);
			else
				fillngCoefficientsNotRandom(maxDegree);
		};
		~Function() {
			delete[] this->coefficients;
		}
	};


	template<typename T>
	std::ostream& operator<< (std::ostream& stream,  Function<T>& func) {
		int maxIndex = func.getMaxDegree();
		stream << "f(x) = ";
		stream << func.getCoef(0) << "x^" << 0;
		for (size_t i = 1; i <= maxIndex; i++)
		{
			stream << " + " << func.getCoef(i) << "x^" << i ;
		}
		return stream;
	};
};
	


	



	
// TODO: установите здесь ссылки на дополнительные заголовки, требующиеся для программы.
