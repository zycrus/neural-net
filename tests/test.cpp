#include "..\include\Matrix.hpp"
#include "..\include\Except.hpp"

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int main(){
    Matrix mat = Matrix(5, 5);
    mat.Random();
    mat.Print();

    return 0;
}