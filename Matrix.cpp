#include "Matrix.h"
#include <iostream>
#include <iomanip>
#include <ctime>

namespace luMath
{
    int Matrix::s_idGenerator = 1;

    Matrix::Matrix() : Matrix(5, 5) { std::cout << "Произошло делегирование конструктора по умолчанию конструктору с параметрами." << std::endl; }
    Matrix::Matrix(int rows) : Matrix(rows, rows) {  std::cout << "Произошло делегирование конструктора квадратной матрицы конструктору с параметрами." << std::endl; }
    Matrix::Row::Row(int cols)
    {
        r_col = new double[cols];
        for (int i = 0; i < cols; i++)
            r_col[i] = rand() % 100 + rand() % 100 * 0.01;
    }
    Matrix::Matrix(int rows, int cols) : m_id{ s_idGenerator++ }
    {
        rows < 1 ? m_rows = 1 : m_rows = rows; 
        cols < 1 ? m_cols = 1 : m_cols = cols;
        std::cout << "Конструктор с параметрами. Создание объекта #" << m_id << ": m = " << m_rows << ", n = " << m_cols << std::endl;
        m_subrows = new Row[m_rows];
        for (int i = 0; i < m_rows; ++i)
            m_subrows[i] = Row(m_cols);
    }
    Matrix::Matrix(const Matrix& fromMatrix) : m_rows{ fromMatrix.m_rows }, m_cols{ fromMatrix.m_cols }, m_id{ s_idGenerator++ }
    {
        std::cout << "Создан объект #" << m_id << std::endl;
        std::cout << "Конструктор глубокого копирования. Копируется объект #" << fromMatrix.m_id << " в объект #" << m_id << std::endl;

        m_subrows = new Row[m_rows];
        for (int i = 0; i < m_rows; ++i)
        {
            m_subrows[i] = Row(m_cols);
            for (int j = 0; j < m_cols; ++j)
                (*this)[i][j] = fromMatrix[i][j];
        }
    }

    Matrix::~Matrix()
    {
        std::cout << "Деструктор объекта #" << m_id << std::endl;
        for (int i = 0; i < m_rows; ++i)
            if (m_subrows[i].r_col != nullptr)
                delete[](m_subrows[i].r_col);
        if (m_subrows != nullptr)
            delete[] m_subrows;
        
        m_subrows = nullptr;
        m_rows = 0; m_cols = 0; m_id = 0;
        std::cout << std::endl;
    }

    bool canMltpl(const Matrix& A, const Matrix& B) { return A.m_cols == B.m_rows; }
    bool canAdd(const Matrix& A, const Matrix& B) { return A.m_rows == B.m_rows && A.m_cols == B.m_cols; }

    double Matrix::maxItem() const
    {
        double max = (*this)[0][0];
        for (int i = 0; i < m_rows; ++i)
            for (int j = 0; j < m_cols; ++j)
                if (max < (*this)[i][j])
                    max = (*this)[i][j];
        return max;
    }
    double Matrix::minItem() const
    {
        double min = (*this)[0][0];
        for (int i = 0; i < m_rows; ++i)
            for (int j = 0; j < m_cols; ++j)
                if (min > (*this)[i][j])
                    min = (*this)[i][j];
        return min;
    }

    Matrix operator+(const Matrix& A, const Matrix& B)
    {
        if (canAdd(A, B))
        {
            Matrix C(A.m_rows, A.m_cols); //Создание нового объекта
            for (int i = 0; i < C.m_rows; ++i)
                for (int j = 0; j < C.m_cols; ++j)
                    C[i][j] = A[i][j] + B[i][j];
            return C;
        }
        else std::cout << "Объект #" << A.m_id << ": m = " << A.m_rows << " n = " << A.m_cols << std::endl
                       << "Объект #" << B.m_id << ": m = " << B.m_rows << " n = " << B.m_cols << std::endl
                       << "\tС данными матрицами операция сложения не может быть произведена. (возвращается первый операнд)" << std::endl;
        return A;
    }
    Matrix operator-(const Matrix& A, const Matrix& B)
    {
        if (canAdd(A, B))
        {
            Matrix C(A.m_rows, A.m_cols); //Создание нового объекта
            for (int i = 0; i < C.m_rows; ++i)
                for (int j = 0; j < C.m_cols; ++j)
                    C[i][j] = A[i][j] - B[i][j];
            return C;
        }
        else std::cout << "Объект #" << A.m_id << ": m = " << A.m_rows << " n = " << A.m_cols << std::endl
                       << "Объект #" << B.m_id << ": m = " << B.m_rows << " n = " << B.m_cols << std::endl
                       << "\tС данными матрицами операция вычитания не может быть произведена. (возвращается первый операнд)" << std::endl;
        return A;
    }
    Matrix operator*(const Matrix& A, const Matrix& B)
    {
        if (canMltpl(A, B))
        {
            double temp = 0;
            Matrix C(A.m_rows, B.m_cols); //Создание нового объекта
            for (int i = 0; i < C.m_rows; ++i)
                for (int j = 0; j < C.m_cols; ++j)
                {
                    temp = 0;
                    for (int k = 0; k < B.m_rows; ++k)
                        temp += A[i][k] * B[k][j];
                    C[i][j] = temp;
                }
            return C;
        }
        else std::cout << "Объект #" << A.m_id << ": m = " << A.m_rows << " n = " << A.m_cols << std::endl
                       << "Объект #" << B.m_id << ": m = " << B.m_rows << " n = " << B.m_cols << std::endl
                       << "\tС данными матрицами операция умножения не может быть произведена. (возвращается первый операнд)" << std::endl;
        return A;//?
    }
    Matrix operator*(const Matrix& A, double k)
    {
        Matrix C(A.m_rows, A.m_cols); //Создание нового объекта
        for (int i = 0; i < C.m_rows; ++i)
            for (int j = 0; j < C.m_cols; ++j)
                C[i][j] = A[i][j] * k;
        return C;
    }

    std::ostream& operator<<(std::ostream& out, const Matrix& matrix)
    {
        std::cout << std::endl;
        for (int i = 0; i < matrix.m_rows; ++i)
        {
            for (int j = 0; j < matrix.m_cols; ++j)
                out << std::fixed << std::setprecision(2) << std::setw(7) << matrix[i][j];
            std::cout << std::endl;
        }
        return out;
    }
    std::istream& operator>>(std::istream& in, Matrix& matrix)
    {
        for (int i = 0; i < matrix.m_rows; ++i)
            for (int j = 0; j < matrix.m_cols; ++j)
                in >> matrix[i][j];
        
        return in;
    }

    const Matrix& Matrix::operator=(const Matrix& matrix)
    {
        if (this == &matrix)
            return *this;
        if((*this).m_rows == matrix.m_rows &&  (*this).m_cols == matrix.m_cols)
            for (int i = 0; i < matrix.m_rows; ++i)
                for (int j = 0; j < matrix.m_cols; ++j)
                    (*this)[i][j] = matrix[i][j];
        return *this;
    }
    const Matrix& Matrix::operator+=(const Matrix& matrix)
    {
        (*this) = (*this) + matrix;
        return *this;
    }
    const Matrix& Matrix::operator-=(const Matrix& matrix)
    {
        (*this) = (*this) - matrix;
        return *this;
    }
    const Matrix& Matrix::operator*=(const Matrix& matrix)
    {
        if (canMltpl(*this, matrix) && (*this).m_cols == matrix.m_cols)
        {
            Matrix C((*this).m_rows, matrix.m_cols); //Создание нового объекта
            (*this) = (*this) * matrix;
        }
        else std::cout << "Объект #" << m_id        << ": m = " << m_rows        << " n = " << m_cols        << std::endl
                       << "Объект #" << matrix.m_id << ": m = " << matrix.m_rows << " n = " << matrix.m_cols << std::endl
                       << "\tС данными матрицами операция умножения не может быть произведена." << std::endl;
        return *this;
    }
    const Matrix& Matrix::operator*=(double k)
    {
        (*this) = (*this) *  k;
        return *this;
    }


     double& Matrix::Row::operator[](int col) {/* if (col < m_cols)*/ return r_col[col]; }
    Matrix::Row& Matrix::operator[](int row) { if(row < m_rows) return m_subrows[row];  }

    const double& Matrix::Row::operator[](int col) const { return r_col[col]; }
    const Matrix::Row& Matrix::operator[](int row) const { return m_subrows[row]; }

}
