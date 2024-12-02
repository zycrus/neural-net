#include "../include/Tensor.hpp"
#include <random>
#include <iostream>
#include <assert.h>

using namespace std;

Tensor::Tensor(int _size, vector<double> _data): size(_size), data(_data){
    
}

string Tensor::toString(){
    string res;
    res.append("Tensor (Size = " + to_string(size) + ") ");
    res.append("(Data = [ ");
    for (int i = 0; i < size; i++)
    {
        res.append(to_string(data[i]));
        if (i < size - 1)
            res.append(", ");
    }
    res.append(" ])");
    return res;
}

Tensor operator+(Tensor const& _t1, Tensor const& _t2){
    assert(_t1.size == _t2.size);
    Tensor res;
    res.size = _t1.size;
    for (int i = 0; i < res.size; i++){
        res.data.insert(res.data.end(), _t1.data[i] + _t2.data[i]);
    }
    return res;
}

Tensor operator-(Tensor const& _t1, Tensor const& _t2){
    assert(_t1.size == _t2.size);
    Tensor res;
    res.size = _t1.size;
    for (int i = 0; i < res.size; i++){
        res.data.insert(res.data.end(), _t1.data[i] - _t2.data[i]);
    }
    return res;
}

Tensor operator*(Tensor const& _t1, Tensor const& _t2){
    assert(_t1.size == _t2.size);
    Tensor res;
    res.size = _t1.size;
    for (int i = 0; i < res.size; i++){
        res.data.insert(res.data.end(), _t1.data[i] * _t2.data[i]);
    }
    return res;
}

Tensor operator/(Tensor const& _t1, Tensor const& _t2){
    assert(_t1.size == _t2.size);
    Tensor res;
    res.size = _t1.size;
    for (int i = 0; i < res.size; i++){
        res.data.insert(res.data.end(), _t1.data[i] / _t2.data[i]);
    }
    return res;
}