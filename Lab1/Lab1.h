// Lab1.h : включаемый файл для стандартных системных включаемых файлов
// или включаемые файлы для конкретного проекта.

#pragma once
#define _USE_MATH_DEFINES

#include <stdexcept>
#include <string>
#include <iostream>
#include <random>
#include <complex>
#include <cmath>
#include <typeinfo>


namespace function_class {
	// Абстрактный класс для всех классов Function
	template <typename T>
	class StartFunction {
	protected:
		std::string typeOfT;
		T* coefficients;
		int maxDegree;
		long double solution;
		virtual void fillngCoefficientsNotRandom(int maxDegree) { };
		virtual void fillngCoefficientsRandom(int maxDegree) { }
		void swap(StartFunction<T>& copy) noexcept{
			std::swap(this->typeOfT, copy.typeOfT);
			std::swap(this->maxDegree, copy.maxDegree);
			for (size_t i = 0; i <= this->maxDegree; i++) {
				std::swap(this->coefficients[i],copy.coefficients[i]);
			}
			this->solution;
		}
	public:
		int getMaxDegree() noexcept{ return this->maxDegree; }
		T getCoef(int index) noexcept { return this->coefficients[index]; }

		// Метод expand, резервирующих память под более
		// высокие степени с коэффициентом 0.
		void expand(size_t index) {
			if (index <= this->maxDegree + 1) { return; }

			T* cof = new T[index + 1];
			for (size_t i = 0; i <= this->maxDegree; ++i)
			{
				cof[i] = this->coefficients[i];
			}
			delete this->coefficients;
			this->coefficients = cof;
			for (size_t i = this->maxDegree + 1; i < index; ++i)
			{
				this->coefficients[i] = 0;
			}
			this->maxDegree = index;
		}

		// метод set для установки коэффициента при
		// заданной степени (обеспечить корректное поведение
		// в случае любой неотрицательной степени);
		void set(size_t index, T value) {
			if (index > this->maxDegree) {
				this->expand(index);
				this->coefficients[index] = value;
			}
			else if (index <= this->maxDegree) {
				this->coefficients[index] = value;
			}
		}

		double solutionOfEquation() {};
		
		// оператор [] для чтения коэффициента при заданной степени
		// (обеспечить корректное поведение при любой неотрицательной степени);
		T operator[](size_t degree) noexcept{
			if (degree < 0)
				throw std::runtime_error("Неверный индекс!");
			if (degree > this->maxDegree)
				return 0;
			return this->coefficients[degree];
		}
		StartFunction<T>& operator=(StartFunction<T>& func2) {
			swap(func2);
			return *this;
		}
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

		// Конструктор с параметрами: Максимальная степень многочлена
		Function(int maxDegree) {
			this->typeOfT = typeid(T).name();
			this->coefficients = new T[maxDegree + 1];
			this->maxDegree = maxDegree;
			fillngCoefficientsRandom(maxDegree);
			solutionOfEquation();
		}

		Function(int maxDegree, bool random) {
			this->typeOfT = typeid(T).name();
			this->coefficients = new T[maxDegree + 1];
			this->maxDegree = maxDegree;
			if (random)
				fillngCoefficientsRandom(maxDegree);
			else
				fillngCoefficientsNotRandom(maxDegree);
			solutionOfEquation();
		};

		// Конструктор с параметрами: Вектор значений при соответствующих степенях
		Function(std::vector<T> coef) {
			this->typeOfT = typeid(T).name();
			this->maxDegree = coef.size() - 1;
			this->coefficients = new T[this->maxDegree + 1];
			for (size_t i = 0; i <= this->maxDegree; ++i) {
				this->coefficients[i] = coef[i];
			}
			solutionOfEquation();
		};
		Function(Function<T>& const func) {
			this->typeOfT = func.typeOfT;
			this->maxDegree = func.maxDegree;
			this->coefficients = new T[this->maxDegree + 1];
			for (size_t i = 0; i <= this->maxDegree; i++){
				this->coefficients[i] = func.coefficients[i];
			}
			solutionOfEquation();
		}

		// Функция, находящая корни кубического уравнения
		void solutionOfEquation() {
			T	a = this->coefficients[3],
				b = this->coefficients[2],
				c = this->coefficients[1],
				d = this->coefficients[0];
			// Решение правильное по формуле из википедии
			long double p = (((long double)3 * a * c - powl((long double)b, 2) ) / ((long double)3 * powl((long double)a, 2) ) );
			//std::cout << "p = " << p << std::endl;
			long double q = ((long double)2 * powf((long double)b, 3) - (long double)9 * a * b * c + (long double)27 * powf((long double)a, 2) * d) / (long double)(27 * powf((long double)a, 3));
			//std::cout << "q = " << q << std::endl;
			long double Q = powl((long double)p / 3, 3) + powl((long double)q / 2, 2);
			//std::cout << "Q = " << Q << std::endl;
			long double alpha = cbrtl(-((long double)q / 2) + sqrtl(Q));
			//std::cout << "alpha = " << alpha << std::endl;
			long double beta = cbrtl(-((long double)q / 2) - sqrtl(Q));
			//std::cout << "beta = " << beta << std::endl;
			this->solution = (long double)(alpha + beta) - ((long double)b / ((long double)3 * (long double)a));



			
		};
		void printSolution() noexcept {
			std::cout << this->solution << std::endl;
		};

		// Оператор сложения с объектом такого же типа или другого
		template <typename N>
		Function<double>& operator +(StartFunction<N> secObj) {
			auto maxDegree_ = (this->maxDegree > secObj.getMaxDegree()) ? this->maxDegree : secObj.getMaxDegree();
			std::vector<double> cof(maxDegree_ + 1);
			for (size_t i = 0; i <= maxDegree_; i++)
			{
				if (i > this->maxDegree) {
					cof[i] = double(secObj[i]);
					continue;
				}
				else if (i > secObj.getMaxDegree()) {
					cof[i] = double(this->coefficients[i]);
					continue;
				}
				cof[i] = double(secObj[i]) + double(this->coefficients[i]);
			}
			Function<double>* func = new Function<double>(cof);
			return *func;
		}
		
		// Оператор вычитания с объектом такого же типа или другого
		template <typename N>
		Function<double>& operator -(StartFunction<N> secObj) {
			auto maxDegree_ = (this->maxDegree > secObj.getMaxDegree()) ? this->maxDegree : secObj.getMaxDegree();
			std::vector<double> cof(maxDegree_ + 1);
			for (size_t i = 0; i <= maxDegree_; i++)
			{
				if (i > this->maxDegree) {
					cof[i] = -double(secObj[i]);
					continue;
				}
				else if (i > secObj.getMaxDegree()) {
					cof[i] = double(this->coefficients[i]);
					continue;
				}
				cof[i] = double(secObj[i]) - double(this->coefficients[i]);
			}
			Function<double>* func = new Function<double>(cof);
			return *func;
		}
		
		// Оператор умножения и поддержка коммутативности
		template <typename N>
		Function<double>& operator *(N scalar) {
			std::vector<double> cof(this->maxDegree + 1);
			for (size_t i = 0; i <= this->maxDegree; i++)
			{
				cof[i] = scalar * double(this->coefficients[i]);
			}
			Function<double>* func = new Function<double>(cof);
			return *func;
		}
		template <typename N>
		friend Function<double>& operator *(N scalar, Function<T>& func) {
			std::vector<double> cof(func.getMaxDegree() + 1);
			for (size_t i = 0; i <= func.getMaxDegree(); i++)
			{
				cof[i] = scalar * double(func.getCoef(i));
			}
			Function<double>* new_func = new Function<double>(cof);
			return *new_func;
		}

		// вычисление значения многочлена при указанном значении х.
		template <typename N>
		double calculation(N x) {
			double result = 0;
			for (size_t i = 0; i < this->getMaxDegree() + 1; ++i)
			{
				result += powl(x, i) * double(this->getCoef(i));
			}
			return result;
		}

		// метод shrink_to_fit уменьшающий размер многочлена до
		// минимально возможного при наличии ведущих нулей
		void shrink_to_fit() {
			int fitMaxDegree = this->maxDegree;

			for (size_t i = fitMaxDegree; i > 0 ; --i)
			{
				if (this->coefficients[i] == 0) {
					--fitMaxDegree;
				}
				else if((this->coefficients[i] != 0)) {
					break;
				}
			}
			if (fitMaxDegree == this->maxDegree)
			{
				return;
			}
			this->maxDegree = fitMaxDegree;
			T* newCoef = new T[this->maxDegree + 1];
			for (size_t i = 0; i <= this->maxDegree; ++i)
			{
				newCoef[i] = this->coefficients[i];
			}
			delete this->coefficients;
			this->coefficients = newCoef;
		}

		
		

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
