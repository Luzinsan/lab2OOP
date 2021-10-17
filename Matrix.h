#pragma once
#include <iostream>          //для std::ostream и std::istream
#include <initializer_list> // для std::initializer_list

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
        Matrix(); // Конструктор по умолчанию - создание матрицы 5x5 с рандомными значениями
        Matrix(int rows); // Конструктор квадратной матрицы с рандомными значениями
        Matrix(int rows, int cols); // Конструктор прямоугольной матрицы с рандомными значениями
        

        Matrix(int size,           const double* array); // Конструктор создания квадратной    матрицы с заданными значениями 
        Matrix(int rows, int cols, const double* array); // Конструктор создания прямоугольной матрицы с заданными значениями 
        Matrix(int size,           const std::initializer_list<double>& list); // квадратной    матрицы с помощью списка инициализации
        Matrix(int rows, int cols, const std::initializer_list<double>& list); // прямоугольной матрицы с помощью списка инициализации
       
        Matrix(int size,           double(*func)(int, int)); // Конструктор создания квадратной матрицы с помощью функции 
        Matrix(int rows, int cols, double(*func)(int, int)); // Конструктор создания прямоугольной матрицы с помощью функции 
        
        Matrix(const std::initializer_list<double>& list); // Конструктор со списком инициализации квадратной матрицы с автоматически заданным размером


        Matrix(const Matrix& fromMatrix) ;// Копирующий конструктор
        Matrix(Matrix&& fromMatrix) noexcept;             // Конструктор перемещения
        ~Matrix();
        Row operator[](int row); // Конструктор создания временной строки
        const Row operator[](int row) const;

        // Проверка возможности перемножение матриц и сложение/вычитания матриц
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
        const Matrix& operator=(Matrix&& matrix) noexcept;
        // Перегрузка оператора присваивания списком инициализации
        const Matrix& operator=(const std::initializer_list<double>& list);

        // Перегрузка оператора суммы/разности/умножения_матриц/умножения_на_скаляр с присваиванием(копированием) 
        const Matrix& operator+=(const Matrix& matrix);
        const Matrix& operator-=(const Matrix& matrix);
        const Matrix& operator*=(const Matrix& matrix);
        const Matrix& operator*=(double k);
    };
}
