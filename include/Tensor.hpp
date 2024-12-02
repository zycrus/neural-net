#pragma once

#ifndef TENSOR_HPP
#define TENSOR_HPP

#include<vector>
#include<string>

using namespace std;

class Tensor{
public:
    int size;
    vector<double> data;

    Tensor(int _size = 1, vector<double> _data = vector<double>());
    string toString();
};

Tensor operator+(Tensor const& _t1, Tensor const& _t2);
Tensor operator-(Tensor const& _t1, Tensor const& _t2);
Tensor operator*(Tensor const& _t1, Tensor const& _t2);
Tensor operator/(Tensor const& _t1, Tensor const& _t2);

#endif