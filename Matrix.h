#pragma once

class Matrix
{
private:
    int m_m, m_n;
    double** array;

public:
    Matrix()      { Matrix(3, 3); }
    Matrix(int m) { Matrix(m, m); }
    Matrix(int m, int n);
    
    ~Matrix()
    {
        for (int i = 0; i < m_m; ++i)
            delete array[i];
        delete array;
    }

};
