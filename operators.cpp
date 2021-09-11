#include "Matrix.h"

namespace luzalex
{
    Matrix operator+(const Matrix& A, const Matrix& B)
    {
        std::cout << "ќпераци€ сложени€:" << std::endl;
        if (canAdd(A, B))
        {
            Matrix C = { A.m_m, A.m_n };
            C.array = new double* [C.m_m];
            for (int i = 0; i < C.m_m; ++i)
            {
                C.array[i] = new double[C.m_n];
                for (int j = 0; j < C.m_n; ++j)
                {
                    C.array[i][j] = A.array[i][j] + B.array[i][j];
                    printf("%3.0f ", C.array[i][j]);
                    //std::cout << "%3.0f" << C.array[i][j];
                }
                std::cout << std::endl;
            }
            return C;
        }
        else std::cout << "— данными матрицами операци€ сложени€ не может быть произведена" << std::endl;
        return A;
    }
    Matrix operator-(const Matrix& A, const Matrix& B)
    {
        std::cout << "ќпераци€ вычитани€:" << std::endl;
        if (canAdd(A, B))
        {
            Matrix C = { A.m_m, A.m_n };
            C.array = new double* [C.m_m];
            for (int i = 0; i < C.m_m; ++i)
            {
                C.array[i] = new double[C.m_n];
                for (int j = 0; j < C.m_n; ++j)
                {
                    C.array[i][j] = A.array[i][j] - B.array[i][j];
                    //printf("%3.0f ", C.array[i][j]);
                    std::cout << "%3.0f" << C.array[i][j];
                }
                std::cout << std::endl;
            }
            return C;
        }
        else std::cout << "— данными матрицами операци€ разности не может быть произведена" << std::endl;
        return A;
    }
    Matrix operator*(const Matrix& A, const Matrix& B)
    {
        std::cout << "ќпераци€ умножени€:" << std::endl;
        if (canMltpl(A, B))
        {
            Matrix C = { A.m_m, B.m_n };
            C.array = new double* [C.m_m];
            for (int i = 0; i < C.m_m; ++i)
            {
                C.array[i] = new double[C.m_n];
                for (int j = 0; j < C.m_n; ++j)
                {
                    C.array[i][j] = A.array[i][j] * B.array[j][i];
                    //printf("%3.0f ", C.array[i][j]);
                    std::cout << "%3.0f" << C.array[i][j];
                }
                std::cout << std::endl;
            }
            return C;
        }
        else std::cout << "— данными матрицами операци€ умножени€ не может быть произведена" << std::endl;
        return A;
    }
    Matrix operator*(const Matrix& A, const int k)
    {
        std::cout << "ќпераци€ умножени€ матрицы на скал€р:" << std::endl;

        Matrix C = { A.m_m, A.m_n };
        C.array = new double* [C.m_m];
        for (int i = 0; i < C.m_m; ++i)
        {
            C.array[i] = new double[C.m_n];
            for (int j = 0; j < C.m_n; ++j)
            {
                C.array[i][j] = A.array[i][j] * k;
                std::cout << "%3.0f" << C.array[i][j];
            }
            std::cout << std::endl;
        }
        return C;
    }

    std::ostream& operator<<(std::ostream& out, const Matrix& matrix)
    {
        for (int i = 0; i < matrix.m_m; ++i)
        {
            for (int j = 0; i < matrix.m_n; ++j)
                out << matrix.array[i][j] << " ";
            std::cout << std::endl;
        }

        return out;

    }


    Matrix& Matrix::operator=(const Matrix& matrix)//метод класса
    {
        // ѕроверка на самоприсваивание
        if (this == &matrix)
            return *this;
        for (int i = 0; i < matrix.m_m; ++i)
            for (int j = 0; j < matrix.m_n; ++j)
                array[i][j] = matrix.array[i][j];

        return *this;
    }

    Matrix& Matrix::operator+=(const Matrix& matrix)//метод класса
    {
        std::cout << "ќпераци€ сложени€ с присваиванием:" << std::endl;
        for (int i = 0; i < m_m; ++i)
        {
            for (int j = 0; j < m_n; ++j)
            {
                array[i][j] += matrix.array[i][j];
                printf("%3.0f ", array[i][j]);
            }
            std::cout << std::endl;
        }
        return *this;
    }
    Matrix& Matrix::operator-=(const Matrix& matrix)//метод класса
    {
        std::cout << "ќпераци€ вычитани€ с присваиванием:" << std::endl;
        for (int i = 0; i < m_m; ++i)
        {
            for (int j = 0; j < m_n; ++j)
            {
                array[i][j] += matrix.array[i][j];
                printf("%3.0f ", array[i][j]);
            }
            std::cout << std::endl;
        }
        return *this;
    }
    Matrix& Matrix::operator*=(const Matrix& matrix)//метод класса
    {
        std::cout << "ќпераци€ умножени€ с присваиванием:" << std::endl;
        if (canMltpl(*this, matrix))
        {
            for (int i = 0; i < m_m; ++i)
            {
                for (int j = 0; j < m_n; ++j)
                {
                    array[i][j] += matrix.array[i][j];
                    printf("%3.0f ", array[i][j]);
                }
                std::cout << std::endl;
            }
        }
        else std::cout << "— данными матрицами операци€ сложени€ с присваиванием не может быть произведена" << std::endl;
        return *this;
    }

    Matrix& Matrix::operator*=(const int k)
    {
        std::cout << "ќпераци€ умножени€ на скал€р с присваиванием:" << std::endl;
        for (int i = 0; i < m_m; ++i)
        {
            for (int j = 0; j < m_n; ++j)
            {
                array[i][j] += k;
                printf("%3.0f ", array[i][j]);
            }
            std::cout << std::endl;
        }

        return *this;
    }


    /*
    double* Matrix::operator[](const Matrix& matrix)
    {



    }

    double& Matrix::operator[](const int index)
    {
        return


    }*/

}