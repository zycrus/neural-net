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

    cout << "SUBTRACT" << endl;

    MatrixSubtract(MatrixSubtract(mat1, mat2), mat1).PrintMatrix();

    cout << "==========================" << endl;
    cout << "==========================" << endl;

    Matrix mat3 = Matrix(3, 3);
    Matrix mat4 = Matrix(3, 2);
    
    mat3.UnitMatrix();
    mat3.PrintMatrix();
    cout << endl;

    mat4.UnitMatrix();
    mat4.PrintMatrix();
    cout << endl;

    cout << "SUBTRACT" << endl;

    MatrixSubtract(mat3, mat4).PrintMatrix();

    return 0;
}