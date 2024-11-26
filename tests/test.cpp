#include "..\include\Matrix.hpp"
#include "..\include\Except.hpp"

#include <iostream>

using namespace std;

int main(){
    cout << "==========================" << endl;

    Matrix mat1 = Matrix(3, 3);
    Matrix mat2 = Matrix(3, 3);

    if(mat1.UnitMatrix()) mat1.PrintMatrix();
    cout << endl;
    if(mat2.UnitMatrix()) mat2.PrintMatrix();
    cout << endl;

    cout << "SCALAR" << endl;

    ScalarMultiply(0.3, mat1).PrintMatrix();

    return 0;
}