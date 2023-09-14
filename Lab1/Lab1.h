// Lab1.h : включаемый файл для стандартных системных включаемых файлов
// или включаемые файлы для конкретного проекта.

#pragma once

#include <string>
#include <iostream>
#include <random>
#include <complex>
#include <typeinfo>

//for (size_t i = 0; i <= maxDegree; ++i)
//{
//	int real;
//	int image;
//	std::cout << "Введите коэффициент для \'x\' со степенью " << i << std::endl;
//	std::cout << "Real ";
//	std::cin >> coefficients[i];
//	std::cout << std::endl;
//}

namespace function_class {
	template <typename T>
	class Function {
	protected:
		void fillngCoefficientsNotRandom(int maxDegree) {
			/*if (!strcmp(typeOfT, "class std::complex<int>"))
			{
				for (size_t i = 0; i <= maxDegree; ++i)
				{
					int real;
					int image;
					std::cout << "Введите коэффициент для \'x\' со степенью " << i << std::endl;
					std::cout << "Real ";
					std::cin >> real;
					std::cout << " Image ";
					std::cin >> image;
					std::cout << std::endl;
					coefficients[i] = new std::complex<int>(real, image);
				}
			} else if (!strcmp(typeOfT, "class std::complex<float>")) {
				for (size_t i = 0; i <= maxDegree; ++i)
				{
					float real;
					float image;
					std::cout << "Введите коэффициент для \'x\' со степенью " << i << std::endl;
					std::cout << "Real ";
					std::cin >> real;
					std::cout << " Image ";
					std::cin >> image;
					std::cout << std::endl;
					coefficients[i] = new std::complex<float>(real, image);
				}
			} else if (!strcmp(typeOfT, "class std::complex<double>")) {
				for (size_t i = 0; i <= maxDegree; ++i)
				{
					double real;
					double image;
					std::cout << "Введите коэффициент для \'x\' со степенью " << i << std::endl;
					std::cout << "Real ";
					std::cin >> real;
					std::cout << " Image ";
					std::cin >> image;
					std::cout << std::endl;
					coefficients[i] = new std::complex<double>(real, image);
				}
			}*/
			if (!strcmp(typeOfT, "class std::complex<int>") ||
				!strcmp(typeOfT, "class std::complex<float>") ||
				!strcmp(typeOfT, "class std::complex<double>"))
			{
				for (size_t i = 0; i <= maxDegree; i++)
				{
					T::value_type real, image;
					std::cout << "Введите коэффициент для \'x\' со степенью " << i << std::endl;
					std::cout << "Real ";
					std::cin >> real;
					std::cout << " Image ";
					std::cin >> image;
					std::cout << std::endl;
					coefficients[i] = new std::complex<T::value_type>(real, image);
				}
			}
			else {
				for (size_t i = 0; i <= maxDegree; ++i)
				{
					std::cout << "Введите коэффициент для \'x\' со степенью " << i << std::endl;
					std::cin >> coefficients[i];
					std::cout << std::endl;
				}
			}

		}
		void fillngCoefficientsRandom(int maxDegree) {
			if (!strcmp(typeOfT, "class std::complex<int>") ||
				!strcmp(typeOfT, "class std::complex<float>") ||
				!strcmp(typeOfT, "class std::complex<double>"))
			{
				for (size_t i = 0; i <= maxDegree; i++)
				{
					T::value_type real, image;
					random_device rd;   // non-deterministic generator
					mt19937 gen(rd());  // to seed mersenne twister.
					uniform_int_distribution<> dist(0, 50);
					real = dist(gen);
					image = dist(gen);
					coefficients[i] = new std::complex<T::value_type>(real, image);
				}
			}
			else {
				for (size_t i = 0; i <= maxDegree; ++i)
				{
					random_device rd;   // non-deterministic generator
					mt19937 gen(rd());  // to seed mersenne twister.
					uniform_int_distribution<> dist(0, 50);
					coefficients[i] = dist(gen);
				}
			}
			
		}
	private:
		std::string typeOfT;
		T coefficients;
		T param;
		int maxDegree;
	public:
		Function() {
			typeOfT = typeid(coefficients).name();
		};
		Function(int maxDegree, bool random) {
			typeOfT = typeid(coefficients).name();
			coefficients = new T[maxDegree + 1];
			if (random)
				fillngCoefficientsRandom(maxDegree)
			else
				fillngCoefficientsRandom(maxDegree);
		};
	};
	template<typename T>
	std::ostream operator<< (std::ostream stream, const Function<T>& func) {

	}
}
;
// TODO: установите здесь ссылки на дополнительные заголовки, требующиеся для программы.
