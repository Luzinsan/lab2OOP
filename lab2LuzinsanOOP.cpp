#include <iostream>
#include <ctime>
#include "Matrix.h"

int main()
{
    srand(time(0));
    rand();

    Matrix matrix(rand()%10, rand() % 10);
    
}
