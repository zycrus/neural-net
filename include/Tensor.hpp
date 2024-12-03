#pragma once
#ifndef TENSOR_HPP
#define TENSOR_HPP

#include <iostream>
#include <vector>
#include <random>
#include <iomanip>

struct Tensor
{
	template<typename T, size_t x, size_t y>
	std::vector<std::vector<T>> generate_random();

	// template<typename T, size_t x, size_t y, size_t z>
	// std::vector<std::vector<std::vector<T>>> generate_random();

	// template<typename T, size_t batch_size, size_t height, size_t width, size_t color>
	// std::vector<std::vector<std::vector<std::vector<T>>>> generate_random();

	// template<typename T>
	// void print(std::vector<std::vector<T>> matrix);

	// template<typename T>
	// void print(std::vector<std::vector<std::vector<T>>> tensor);

	// template<typename T>
	// void print(std::vector<std::vector<std::vector<std::vector<T>>>> tensor);
};



#endif