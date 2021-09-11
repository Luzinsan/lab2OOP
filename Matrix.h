#pragma once
#include <iostream>

namespace luzalex
{
    class Matrix
    {
    private:
        int m_m, m_n;//m_m - кол-во строк; m_n - кол-во столбцов
        double** array;
        static int s_idGenerator;
        int m_id;

    public:
        Matrix(): m_id{ s_idGenerator++ }
        {
            std::cout << "Конструктор по умолчанию #" << m_id << std::endl;
            Matrix(3, 3);
        }
        Matrix(int m): m_id{ s_idGenerator++ }
        {
            std::cout << "Конструктор #" << m_id << " - квадратная матрица" << std::endl;
            Matrix(m, m);
        }
        Matrix(int m, int n);
        Matrix(const Matrix& fromMatrix);
        ~Matrix()
        {
            std::cout << "Деструктор матрицы #" << m_id << std::endl;
            for (int i = 0; i < m_m; ++i)
                delete[] array[i];
            delete[] array;
        }

        friend const bool canMltpl(const Matrix& A, const Matrix& B)
        { return A.m_n == B.m_m; }

        friend const bool canAdd(const Matrix& A, const Matrix& B)
        { return A.m_m == B.m_m && A.m_n == B.m_n; }

        const double maxItem();
        const double minItem();
        

        //дружественность функции позволяет напрямую обращаться к закрытому члену класса
        //перегрузка бинарных операторов для матриц (сложение, вычитание, умножение матриц), если это возможно (проверка есть)
        friend const Matrix operator+(const Matrix& A, const Matrix& B);
        friend const Matrix operator-(const Matrix& A, const Matrix& B);
        friend const Matrix operator*(const Matrix& A, const Matrix& B);
        /* Перегрузка оператора* для умножения матрицы на скаляр
           с сохранением первоначальной матрицы и копированием умноженной матрицы с возвратом в caller*/
        friend const Matrix operator*(const Matrix& A, const double k);
        // Перегрузка оператора вывода матрицы
        friend std::ostream& operator<<(std::ostream& out, const Matrix& matrix);


        // Перегрузка оператора присваивания как метода класса (передаётся неявный объект - левый операнд)
        const Matrix& operator=(const Matrix& matrix);
        // Перегрузка оператора суммы/разности/умножения_матриц/умножения_на_скаляр с присваиванием как метода класса
        const Matrix& operator+=(const Matrix& matrix);
        const Matrix& operator-=(const Matrix& matrix);
        const Matrix& operator*=(const Matrix& matrix);
        const Matrix& operator*=(const double k);

        //Оператор доступа к члену
        //double* operator[](const Matrix& matrix);
        //double& operator[](const int index);

    };
}
