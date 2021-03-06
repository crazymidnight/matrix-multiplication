// matmul.cpp: определяет точку входа для консольного приложения.

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>
#include <WinUser.h>


// объявления типа матрицы
typedef std::vector< std::vector<double> > matX;

// функция перемножения матриц
matX multiplyMatrix(int m, int n, int p, matX matA, matX matB) {
	matX matC(m, std::vector<double>(p));

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < p; j++)
		{
			matC[i][j] = 0;
			for (int k = 0; k < n; k++)
			{
				matC[i][j] += matA[i][k] * matB[k][j];
				
			}
		}
	}
	std::cout << "===" << matC[0][0] << std::endl;
	return matC;
}

// функция ввода матрицы
matX inputMatrix(int m, int n)
{
	double num;
	std::string in_num;
	bool successful;
	matX mat(m, std::vector<double>(n));
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			successful = false;
			while (!successful)
			{
				std::cout << "Element " << i << ", " << j << std::endl;
				std::cin >> in_num;
				try
				{
					if (!isdigit(in_num[0]) && in_num[0] != '-' || !isdigit(in_num[1]) && in_num[0] == '-')
					{
						throw 1;
					}
					const char * c_str = in_num.c_str();
					num = std::atof(c_str);
					mat[i][j] = num;
					successful = true;
				}
				catch (int i)
				{
					std::cout << "It's not a number! Try again!" << std::endl;
					continue;
				}
			}
		}
	}
	std::cout << "Your matrix" << std::endl;
	std::cout << mat[0][0];
	return mat;
}
// функция ввода размерности матриц
int inputDim()
{
	int m;
	std::string in_num;
	bool successful;
	successful = false;
	while (!successful)
	{
		try
		{
			std::cin >> in_num;
			if (!isdigit(in_num[0]))
			{
				throw 1;
			}

			const char * c_str = in_num.c_str();
			m = atoi(c_str);
			successful = true;
		}

		catch (int i)
		{
			if (i == 1) std::cout << "Type error! Enter integer number" << std::endl;
			continue;
		}
	}
	return m;
}

// функция вывода матрицы
void showMat(int m, int n, matX mat)
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
			std::cout << mat[i][j] << "    ";
		std::cout << std::endl;
	}
}

int main()
{
	int m, n, p;
	matX matA;
	matX matB;
	matX matC;

	
	std::cout << "Enter dimensions of two matrices (m, n) and (n, p):" << "\n";
	
	std::cout << "m = ";
	m = inputDim();
	std::cout << "n = ";
	n = inputDim();
	std::cout << "p = ";
	p = inputDim();
	std::cout << "Ok!" << std::endl;
	std::cout << m << ", "<< n << ", " << p << std::endl;


	std::cout << "Enter first matrix" << std::endl;
	matA = inputMatrix(m, n);

	std::cout << "Enter second matrix" << std::endl;
	matB = inputMatrix(n, p);

	matC = multiplyMatrix(m, n, p, matA, matB);

	std::cout << "Matrix A:" << std::endl;
	showMat(m, n, matA);

	std::cout << "Matrix B:" << std::endl;
	showMat(n, p, matB);

	std::cout << "The result of multiplying:" << std::endl;
	showMat(m, p, matC);
	
	std::cout << "Press Space to exit!";
	
	while (1) {
		if (GetAsyncKeyState(VK_SPACE))
		{
			break; //User pressed space
		}
	}
	return 0;
}

