#include "../include/Matrix.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <random>
#include <iomanip>


Matrix::Matrix(int _x, int _y):x(_x), y(_y){
    for (int i = 0; i < x; i ++){
        vector<double> temp2;
        elements.insert(elements.end(), temp2);
        for (int j = 0; j < y; j++){
            elements.at(i).insert(elements.at(i).end(), 0);
        }
    }
}

void Matrix::Triangle(){
    if (x != y) return;
    for (int i = 0; i < x; i ++){
        for(int j = 0; j < y; j++){
            if (i < j) elements.at(i).at(j) = 0;
            else elements.at(i).at(j) = 1;
        }
    }
}

void Matrix::Replace(double _toReplace, double _val){
    for (int i = 0; i < x; i ++){
        for(int j = 0; j < y; j++){
            if (elements.at(i).at(j) == _toReplace) elements.at(i).at(j) = _val;
        }
    }
}

Matrix Matrix::Transpose(){
    Matrix res = Matrix(y, x);
    for (int i = 0; i < x; i++){
        for (int j = 0; j < y; j++){
            res.elements.at(j).at(i) = elements.at(i).at(j);
        }
    }
    return res;
}

void Matrix::Random(){
    // Define the mean and standard deviation
    double mean = 0.0;
    double stddev = 1.0;

    // Create a random device and seed the generator
    std::random_device rd;
    std::mt19937 gen(rd());

    // Create a normal distribution with the specified mean and standard deviation
    std::normal_distribution<> d(mean, stddev);

    elements.clear();

    for (int i = 0; i < x; i++){
        vector<double> temp;
        elements.insert(elements.end(), temp);
        for (int j = 0; j < y; j++){
            elements.back().insert(elements.back().end(), d(gen));
        }
    }
}

void Matrix::Print(int _precision){
    for (int i = 0; i < x; i ++){
        for(int j = 0; j < y; j++){
            cout  << std::fixed << std::setprecision(_precision) << elements.at(i).at(j) << "\t";
        }
        cout << endl;
    }
}


/*
    MATRIX OPERATIONS
*/
Matrix AddMatrix(Matrix _m1, Matrix _m2){
    try{
        if (_m1.x != _m2.x || _m1.y != _m2.y)
            throw Exception("Matrix size does not match.");

        Matrix res = Matrix(_m1.x, _m1.y);
        for (int i = 0; i < _m1.x; i++){
            for (int j = 0; j < _m1.y; j++){
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