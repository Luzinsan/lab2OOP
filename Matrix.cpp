#include "Matrix.h"

namespace luzalex
{
    Matrix::Matrix(int m, int n) : m_m{ (m % 11) }, m_n{ (n % 11) }
    {
        std::cout << "Конструктор с параметрами m = " << m << " и n = " << n << std::endl;
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

    Matrix::Matrix(const Matrix& fromMatrix) : m_m{ fromMatrix.m_m }, m_n{ fromMatrix.m_n }
    {
        std::cout << "Конструктор глубокого копирования" << std::endl;

        array = new double* [m_m];
        std::cout << m_m << " " << m_n << std::endl;
        for (int i = 0; i < m_m; ++i)
        {
            array[i] = new double[m_n];
            for (int j = 0; j < m_n; ++j)
            {
                array[i][j] = fromMatrix.array[i][j];
                printf("%3.0f ", array[i][j]);
            }
            std::cout << std::endl;
        }

    }
}
