#include "Matrix.h"
#include <iomanip>
using namespace luMath;



int main()
{
    system("color 1E");
    setlocale(LC_ALL, "Rus");
    srand(static_cast<unsigned int>(time(0)));
    rand();
    

    Matrix matrix0;
    matrix0 = { 0,1,2,3,4,5,6,7,8 };
    std::cout << "matrix0: \n" << matrix0 << std::endl;
    Matrix matrix9({ 11,12,13,14,15,16,17,18,19,20 });
    std::cout << "matrix9: \n" << matrix9 << std::endl;

    
    Matrix asterix;
    std::cout << "asterix: \n" << std::setw(25) << asterix << std::endl;

    Matrix masterix(8);
    std::cout << "masterix: \n" << masterix << std::endl;

    Matrix matrix(4, 8);
    std::cout << "matrix: \n" << matrix << std::endl;

    Matrix maMatrix(matrix);
    std::cout << "maMatrix: \n" << maMatrix << std::endl;

    Matrix abelix(matrix + maMatrix);
    std::cout << "abelix: \n" << matrix << '+' << maMatrix << '=' << abelix << std::endl;

    Matrix matrix1(matrix - maMatrix);
    std::cout << "matrix1: \n" << matrix << '-' << maMatrix << '=' << matrix1 << std::endl;

    Matrix matrix2(matrix * masterix);
    std::cout << "matrix2: \n" << matrix << '*' << masterix << "=" << matrix2 << std::endl;

    std::cout << "The max item of matrix2: \n" << matrix2 << "\t\tis " << matrix2.maxItem() << std::endl;
    std::cout << "The min item of matrix2: \n" << matrix2 << "\t\tis " << matrix2.minItem() << std::endl;
    int k = 3;
    Matrix matrix3(matrix * k);
    std::cout << "matrix3: \n" << matrix << '*' << k << "\n=" << matrix3 << std::endl;

    Matrix matrix4(4, 8);
    matrix4 = matrix;

    std::cout << "matrix4: \n" << matrix4 << "+=" << abelix << '=' << std::endl;
    matrix4 += abelix;
    std::cout << matrix4 << std::endl;

    std::cout << "matrix4: \n" << matrix4 << "-=" << abelix << '=' << std::endl;
    matrix4 -= abelix;
    std::cout << matrix4 << std::endl;

    std::cout << "matrix4: \n" << matrix4 << "*=" << masterix << '=' << std::endl;
    matrix4 *= masterix;
    std::cout << matrix4 << std::endl;

    std::cout << "matrix4: \n" << matrix4 << "*=" << k << "\n=" << std::endl;
    matrix4 *= k;
    std::cout << matrix4 << std::endl;

    std::cout << "matrix4[3][7]: \n" << matrix4[3][7] << std::endl;

    Matrix matrix5(3);
    std::cin >> matrix5;
    std::cout << "matrix5: \n" << matrix5 << std::endl;
    Matrix matrix6(3);
    std::cin >> matrix6;
    std::cout << "matrix6: \n" << matrix6 << std::endl;
    std::cout << "matrix5: \n" << matrix5 << "*=" << matrix6 << '=' << std::endl;
    matrix5 *= matrix6;
    std::cout << "matrix5: \n" << matrix5 << std::endl;
    matrix5[2][3] = 6;
    const Matrix mamAtrix(matrix5);
    std::cout << std::setw(15) << mamAtrix << "\n" << matrix5[2][2] << '\n';


    return 0;
}
