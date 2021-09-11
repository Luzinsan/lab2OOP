#include "Matrix.h"

namespace luzalex
{
    int Matrix::s_idGenerator = 1;

    Matrix::Matrix(int m, int n) : m_m{ (m % 10) }, m_n{ (n % 10) }, m_id{ s_idGenerator++}
    {
        std::cout << "Конструктор с параметрами m = " << m << " и n = " << n << "  под номером #" << m_id << std::endl;
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
        std::cout << std::endl;
    }

    Matrix::Matrix(const Matrix& fromMatrix) : m_m{ fromMatrix.m_m }, m_n{ fromMatrix.m_n },  m_id{ s_idGenerator++ }
    {
        std::cout << "Конструктор глубокого копирования #"<< m_id << std::endl;

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
        std::cout << std::endl;
    }

    const double Matrix::maxItem()
    {
        double max = array[0][0];
        for (int i = 0; i < m_m; ++i)
            for (int j = 0; j < m_n; ++j)
                if (max < array[i][j])
                    max = array[i][j];
        return max;
    }

    const double Matrix::minItem()
    {
        double min = array[0][0];
        for (int i = 0; i < m_m; ++i)
            for (int j = 0; j < m_n; ++j)
                if (min > array[i][j])
                    min = array[i][j];
        return min;
    }
}
