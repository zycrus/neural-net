#include "../include/Tensor.hpp"
#include <random>

Tensor::Tensor(int _size, vector<double> _data): size(_size), data(_data){
    
}

Tensor::operator string () const{
    string res;
    res.append("[");
    for (int i = 0; i < size; i++)
    {
        res.append(to_string(data[i]));
        if (i != size)
            res.append(", ");
    }
    res.append("]");
    return res;
}

Tensor operator+(Tensor const& _t1, Tensor const& _t2){
    Tensor sum;
    for (int i = 0; i < max(_t1.size, _t2.size); i++){
        sum.data.insert(sum.data.end(), _t1.data[i] + _t2.data[i]);
    }
    return sum;
}