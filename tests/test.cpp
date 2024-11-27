#include "..\include\Matrix.hpp"
#include "..\include\Except.hpp"

#include <iostream>
#include <string>

using namespace std;

int main(){
    Matrix mat = Matrix(0, 0);
    mat.LoadFromFile("test.csv");
    mat.PrintMatrix();
}