#include "Matrix.h"

namespace luzalex
{
    const Matrix operator+(const Matrix& A, const Matrix& B)
    {
        if (canAdd(A, B))
        {
            Matrix C = { A.m_m, A.m_n };
            std::cout << "Операция сложения:" << std::endl;
            C.array = new double* [C.m_m];
            for (int i = 0; i < C.m_m; ++i)
            {
                C.array[i] = new double[C.m_n];
                for (int j = 0; j < C.m_n; ++j)
                {
                    C.array[i][j] = A.array[i][j] + B.array[i][j];
                    printf("%3.0f ", C.array[i][j]);
                }
                std::cout << std::endl;
            }
            return C;
        }
        else std::cout << "С данными матрицами операция сложения не может быть произведена" << std::endl;
        return A;
    }
    const Matrix operator-(const Matrix& A, const Matrix& B)
    {
        if (canAdd(A, B))
        {
            Matrix C = { A.m_m, A.m_n };
            std::cout << "Операция вычитания:" << std::endl;
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
        else std::cout << "С данными матрицами операция разности не может быть произведена" << std::endl;
        return A;
    }
    const Matrix operator*(const Matrix& A, const Matrix& B)
    {
        
        if (canMltpl(A, B))
        {
            Matrix C = { A.m_m, B.m_n };
            std::cout << "Операция умножения:" << std::endl;
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
        else std::cout << "С данными матрицами операция умножения не может быть произведена" << std::endl;
        return A;
    }
    const Matrix operator*(const Matrix& A, const double k)
    {
        

        Matrix C = { A.m_m, A.m_n };
        std::cout << "Операция умножения матрицы на скаляр:" << std::endl;
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

    const Matrix& Matrix::operator=(const Matrix& matrix)//метод класса
    {
        // Проверка на самоприсваивание
        if (this == &matrix)
            return *this;
        for (int i = 0; i < matrix.m_m; ++i)
            for (int j = 0; j < matrix.m_n; ++j)
                array[i][j] = matrix.array[i][j];

        return *this;
    }
    const Matrix& Matrix::operator+=(const Matrix& matrix)//метод класса
    {
        std::cout << "Операция сложения с присваиванием:" << std::endl;
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
    const Matrix& Matrix::operator-=(const Matrix& matrix)//метод класса
    {
        std::cout << "Операция вычитания с присваиванием:" << std::endl;
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
    const Matrix& Matrix::operator*=(const Matrix& matrix)//метод класса
    {
        std::cout << "Операция умножения с присваиванием:" << std::endl;
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
        else std::cout << "С данными матрицами операция сложения с присваиванием не может быть произведена" << std::endl;
        return *this;
    }
    const Matrix& Matrix::operator*=(const double k)
    {
        std::cout << "Операция умножения на скаляр с присваиванием:" << std::endl;
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
