#include "..\include\Matrix.hpp"
#include "..\include\Except.hpp"

#include <iostream>

using namespace std;

int main(){
    
    Matrix mat = Matrix(3, 3);
    
    if(mat.UnitMatrix()) mat.PrintMatrix();

    return 0;
}