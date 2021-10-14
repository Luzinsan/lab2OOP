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
        double* m_items;

        class Row
        {
        private:
            double* p_row;
            int m_cols;
        public:
            Row(double* row, int m_cols);
            ~Row();
            double& operator[](int col);
            const double& operator[](int col) const;
        };

    public:
        Matrix(); // Конструктор по умолчанию - создание матрицы 5x5
        Matrix(int rows); // Конструктор квадратной матрицы
        Matrix(int rows, int cols); // Конструктор прямоугольной матрицы
        Matrix(const Matrix& fromMatrix); // Копирующий конструктор
        Matrix(Matrix&& fromMatrix) noexcept; // Копирующий конструктор
        ~Matrix();
        Row operator[](int row); // Конструктор создания временной строки (без выделения памяти)
        const Row operator[](int row) const;

        // Проверка возможности перемножение матриц и сложение/вычитание матриц
        friend bool canMltpl(const Matrix& A, const Matrix& B);
        friend bool canAdd(const Matrix& A, const Matrix& B);

        // Нахождение минимального/максимального значения матрицы
        double maxItem() const;
        double minItem() const;

        // Перегрузка бинарных операторов для матриц (сложение, вычитание, умножение матриц, умножение матрицы на скаляр)
        friend Matrix operator+(const Matrix& A, const Matrix& B);
        friend Matrix operator-(const Matrix& A, const Matrix& B);
        friend Matrix operator*(const Matrix& A, const Matrix& B);
        friend Matrix operator*(const Matrix& A, double k);

        // Перегрузка оператора вывода/ввода матрицы
        friend std::ostream& operator<<(std::ostream& out, const Matrix& matrix);
       
        friend std::istream& operator>>(std::istream& in, Matrix& matrix);

        // Перегрузка оператора присваивания(копирования) 
        const Matrix& operator=(const Matrix& matrix) ;
        // Перегрузка оператора присваивания(перемещающего) 
        Matrix& operator=(Matrix&& matrix) noexcept;

        // Перегрузка оператора суммы/разности/умножения_матриц/умножения_на_скаляр с присваиванием(копированием) 
        const Matrix& operator+=(const Matrix& matrix);
        const Matrix& operator-=(const Matrix& matrix);
        const Matrix& operator*=(const Matrix& matrix);
        const Matrix& operator*=(double k);
    };
}
