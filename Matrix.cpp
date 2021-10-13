#include "Matrix.h"
#include <iostream>
#include <iomanip>
#include <ctime>

namespace luMath
{
    //static std::_Smanip<std::streamsize> _cdecl size = static_cast<std::_Smanip<std::streamsize>>(7);
   /* std::ostream& operator<<(std::ostream& out, std::_Smanip<std::streamsize> _cdecl size)
    {
        out << std::fixed << std::setprecision(2) << size;
        return out;
    }*/




    /* необходимо реализовать также перемещающие конструкции (конструктор перемещения и оператор перемещения=).*/

    /* Все ошибки должны генерировать исключение (throw). 
    Текст исключения должен кратко описывать причину ошибки 
    и содержать ID объекта\объектов вызвавших генерацию исключения.*/

    /* std::cout << setw(15) << M1; 
        Нужно реализовать перегрузку оператора вывода на поток так, 
        чтобы в случае, если ширина вывода не была задана (и равна значению по умолчанию 0), 
        матрица выводилась со стандартным значением ширины (пусть 7 ), 
        а в случае, если ширина задана (и отлична от 0), матрица выводилась бы с заданной пользовательской шириной.
    */


    int Matrix::s_idGenerator = 1;

    Matrix::Matrix() : Matrix(5, 5) 
    { 
        std::cout << "Произошло делегирование конструктора по умолчанию конструктору с параметрами." 
            << std::endl; 
    }
    Matrix::Matrix(int rows) : Matrix(rows, rows) 
    {  
        std::cout << "Произошло делегирование конструктора квадратной матрицы конструктору с параметрами." 
            << std::endl; 
    }
    Matrix::Matrix(int rows, int cols) : m_rows{ rows }, m_cols{ cols }, m_id{ s_idGenerator++ }
    {
        try
        {
            if(m_rows <= 0 || m_cols <= 0)
                throw "Размерность строк или столбцов не может быть меньше либо равным нулю. Обработка исключения: матрица 5x5";
        }
        catch (const char* exception)
        {
            std::cout << exception;
            m_rows = 5; m_cols = 5;
        }

        std::cout << "Конструктор с параметрами. Создание объекта #" << m_id
            << ": m = " << m_rows
            << ", n = " << m_cols
            << std::endl;

        m_items = new double[m_rows * m_cols];
        for (int i = 0; i < m_cols * m_rows; i++)
            m_items[i] = rand() % 10;// + rand() % 100 * 0.01;
    }

    Matrix::Matrix(const Matrix& fromMatrix) : 
        m_rows{ fromMatrix.m_rows }, m_cols{ fromMatrix.m_cols }, m_id{ s_idGenerator++ }
    {
        std::cout << "Создан объект #" << m_id << std::endl
            << "Конструктор глубокого копирования. Копируется объект #" << fromMatrix.m_id 
            << " в объект #" << m_id << std::endl;

        m_items = new double[m_rows * m_cols];
        try
        {
            if (!m_items)
                throw "\n\t\tФатальное выделение памяти!\n";

            for (int i = 0; i < m_rows; i++)
                for (int j = 0; j < m_cols; j++)
                    m_items[i * m_cols + j] = fromMatrix.m_items[i * m_cols + j];
        }
        catch (const char* exception)
        {
            std::cout << exception << "Объект №" << m_id << " НЕ был создан\n";
        }
    }
    Matrix::Row::Row(double* row, int cols) : p_row{ row }, m_cols{ cols } { }
    
    Matrix::Row::~Row() 
    {  
        /*
        * Не вызываем delete для p_row, так как нам ещё нужна ячейка, 
        * куда указывал p_row(через m_items мы ещё держим контроль 
        * над этой областью памяти - утечки не происходит)
        */
    }
    Matrix::~Matrix()
    {
        std::cout << "Деструктор объекта #" << m_id << std::endl;
        delete[] m_items;
    }

    bool canMltpl(const Matrix& A, const Matrix& B) 
    { return A.m_cols == B.m_rows; }
    bool canAdd(const Matrix& A, const Matrix& B) 
    { 
        return A.m_rows == B.m_rows 
          && A.m_cols == B.m_cols; 
    }

    double Matrix::maxItem() const
    {
        double max = m_items[0];
        for (int i = 0; i < m_rows; i++)
            for (int j = 0; j < m_cols; j++)
                if (max < m_items[i * m_cols + j])
                    max = m_items[i * m_cols + j];
        return max;
    }
    double Matrix::minItem() const
    {
        double min = m_items[0];
        for (int i = 0; i < m_rows; i++)
            for (int j = 0; j < m_cols; j++)
                if (min > m_items[i * m_cols + j])
                    min = m_items[i * m_cols + j];
        return min;
    }

    Matrix operator+(const Matrix& A, const Matrix& B)
    {
        try
        {
            if (!canAdd(A, B))
                throw "\nС данными матрицами операция сложения не может быть произведена.\t(возвращается левый операнд)\n";
            
            Matrix C(A.m_rows, A.m_cols); //Создание нового объекта
            for (int i = 0; i < C.m_rows; i++)
                for (int j = 0; j < C.m_cols; j++)
                    C.m_items[i * C.m_cols + j] = A.m_items[i * A.m_cols + j]
                                                + B.m_items[i * B.m_cols + j];
            return C;
        }
        catch (const char* exception)
        {
            std::cout << "Объект #" << A.m_id << ": m = " << A.m_rows << " n = " << A.m_cols << std::endl
                      << "Объект #" << B.m_id << ": m = " << B.m_rows << " n = " << B.m_cols << std::endl
                      << exception;
            return A;
        }
    }
    Matrix operator-(const Matrix& A, const Matrix& B)
    {
        try
        {
            if (!canAdd(A, B))
                throw "\n\tС данными матрицами операция вычитания не может быть произведена. (возвращается левый операнд)\n";

            Matrix C(A.m_rows, A.m_cols); //Создание нового объекта
            for (int i = 0; i < C.m_rows; i++)
                for (int j = 0; j < C.m_cols; j++)
                    C.m_items[i * C.m_cols + j] = A.m_items[i * A.m_cols + j]
                                                - B.m_items[i * B.m_cols + j];
            return C;
        }
        catch (const char* exception)
        {
            std::cout << "Объект #" << A.m_id << ": m = " << A.m_rows << " n = " << A.m_cols << std::endl
                      << "Объект #" << B.m_id << ": m = " << B.m_rows << " n = " << B.m_cols << std::endl
                      << exception << std::endl;
            return A;
        }
    }
    Matrix operator*(const Matrix& A, const Matrix& B)
    {
        try
        {
            if (!canMltpl(A, B))
                throw "\n\tС данными матрицами операция произведения не может быть произведена. (возвращается левый операнд)\n";

            double temp = 0;
            Matrix C(A.m_rows, B.m_cols);
            for (int i = 0; i < C.m_rows; i++)
                for (int j = 0; j < C.m_cols; j++)
                {
                    temp = 0;
                    for (int k = 0; k < B.m_rows; k++)
                        temp += A.m_items[i * A.m_cols + k]
                              * B.m_items[k * B.m_cols + j];
                    C.m_items[i * C.m_cols + j] = temp;
                }
            return C;
        }
        catch (const char* exception)
        {
            std::cout << "Объект #" << A.m_id << ": m = " << A.m_rows << " n = " << A.m_cols << std::endl
                      << "Объект #" << B.m_id << ": m = " << B.m_rows << " n = " << B.m_cols << std::endl
                      << exception << std::endl;
            return A;
        }
    }
    Matrix operator*(const Matrix& A, double k)
    {
        Matrix C(A.m_rows, A.m_cols); //Создание нового объекта
        for (int i = 0; i < C.m_rows; i++)
            for (int j = 0; j < C.m_cols; j++)
                C.m_items[i * C.m_cols + j] = A.m_items[i * A.m_cols + j] 
                                            * k;
        return C;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    std::ostream& operator<<(std::ostream& out, const Matrix& matrix)/////////////////////////////////////////////////////
    {
        out << "\n";
        for (int i = 0; i < matrix.m_rows; i++)
        {
            for (int j = 0; j < matrix.m_cols; j++)
                out << std::fixed << std::setprecision(2) << std::setw(7) << matrix.m_items[i * matrix.m_cols + j];
            out << "\n";
        }
        return out;
    }
    
    std::istream& operator>>(std::istream& in, Matrix& matrix)
    {
        for (int i = 0; i < matrix.m_rows; i++)
            for (int j = 0; j < matrix.m_cols; j++)
                in >> matrix.m_items[i * matrix.m_cols + j];
        return in;
    }

    const Matrix& Matrix::operator=(const Matrix& matrix)
    {
        if (this == &matrix)
            return *this;
        if(m_rows == matrix.m_rows &&  m_cols == matrix.m_cols)
            for (int i = 0; i < matrix.m_rows; i++)
                for (int j = 0; j < matrix.m_cols; j++)
                    m_items[i * m_cols + j] = matrix.m_items[i * matrix.m_cols + j];
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
        try
        {
            if (!(canMltpl(*this, matrix) && m_cols == matrix.m_cols))
                throw "\tС данными матрицами операция умножения не может быть произведена, \n"
                      "\tлибо размерность полученной матрицы не совпадает с размерностью левого операнда.";

            Matrix C(m_rows, matrix.m_cols);
            (*this) = (*this) * matrix;
        }
        catch (const char* exception)
        {
            std::cout << "Объект #" <<        m_id << ": m = " <<        m_rows << " n = " <<        m_cols << std::endl
                      << "Объект #" << matrix.m_id << ": m = " << matrix.m_rows << " n = " << matrix.m_cols << std::endl
                      << exception << std::endl;
        }
        return *this;
    }
    const Matrix& Matrix::operator*=(double k)
    {
        (*this) = (*this) *  k;
        return *this;
    }

    double& Matrix::Row::operator[](int col) 
    {
        try 
        {
            if (col >= m_cols)
                throw "\nНомер столбца выходит за пределы матрицы.";
        }
        catch(const char* exception)
        {
            col = m_cols - 1;
            std::cout << exception << "\tИсключение обработано: номер возвращаемого элемента столбца в заданной строке ->" << col << "\n";
        }
        return p_row[col]; // возвращаем ссылку на col-элемент строки p_row
    }
    Matrix::Row Matrix::operator[](int row) 
    { 
        try
        {
            if (row >= m_rows)
                throw "\nНомер строки выходит за пределы матрицы.";
        }
        catch (const char* exception)
        {
            row = m_rows - 1;
            std::cout << exception << "\tИсключение обработано: номер возвращаемой строки ->" << row << "\n";
        }
        
        /*Возвращаем анонимный объект с инициализацией его полей 
        1) указателем на нужную строку (строку row)
        2) и кол-вом столбцов для проверки правильности обращения к элементу строки в последствии 
        ***После создания анонимного объекта применяется перегрузка оператора[] в подклассе Row */
        return  Row(m_items + (row * m_cols), m_cols); 
    }

    const double& Matrix::Row::operator[](int col) const 
    { 
        try
        {
            if (col >= m_cols)
                throw "\nНомер столбца выходит за пределы матрицы.";
        }
        catch (const char* exception)
        {
            col = m_cols - 1;
            std::cout << exception<< "\tИсключение обработано: номер возвращаемой константной строки ->" << col << "\n";
        }
        return p_row[col]; // возвращаем ссылку на col-элемент строки p_row
    }
    const Matrix::Row Matrix::operator[](int row) const 
    { 
        try
        {
            if (row >= m_rows)
                throw "\nНомер строки выходит за пределы матрицы.";
        }
        catch (const char* exception)
        {
            row = m_rows - 1;
            std::cout << exception << "\tИсключение обработано: номер возвращаемой строки ->" << row << "\n";
        }
        return  Row(m_items + (row * m_cols), m_cols);
    }
}
