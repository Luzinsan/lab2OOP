#pragma once
#include <iostream>

namespace luzalex
{
    class Matrix
    {
    private:
        int m_m, m_n;//m_m - кол-во строк; m_n - кол-во столбцов
        double** array;

    public:
        Matrix()
        {
            std::cout << "Конструктор по умолчанию" << std::endl;
            Matrix(3, 3);
        }
        Matrix(int m)
        {
            std::cout << "Конструктор - квадратная матрица" << std::endl;
            Matrix(m, m);
        }

        Matrix(int m, int n);
        Matrix(const Matrix& fromMatrix);
        ~Matrix()
        {
            std::cout << "Деструктор" << std::endl;
            for (int i = 0; i < m_m; ++i)
                delete[] array[i];
            delete[] array;
        }

        friend bool canMltpl(const Matrix& A, const Matrix& B)
        {
            return A.m_n == B.m_m;
        }

        friend bool canAdd(const Matrix& A, const Matrix& B)
        {
            return A.m_m == B.m_m && A.m_n == B.m_n;
        }

        double maxItem()
        {
            double max = array[0][0];
            for (int i = 0; i < m_m; ++i)
                for (int j = 0; j < m_n; ++j)
                    if (max < array[i][j])
                        max = array[i][j];
            return max;
        }
        double minItem()
        {
            double min = array[0][0];
            for (int i = 0; i < m_m; ++i)
                for (int j = 0; j < m_n; ++j)
                    if (min > array[i][j])
                        min = array[i][j];
            return min;
        }

        //дружественность функции позволяет напрямую обращаться к закрытому члену класса
        friend Matrix operator+(const Matrix& A, const Matrix& B);
        friend Matrix operator-(const Matrix& A, const Matrix& B);
        friend Matrix operator*(const Matrix& A, const Matrix& B);
        friend Matrix operator*(const Matrix& A, const int k);
        friend std::ostream& operator<<(std::ostream& out, const Matrix& matrix);


        // Перегрузка оператора присваивания как метода класса (передаётся неявный объект - левый операнд)
        Matrix& operator=(const Matrix& matrix);
        // Перегрузка оператора суммы с присваиванием как метода класса
        Matrix& operator+=(const Matrix& matrix);
        Matrix& operator-=(const Matrix& matrix);
        Matrix& operator*=(const Matrix& matrix);
        Matrix& operator*=(const int k);

        //Оператор доступа к члену
        //double* operator[](const Matrix& matrix);
        //double& operator[](const int index);

    };
}
