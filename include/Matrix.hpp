#ifndef MATRIX_HPP
#define MATRIX_HPP

#pragma once
#include <vector>
#include "../include/Except.hpp"

using namespace std;


class Matrix{
public:
    vector<vector<float>> elements;
    int rows, cols;
    
    Matrix(int _row, int _col);
    bool UnitMatrix();
    bool SetElement(int _row, int _col, float _val);
    vector<float> GetRow(int _row);
    vector<float> GetColumn(int _col);
    void PrintRow(int _row);
    void PrintColumn(int _col);
    void PrintMatrix();
    Matrix Transpose();

    bool LoadFromFile(char* _file);
    bool SaveToFile(char* _file);
};

//Operations
float DotVector(vector<float> _v1, vector<float> _v2);
Matrix MatrixProduct(Matrix _m1, Matrix _m2);
Matrix MatrixAdd(Matrix _m1, Matrix _m2);
Matrix MatrixSubtract(Matrix _m1, Matrix _m2);
Matrix ScalarMultiply(float _s, Matrix _m);


#endif