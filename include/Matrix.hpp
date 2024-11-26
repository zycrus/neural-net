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

    bool LoadFromFile(string _file);
    bool SaveToFile(string _file);
};

//Operations
float DotVector(vector<float> _v1, vector<float> _v2);
Matrix MultiplyMatrix(Matrix _m1, Matrix _m2);
Matrix AddMatrix(Matrix _m1, Matrix _m2);
Matrix SubtractMatrix(Matrix _m1, Matrix _m2);
Matrix MultiplyByScalar(float _s, Matrix _m);


#endif