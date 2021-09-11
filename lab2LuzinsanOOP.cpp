#include <ctime>
#include "Matrix.h"

using namespace luzalex;

int main()
{
    setlocale(LC_ALL, "Russian");
    srand(static_cast<unsigned int>(time(0)));
    rand();

    std::cout << "asterix: \n" << std::endl;
    Matrix asterix;
    std::cout << "masterix: \n" << std::endl;
    Matrix masterix(rand()%10);
    std::cout << "matrix: \n" << std::endl;
    Matrix matrix(rand()%10, rand() % 10);
    std::cout << "maMatrix: \n" << std::endl;
    Matrix maMatrix(matrix);
    std::cout << "abelix: \n" << std::endl;
    Matrix abelix(matrix + maMatrix);

    return 0;
}
