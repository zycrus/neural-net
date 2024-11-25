#ifndef MATRIX_HPP
#define MATRIX_HPP

#pragma once
#include <vector>
#include "../include/Except.hpp"

using namespace std;


class Matrix{
public:
    vector<vector<int>> elements;
    int rows, cols;
    
    Matrix(int _row, int _col);
    bool UnitMatrix();
    bool SetElement(int _row, int _col, int _val);
    vector<int> GetRow(int _row);
    vector<int> GetColumn(int _col);
    void PrintRow(int _row);
    void PrintColumn(int _col);
    void PrintMatrix();
    Matrix Transpose();
};

//Operations
int DotVector(vector<int> _v1, vector<int> _v2);
Matrix MatrixProduct(Matrix _m1, Matrix _m2);
Matrix MatrixAdd(Matrix _m1, Matrix _m2);
Matrix MatrixSubtract(Matrix _m1, Matrix _m2);
Matrix ScalarMultiply(int s, Matrix _m);

#endif