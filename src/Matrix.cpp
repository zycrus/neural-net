#include "../include/Matrix.hpp"
#include <iostream>


Matrix::Matrix(int _row, int _col){
    rows = _row;
    cols = _col;
    
    for (int i = 0; i < rows; i++){
        vector<float> temp;
        elements.insert(elements.end(), temp);
        for (int j = 0; j < cols; j++){
            elements.at(i).insert(elements.at(i).end(), 0);
        }
    }
}

bool Matrix::UnitMatrix(){
    try{
        if (rows != cols) throw Exception("Matrix is not a square matrix.");
        for (int i = 0; i < rows; i++){
            for (int j = 0; j < cols; j++){
                if (i == j) elements.at(i).at(j) = 1;
                else elements.at(i).at(j) = 0;
            }
        }
        return true;
    }
    catch (Exception& e){
        cout << "Error Generating Unit Matrix: " << e.what() << endl;
        return false;
    }
}

bool Matrix::SetElement(int _row, int _col, float _val){
    try{
        if (_row >= rows || _col >= cols) throw Exception("Specified Row and Column exceeds the Matrix size.");
        elements.at(_row).at(_col) = _val;
        return true;
    }
    catch (Exception& e){
        cout << "Error Editing Element: " << e.what() << endl;
        return false;
    }
}

vector<float> Matrix::GetRow(int _row){
    return elements.at(_row);
}

vector<float> Matrix::GetColumn(int _col){
    vector<float> res;
    for (int i = 0; i < rows; i++){
        res.insert(res.end(), elements.at(i).at(_col));
    }
    return res;
}

void Matrix::PrintRow(int _row){
    cout << "R" << _row << "\t";
    for (int i = 0; i < cols; i++){
        cout << GetRow(_row).at(i) << "\t";
    }
}

void Matrix::PrintColumn(int _col){
    for (int i = 0; i < rows; i++){
        cout << GetColumn(_col).at(i) << "\t";
    }
}

void Matrix::PrintMatrix(){
    for (int i = 0; i < cols; i ++){
        cout << "\tC" << i;
    }
    cout << endl;
    for (int i = 0; i < rows; i++){
        PrintRow(i);
        cout << endl;
    }
}

Matrix Matrix::Transpose(){
    Matrix res = Matrix(cols, rows);
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            res.elements.at(j).at(i) = elements.at(i).at(j);
        }
    }
    return res;
}

float VectorDot(vector<float> _v1, vector<float> _v2){
    float res = 0;

    for (int i = 0; i < (int)_v1.size(); i++){
        res += _v1[i] * _v2[i];
    }

    return res;
}

Matrix MatrixProduct(Matrix _m1, Matrix _m2){
    Matrix res = Matrix(_m1.rows, _m2.cols);

    for (int i = 0; i < _m1.rows; i++){
        for (int j = 0; j < _m2.cols; j++){
            res.elements.at(i).at(j) = VectorDot(_m1.GetRow(i), _m2.GetColumn(j));
        }
    }
    return res;
}

Matrix MatrixAdd(Matrix _m1, Matrix _m2){
    try{
        if (_m1.rows != _m2.rows || _m1.cols != _m2.cols)
            throw Exception("Matrix size does not match.");

        Matrix res = Matrix(_m1.rows, _m1.cols);
        for (int i = 0; i < _m1.rows; i++){
            for (int j = 0; j < _m1.cols; j++){
                res.elements.at(i).at(j) =  _m1.elements.at(i).at(j) +  _m2.elements.at(i).at(j);
            }
        }
        return res;
    }
    catch (Exception& e){
        cout << "Cannot Add Matrices: " << e.what() << endl;
    }
    return Matrix(0, 0);
}

Matrix MatrixSubtract(Matrix _m1, Matrix _m2){
    try{
        if (_m1.rows != _m2.rows || _m1.cols != _m2.cols)
            throw Exception("Matrix size does not match.");

        Matrix res = Matrix(_m1.rows, _m1.cols);
        for (int i = 0; i < _m1.rows; i++){
            for (int j = 0; j < _m1.cols; j++){
                res.elements.at(i).at(j) =  _m1.elements.at(i).at(j) -  _m2.elements.at(i).at(j);
            }
        }
        return res;
    }
    catch (Exception& e){
        cout << "Cannot Subtract Matrices: " << e.what() << endl;
    }
    return Matrix(0, 0);
}

Matrix ScalarMultiply(float _s, Matrix _m){
    Matrix res = Matrix(_m.rows, _m.cols);
    for (int i = 0; i < _m.rows; i++){
        for (int j = 0; j < _m.cols; j++){
            res.elements.at(i).at(j) =  _m.elements.at(i).at(j) * _s;
        }
    }
    return res;
}