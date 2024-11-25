#include "Matrix.h"
#include <iostream>

//Matrix 01 branch

Matrix::Matrix(int _row, int _col){
    rows = _row;
    cols = _col;
    
    for (int i = 0; i < rows; i++){
        vector<int> temp;
        elements.insert(elements.end(), temp);
        for (int j = 0; j < cols; j++){
            elements.at(i).insert(elements.at(i).end(), 0);
        }
    }
}

void Matrix::UnitMatrix(){
    if (rows != cols) return;
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            if (i == j) elements.at(i).at(j) = 1;
            else elements.at(i).at(j) = 0;
        }
    }
}

void Matrix::SetElement(int _row, int _col, int _val){
    elements.at(_row).at(_col) = _val;
}

vector<int> Matrix::GetRow(int _row){
    return elements.at(_row);
}

vector<int> Matrix::GetColumn(int _col){
    vector<int> res;
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

int VectorDot(vector<int> _v1, vector<int> _v2){
    int res = 0;

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

int main() {
    // Write C++ code here
    

    cout << "M1:" << endl;

    Matrix m1 = Matrix(3, 5);

    m1.SetElement(1, 0, 10);
    m1.SetElement(1, 2, 20);
    m1.SetElement(0, 1, 50);
    m1.SetElement(0, 3, 12);
    m1.SetElement(0, 4, 20);
    m1.PrintMatrix();

    cout << "\nM2:" << endl;

    Matrix m2 = Matrix(5,2);
    m2.SetElement(0, 0, 1);
    m2.SetElement(1, 0, 1);
    m2.SetElement(0, 1, 4);
    m2.SetElement(2, 0, 5);
    m2.SetElement(4, 0, 23);
    m2.PrintMatrix();

    
    cout << "\nMatrix Product:" << endl;
    Matrix dot_matrix = MatrixProduct(m1, m2);
    dot_matrix.PrintMatrix();

    return 0;
}