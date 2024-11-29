#pragma once

#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "../include/Except.hpp"
#include <stdarg.h>
#include <initializer_list>
#include <vector>

using namespace std;


class Matrix{
public:
    vector<vector<double>> elements;
    int x, y;
    
    Matrix(int _x, int _y);

    void Triangle();
    void Random();

    void Replace(double _toReplace, double _val);
    Matrix Transpose();

    void Print(int _precision = 10);
};


/*
    MATRIX OPERATIONS
*/
Matrix AddMatrix(Matrix _m1, Matrix _v2);
Matrix DotVector(vector<double> _v1, vector<double> _v2);
Matrix MultiplyMatrix(Matrix _m1, Matrix _v2);
Matrix MultiplyToScalar(Matrix _m, double _scalar);


#endif