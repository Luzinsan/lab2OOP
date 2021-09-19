#pragma once
#include <iostream>//для std::ostream и std::istream

namespace luMath 
{
    class Matrix
    {
    private:
        static int s_idGenerator;
        int m_id;
        int m_rows, m_cols;

        class Row;// подкласс строк матрицы (объявление)
        Row* m_subrows; // указатель на массив подкласса строк матрицы
        class Row// подкласс строк матрицы (реализация)
        {
        public:
            double* r_col;
            Row() {}
            Row(int cols);
            double& operator[](int col);
            double& operator[](int col) const;
        };

    public:

        Matrix();
        Matrix(int rows);
        Matrix(int rows, int cols);
        Matrix(const Matrix& fromMatrix);
        ~Matrix();
        Row& operator[](int row);
        Row& operator[](int row) const;

        // Проверка возможности перемножение матриц ... и сложения/вычитания их элементов
        friend bool canMltpl(const Matrix& A, const Matrix& B);
        friend bool canAdd(const Matrix& A, const Matrix& B);

        // Нахождение минимального/максимального значения матрицы
        double maxItem();
        double minItem();

        // Перегрузка бинарных операторов для матриц (сложение, вычитание, умножение матрицб умножение матрицы на скаляр), если это возможно (проверка есть)
        friend Matrix operator+(const Matrix& A, const Matrix& B);
        friend Matrix operator-(const Matrix& A, const Matrix& B);
        friend Matrix operator*(const Matrix& A, const Matrix& B);
        friend Matrix operator*(const Matrix& A, double k);

        // Перегрузка оператора вывода/ввода матрицы
        friend std::ostream& operator<<(std::ostream& out, const Matrix& matrix);
        friend std::istream& operator>>(std::istream& in, Matrix& matrix);

        // Перегрузка оператора присваивания 
        const Matrix& operator=(const Matrix& matrix);
        // Перегрузка оператора суммы/разности/умножения_матриц/умножения_на_скаляр с присваиванием 
        const Matrix& operator+=(const Matrix& matrix);
        const Matrix& operator-=(const Matrix& matrix);
        const Matrix& operator*=(const Matrix& matrix);
        const Matrix& operator*=(double k);

       
    };

}
