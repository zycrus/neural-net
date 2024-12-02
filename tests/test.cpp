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
    Tensor t1 = Tensor(3, {1, 2, 3});
    Tensor t2 = Tensor(3, {3, 4, 5});
    cout << t1.toString() << endl;
    cout << t2.toString() << endl;
    cout << (t1 / t2).toString() << endl;
    return 0;
}