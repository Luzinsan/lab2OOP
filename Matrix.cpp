#include "Matrix.h"
#include <ctime>
#include <iostream>

Matrix::Matrix(int m, int n) : m_m{ (m % 10 + 1) }, m_n{ (n % 10 + 1) }
{
    array = new double* [m_m];
    std::cout << m_m << " " << m_n << std::endl;
    for (int i = 0; i < m_m; ++i)
    {
        array[i] = new double[m_n];
        for (int j = 0; j < m_n; ++j)
        { 
            array[i][j] = rand() % 100; 
            printf("%3.0f ", array[i][j]);
        }
        std::cout << std::endl;
    }
}