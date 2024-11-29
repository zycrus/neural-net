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
    operator string () const;
};

Tensor operator+(Tensor const& _t1, Tensor const& _t2);

#endif