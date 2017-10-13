// lab1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <locale.h>
#include <amp.h>  
#include <string>

#include <Windows.h>
#include <WinUser.h>
using namespace concurrency;

void MultiplyMatrix(int m, int n, int p) {
	double aMatrix[] = { 1.5, 4.1, 2.6, 5.2, 3.3, 6.9 };
	double bMatrix[] = { 7.4, 8.3, 9.5, 10.1, 11.22, 12.213 };
	double productMatrix[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	array_view<double, 2> a(m, n, aMatrix);
	array_view<double, 2> b(n, p, bMatrix);
	array_view<double, 2> product(m, p, productMatrix);

	parallel_for_each(
		product.extent,
		[=](index<2> idx) restrict(amp) {
		int row = idx[0];
		int col = idx[1];
		for (int inner = 0; inner < 2; inner++) {
			product[idx] += a(row, inner) * b(inner, col);
		}
	}
	);

	product.synchronize();

	for (int row = 0; row < m; row++) {
		for (int col = 0; col < p; col++) {
			//std::cout << productMatrix[row*3 + col] << "  ";  
			std::cout << product(row, col) << "  ";
		}
		std::cout << "\n";
	}
}



typedef std::vector< std::vector<double> > matX;

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
					if (!isdigit(in_num[0]))
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
		};
	};
	std::cout << "Your matrix" << std::endl;
	std::cout << mat[0][0];
	return mat;
}

int main()
{
	int m, n, p;
	std::cout << "Enter dimensions of two matrices (m, n) and (n, p):" << "\n";
	std::cout << "m = ";
	std::cin >> m;
	std::cout << "n = ";
	std::cin >> n;
	std::cout << "p = ";
	std::cin >> p;
	std::cout << "Ok!" << "\n";
	std::cout << m << ", "<< n << ", " << p << "\n";


	std::cout << "Enter first matrix" << std::endl;
	matX matA = inputMatrix(m, n);

	std::cout << "Enter second matrix" << std::endl;
	matX matB = inputMatrix(n, p);




	MultiplyMatrix(m, n, p);
	std::cout << "Press Space to exit!";
	
	while (1) {
		if (GetAsyncKeyState(VK_SPACE))
		{
			break; //User pressed space
		}
	}
	return 0;
}

