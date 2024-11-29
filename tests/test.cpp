#include "..\include\Matrix.hpp"
#include "..\include\Tensor.hpp"
#include "..\include\Except.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

int main(){
    // Matrix mat = Matrix(5, 5);
    // mat.Random();
    // mat.Print();
    Tensor t = Tensor(3, {1, 2, 3});
    cout << t;
    return 0;
}