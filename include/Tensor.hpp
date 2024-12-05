#pragma once
#ifndef TENSOR_HPP
#define TENSOR_HPP

#include <iostream>
#include <vector>
#include <random>
#include <iomanip>

using namespace std;

template<typename T>
class Tensor
{
public:
	vector<T> data;
	vector<int> shape;

	Tensor(vector<int> shape): shape(shape);

	Tensor generate_random(vector<int> _shape);

	// std::vector<std::vector<std::vector<T>>> generate_random();

	// std::vector<std::vector<std::vector<std::vector<T>>>> generate_random();

	// template<typename T>
	// void print(std::vector<std::vector<T>> matrix);

	// template<typename T>
	// void print(std::vector<std::vector<std::vector<T>>> tensor);

	// template<typename T>
	// void print(std::vector<std::vector<std::vector<std::vector<T>>>> tensor);
};



#endif