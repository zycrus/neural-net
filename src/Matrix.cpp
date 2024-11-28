#include "../include/Matrix.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <random>


Matrix::Matrix(int _row, int _col){
    // cout << "Initializing Matrix" << endl;
    rows = _row;
    cols = _col;
    
    for (int i = 0; i < rows; i++){
        vector<float> temp;
        elements.insert(elements.end(), temp);
        for (int j = 0; j < cols; j++){
            elements.back().insert(elements.back().end(), 0);
        }
    }
}

bool Matrix::RandomMatrix(int _row, int _col){
    try{
        // Define the mean and standard deviation
        double mean = 0.0;
        double stddev = 1.0;

        // Create a random device and seed the generator
        std::random_device rd;
        std::mt19937 gen(rd());

        // Create a normal distribution with the specified mean and standard deviation
        std::normal_distribution<> d(mean, stddev);

        rows = _row;
        cols = _col;
        elements.clear();

        for (int i = 0; i < rows; i++){
            vector<float> temp;
            elements.insert(elements.end(), temp);
            for (int j = 0; j < cols; j++){
                elements.back().insert(elements.back().end(), d(gen));
            }
        }
        return true;
    }
    catch(exception& e){
        cerr << "Error Generating Random Matrix: " << e.what() << endl;
        return false;
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
        cerr << "Error Generating Unit Matrix: " << e.what() << endl;
        return false;
    }
}

bool Matrix::TriangularMatrix(){
    try{
        if (rows != cols) throw Exception("Matrix is not a square matrix.");
        for (int i = 0; i < rows; i++){
            for (int j = 0; j < cols; j++){
                if (i >= j) elements.at(i).at(j) = 1;
                else elements.at(i).at(j) = 0;
            }
        }
        return true;
    }
    catch (Exception& e){
        cerr << "Error Generating Triangular Matrix: " << e.what() << endl;
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
        cerr << "Error Editing Element: " << e.what() << endl;
        return false;
    }
}

bool Matrix::Replace(float _find, float _val){
    try{
        for (int i = 0; i < rows; i++){
            for (int j = 0; j < cols; j++){
                if (elements.at(i).at(j) == _find) elements.at(i).at(j) = _val;
            }
        }
        return true;
    }
    catch(exception& e){
        cerr << "Error Replacing Element: " << e.what() << endl;
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

bool Matrix::LoadFromFile(string _file){
    rows = 0;
    try{
        ifstream file;
        string line;
        file.open("csv/" + _file);
        vector<float> temp;

        while (file >> line){
            cols = 0;
            string val;

            stringstream lineString(line);

            elements.insert(elements.end(), temp);

            while (getline(lineString, val, ',')){
                elements.back().insert(elements.back().end(), stof(val));
                cols++;
            }
            rows++;
        }
        cout << "File Loaded." << endl;
        file.close();
        return true;
    }
    catch (Exception& e){
        cerr << "Cannot read file: " << e.what() << endl;
        return false;
    }
}





float DotVector(vector<float> _v1, vector<float> _v2){
    float res = 0;

    for (int i = 0; i < (int)_v1.size(); i++){
        res += _v1[i] * _v2[i];
    }

    return res;
}

Matrix MultiplyMatrix(Matrix _m1, Matrix _m2){
    Matrix res = Matrix(_m1.rows, _m2.cols);

    for (int i = 0; i < _m1.rows; i++){
        for (int j = 0; j < _m2.cols; j++){
            res.elements.at(i).at(j) = DotVector(_m1.GetRow(i), _m2.GetColumn(j));
        }
    }
    return res;
}

Matrix AddMatrix(Matrix _m1, Matrix _m2){
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
        cerr << "Cannot Add Matrices: " << e.what() << endl;
    }
    return Matrix(0, 0);
}

Matrix SubtractMatrix(Matrix _m1, Matrix _m2){
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
        cerr << "Cannot Subtract Matrices: " << e.what() << endl;
    }
    return Matrix(0, 0);
}

Matrix MultiplyByScalar(float _s, Matrix _m){
    Matrix res = Matrix(_m.rows, _m.cols);
    for (int i = 0; i < _m.rows; i++){
        for (int j = 0; j < _m.cols; j++){
            res.elements.at(i).at(j) =  _m.elements.at(i).at(j) * _s;
        }
    }
    return res;
}