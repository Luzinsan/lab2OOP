#include "Matrix.h"
#include <ctime>
#include <iomanip>//для setw()

namespace luMath
{
    int Matrix::s_idGenerator = 1;

    // Основной конструктор
    Matrix::Matrix(int rows, int cols, const double* array) : m_rows{ rows }, m_cols{ cols }, m_id{ s_idGenerator++ }
    {
        try
        {
            if (m_rows <= 0 || m_cols <= 0)
                throw "Объект №", m_id, ". Размерность строк или столбцов не может быть меньше либо равным нулю. Обработка исключения: матрица 5x5";
        }
        catch (const char* exception)
        {
            std::cout << exception;
            m_rows = 5; m_cols = 5;
        }

        std::cout << "\n\tКонструктор создания матрицы с заданными значениями. Создание объекта #" << m_id
            << ": m = " << m_rows
            << ", n = " << m_cols
            << std::endl;
        m_items = new double[m_rows * m_cols];

        try
        {
            if (!m_items) throw "\n\t\tФатальное выделение памяти для объекта №", m_id, '\n';
            for (int iii = 0; iii < m_rows * m_cols; ++iii)
                m_items[iii] = array[iii];
        }
        catch (const char* exception)
        { std::cout << exception; }
    }

    Matrix::Matrix() : Matrix(5, 5)
    { std::cout << "\n\tПроизошло делегирование конструктора по умолчанию конструктору с параметрами." << std::endl; }
    Matrix::Matrix(int rows) : Matrix(rows, rows)
    { std::cout << "\n\tПроизошло делегирование конструктора квадратной матрицы конструктору с параметрами." << std::endl; }
    Matrix::Matrix(int rows, int cols) : Matrix(rows, cols, new double[rows * cols])
    {
        for (int iii = 0; iii < m_cols * m_rows; ++iii)
            m_items[iii] = rand() % 10;// + rand() % 100 * 0.01;
        std::cout << "\n\tПроизошло делегирование конструктора с параметрами"
                  << "\n\tконструктору создания прямоугольной матрицы с заданными значениями." << std::endl;
    }
    Matrix::Matrix(int size, const double* array) : Matrix(size, size, array)
    { std::cout << "\n\tПроизошло делегирование конструктора создания квадратой матрицы с заданными значеними"
                << "\n\tконструктору создания прямоугольной матрицы с заданными значениями." << std::endl; }
    Matrix::Matrix(int size, const std::initializer_list<double>& list) : Matrix(size, size, list)
    {
        std::cout << "\n\tПроизошло делегирование конструктора создания квадратой матрицы со списком инициализации"
                                    << "\n\t\tконструктору создания прямоугольной матрицы со списком инициализации." << std::endl;
    }
    Matrix::Matrix(const std::initializer_list<double>& list) 
        : Matrix((((static_cast<int>(sqrt(list.size()) * 10)) % 10 == 0) ? static_cast<int>(sqrt(list.size()))
                                                                         : static_cast<int>(sqrt(list.size()))+1),
                 (((static_cast<int>(sqrt(list.size()) * 10)) % 10 == 0) ? static_cast<int>(sqrt(list.size()))
                                                                         : static_cast<int>(sqrt(list.size())) + 1),
                 list)
    {
        std::cout << "\n\tКонструктор со списком инициализации делегировал создание "
                  << "\n\tконструктору создания прямоугольной матрицы со списком инициализации.";
    }
    Matrix::Matrix(int rows, int cols, const std::initializer_list<double>& list) : Matrix(rows, cols, new double[rows * cols])
    {
        std::cout << "\n\tПроизошло делегирование конструктора создания прямоугольной матрицы со списком инициализации"
                                        << "\n\t\tконструктору создания прямоугольной матрицы c заданными значениями." << std::endl;
        int count = 0;
        for (auto& element : list)
        {
            m_items[count] = element;
            count++;
        }
        for (; count < m_rows * m_cols; ++count)
            m_items[count] = 0;

        std::cout << "\n\tКонструктор создания прямоугольной матрицы со списком инициализации проинициализировал элементы матрицы №" 
                  << m_id << std::endl;
    }
    

    Matrix::Matrix(int size,            double(*func)(int rows, int cols))  : Matrix(size, size, func) 
    {
        std::cout << "\n\tПроизошло делегирование конструктора создания квадратой матрицы с функцией"
                  << "\n\t\tконструктору создания прямоугольной матрицы с функцией." << std::endl;
    }
    Matrix::Matrix(int rows,  int cols, double(*func)(int rows, int cols )) : Matrix(rows, cols, new double[rows * cols])
    {
        std::cout << "\n\tПроизошло делегирование конструктора создания прямоугольной матрицы с функцией"
                  << "\n\t\tконструктору создания прямоугольной матрицы c заданными значениями." << std::endl;
        for (int iii = 0; iii < m_rows; ++iii)
            for (int jjj = 0; jjj < m_cols; ++jjj)
                m_items[iii * m_cols + jjj] = func(iii, jjj);
        std::cout << "\n\tКонструктор создания прямоугольной матрицы с функцией проинициализировал элементы матрицы №"
                  << m_id << std::endl;
    }

    
    Matrix::Matrix(const Matrix& fromMatrix) : Matrix(fromMatrix.m_rows, fromMatrix.m_cols, fromMatrix.m_items)
    {
        std::cout << "\n\tКонструктор глубокого копирования делегировал создание "
                  << "\n\tконструктору создания прямоугольной матрицы с заданными значениями.";
    }
    Matrix::Matrix(Matrix&& fromMatrix) noexcept:
        m_rows{ fromMatrix.m_rows }, 
        m_cols{ fromMatrix.m_cols }, 
        m_id{ s_idGenerator++ }, 
        m_items{ fromMatrix.m_items }
    {
        fromMatrix.m_rows = 0;
        fromMatrix.m_cols = 0;
        fromMatrix.m_items = nullptr;
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
        std::cout << "\n\tДеструктор объекта #" << m_id << std::endl;
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
        for (int iii = 0; iii < m_rows * m_cols; ++iii)
            if (max < m_items[iii])
                max = m_items[iii];
        return max;
    }
    double Matrix::minItem() const
    {
        double min = m_items[0];
        for (int iii = 0; iii < m_rows * m_cols; ++iii)
            if (min < m_items[iii])
                min = m_items[iii];
        return min;
    }

    Matrix operator+(const Matrix& A, const Matrix& B)
    { return Matrix(A) += B; }
    Matrix operator-(const Matrix& A, const Matrix& B)
    { return Matrix(A) -= B; }
    Matrix operator*(const Matrix& A, const Matrix& B)
    { return Matrix(A) *= B; }
    Matrix operator*(const Matrix& A, double k)
    { return Matrix(A) *= k; }

    std::ostream& operator<<(std::ostream& out, const Matrix& matrix)
    {
        int size = static_cast<int>(std::cout.width());
        out << "\n";
        for (int i = 0; i < matrix.m_rows; i++)
        {
            for (int j = 0; j < matrix.m_cols; j++)
                if(size) out << std::fixed << std::setprecision(2) << std::setw(size) << matrix.m_items[i * matrix.m_cols + j];
                else     out << std::fixed << std::setprecision(2) << std::setw(10)    << matrix.m_items[i * matrix.m_cols + j];
            out << "\n";
        }
        return out;
    }
    std::istream& operator>>(std::istream& in, Matrix& matrix)
    {
        for (int iii = 0; iii < matrix.m_rows * matrix.m_cols; ++iii)
            in >> matrix.m_items[iii];
        return in;
    }

    const Matrix& Matrix::operator=(const Matrix& matrix)
    {
        if (this == &matrix)
            return *this;

        m_cols = matrix.m_cols;
        m_rows = matrix.m_rows;
        delete[] m_items;
        m_items = new double[m_cols * m_rows];
        for (int iii = 0; iii < m_rows * m_cols; ++iii)
            m_items[iii] = matrix.m_items[iii];
        return *this;
    }
    const Matrix& Matrix::operator=(Matrix&& matrix) noexcept
    {
        if (this == &matrix)
            return *this;

        m_cols = matrix.m_cols;
        m_rows = matrix.m_rows;
        m_id = matrix.m_id;
        delete[] m_items;
        m_items = matrix.m_items;
        matrix.m_cols = 0;
        matrix.m_rows = 0;
        matrix.m_items = nullptr;
        return *this;
    }
    const Matrix& Matrix::operator=(const std::initializer_list<double>& list)
    {
        if (list.size() != static_cast<size_t>(m_rows * m_cols))
        {
            delete[] m_items;
            m_rows = (static_cast<int>(sqrt(list.size()) * 10) % 10 == 0) ? static_cast<int>(sqrt(list.size()))
                                                                          : static_cast<int>(sqrt(list.size())) + 1;
            m_cols = m_rows;
            m_items = new double[m_rows * m_cols];
        }
        int count = 0;
        for (auto& element : list)
        {
            m_items[count] = element;
            count++;
        }
        for (; count < m_rows * m_cols; ++count)
            m_items[count] = 0;
        return *this;
    }
    const Matrix& Matrix::operator+=(const Matrix& matrix)
    {
        try
        {
            if (!canAdd(*this, matrix))
                throw "\nМатрица №",          m_id, ": m = ",        m_rows, "; n = ",        m_cols,
                      "\nи матрица №", matrix.m_id, ": m = ", matrix.m_rows, "; n = ", matrix.m_cols,
                      ".\nС данными матрицами операция сложения не может быть произведена.\t(возвращается левый операнд)\n";

            for (int iii = 0; iii < m_rows*m_cols; ++iii)
                m_items[iii] += matrix.m_items[iii];
        }
        catch (const char* exception)
        { std::cout << exception; }
        return *this;
    }
    const Matrix& Matrix::operator-=(const Matrix& matrix)
    {
        try
        {
            if (!canAdd(*this, matrix))
                throw "\nМатрица №",          m_id, ": m = ",        m_rows, "; n = ",        m_cols,
                      "\nи матрица №", matrix.m_id, ": m = ", matrix.m_rows, "; n = ", matrix.m_cols,
                      ".\nС данными матрицами разности сложения не может быть произведена.\t(возвращается левый операнд)\n";

            for (int iii = 0; iii < m_rows * m_cols; ++iii)
                m_items[iii] += matrix.m_items[iii];
        }
        catch (const char* exception)
        { std::cout << exception; }
        return *this;
    }
    const Matrix& Matrix::operator*=(const Matrix& matrix)
    {
        try
        {
            if (!(canMltpl(*this, matrix) && m_cols == matrix.m_cols))
                throw "\nМатрица №",          m_id, ": m = ",        m_rows, "; n = ",        m_cols,
                      "\nи матрица №", matrix.m_id, ": m = ", matrix.m_rows, "; n = ", matrix.m_cols,
                      ".\nС данными матрицами операция умножения не может быть произведена, \n";
                      "либо размерность полученной матрицы не совпадает с размерностью левого операнда.\n\t(возвращается левый операнд)";

            double temp = 0;
            Matrix T(m_rows, matrix.m_cols);
            for (int iii = 0; iii < m_rows; ++iii)
                for (int jjj = 0; jjj < matrix.m_cols; ++jjj)
                {
                    temp = 0;
                    for (int kkk = 0; kkk < matrix.m_rows; ++kkk)
                        temp += m_items[iii * m_cols + kkk]
                              * matrix.m_items[kkk * matrix.m_cols + jjj];
                    T.m_items[iii * T.m_cols + jjj] = temp;
                }
            *this = T;
        }
        catch (const char* exception)
        { std::cout << exception << std::endl; }
        return *this;
    }
    const Matrix& Matrix::operator*=(double k)
    {
        for (int iii = 0; iii < m_rows; ++iii)
            m_items[iii] *= k;
        return *this;
    }

    double& Matrix::Row::operator[](int col) 
    {
        try 
        {
            if (col >= m_cols)
                throw "\n\tНомер столбца выходит за пределы матрицы\n";
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
                throw "\n\tНомер строки выходит за пределы матрицы #", m_id,'\n';
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
                throw "\n\tНомер столбца выходит за пределы матрицы.\n";
        }
        catch (const char* exception)
        {
            col = m_cols - 1;
            std::cout << exception << "\tИсключение обработано: номер возвращаемой константной строки ->" << col << "\n";
        }
        return p_row[col]; // возвращаем ссылку на col-элемент строки p_row
    }
    const Matrix::Row Matrix::operator[](int row) const 
    { 
        try
        {
            if (row >= m_rows)
                throw "\n\tНомер строки выходит за пределы матрицы #", m_id, '\n';
        }
        catch (const char* exception)
        {
            row = m_rows - 1;
            std::cout << exception << "\tИсключение обработано: номер возвращаемой строки ->" << row << "\n";
        }
        return  Row(m_items + (row * m_cols), m_cols);
    }
}
