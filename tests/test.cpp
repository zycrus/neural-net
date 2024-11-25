#include "..\include\Matrix.hpp"
#include "..\include\Except.hpp"

#include <iostream>

using namespace std;

int main(){
    
    Matrix mat = Matrix(3, 3);
    
    if(mat.UnitMatrix()) mat.PrintMatrix();
    if(mat.SetElement(0, 1, 1)) mat.PrintMatrix();

    return 0;
}