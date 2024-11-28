#include "..\include\Matrix.hpp"
#include "..\include\Except.hpp"

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int main(){
    // Matrix mat = Matrix(0, 0);
    // mat.LoadFromFile("test.csv");
    // mat.PrintMatrix();

    int L = 4;
    int dk = 8;
    int dv = 8;
    Matrix q = Matrix(0, 0);
    Matrix k = Matrix(0, 0);
    Matrix v = Matrix(0, 0);

    q.RandomMatrix(L, dk);
    k.RandomMatrix(L, dk);
    v.RandomMatrix(L, dv);

    cout << "\nQ:" << endl;
    q.PrintMatrix();
    cout << "\nK:" << endl;
    k.PrintMatrix();
    cout << "\nV:" << endl;
    v.PrintMatrix();

    // cout << "\nMask(M):" << endl;
    // Matrix mask = Matrix(L, L);
    // mask.TriangularMatrix();
    // mask.Replace(0, -numeric_limits<float>::infinity());
    // mask.Replace(1, 0);
    // mask.PrintMatrix();

    // cout << "\nQk.T/sqrt(dk):" << endl;
    // Matrix scaled = MultiplyByScalar(1/sqrt(dk), MultiplyMatrix(q, k.Transpose()));
    // scaled.PrintMatrix();

    // cout << "\nQk.T/sqrt(dk) + M:" << endl;
    // Matrix masked = AddMatrix(scaled, mask);
    // masked.PrintMatrix();

    // cout << "\nsoftmax:" << endl;
    // Matrix softmax = Softmax(scaled);

    cout << "\nAttention:" << endl;
    Matrix attention = Attention(L, dk, dv, q, k ,v);
    attention.PrintMatrix();

    cout << "\nNew V:" << endl;
    MultiplyMatrix(attention, v).PrintMatrix();
}