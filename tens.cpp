#include <iostream>
#include <chrono>
#include <random>
#include <iomanip>
#include <assert.h>

#include "tens.hpp"



void run() {
	Tensor x({1, 10});
	// Tensor y({3, 10});
	x.generate_random();
	// y.generate_random();
	// x.print();
	// y.print();
	// (x + y).print();
}

int main() {
	auto start = std::chrono::high_resolution_clock::now();

    // Call the function or block of code whose runtime you want to measure
    run();

    // Get the end point of the timer
    auto end = std::chrono::high_resolution_clock::now();

    // Calculate the duration (end - start) in milliseconds
    std::chrono::duration<double, std::milli> duration = end - start;

    // Print the runtime in milliseconds
    std::cout << "Execution time: " << duration.count() << " ms" << std::endl;

	return 0;
}



// TENSOR
// Helper function to calculate total size
size_t Tensor::get_size(const std::vector<size_t>& dims) const {
    size_t size = 1;
    for (auto dim : dims)
        size *= dim;
    return size;
}

// Helper function to compute flat index from multi-dimensional indices
size_t Tensor::get_flat_index(const std::vector<size_t>& indices) const {
    size_t index = 0;
    size_t stride = 1;
    for (int i = shape.size() - 1; i >= 0; i--) {
        index += indices[i] * stride;
        stride *= shape[i];
    }
    return index;
}

// Constructor with shape
Tensor::Tensor(const std::vector<size_t>& dims): shape(dims) {
	this->total_size = get_size(this->shape);
	this->data.resize(this->total_size);
}

// Constructor with data and shape
Tensor::Tensor(const std::vector<T>& data, const std::vector<size_t>& dims): data(data), shape(dims) {
	this->total_size = get_size(this->shape);
	this->data.resize(this->total_size);
}

// Getter for shape
const std::vector<size_t> Tensor::get_shape() const {
	return shape;
}

 // Fill tensor with a specific value
void Tensor::fill(const T& value) {
    std::fill(data.begin(), data.end(), value);
}

void Tensor::generate_random() {
    static thread_local std::mt19937 gen{std::random_device{}()};
    std::normal_distribution<T> d(0.0, 1.0);  // Specify mean and stddev

    // Genrate and insert random value from the normal distribution to the matrix
    for (int i = 0; i < data.size(); i++) {
            data[i] = d(gen);
    }
}



// Add operator
Tensor Tensor::operator+(const Tensor other) const{	
    // Check if shapes match
    assert (shape == other.get_shape());

    // Create a new tensor to hold the result
    Tensor result(shape);

    // Perform element-wise addition
    for (size_t i = 0; i < total_size; ++i) {
        result.data[i] = data[i] + other.data[i];
    }

    return result;
}

// Access operator (for both getting and setting values)
T& Tensor::operator()(const std::vector<size_t>& indices) {
    size_t flat_idx = get_flat_index(indices);
    return data[flat_idx];
}

// Const version of the access operator (for getting values)
const T& Tensor::operator()(const std::vector<size_t>& indices) const {
    size_t flat_idx = get_flat_index(indices);
    return data[flat_idx];
}

void Tensor::print(const std::vector<size_t>& indices, size_t depth) const {
    if (depth == shape.size() - 1) {
        std::cout << "[ ";
        for (size_t i = 0; i < shape[depth]; ++i) {
            auto current_indices = indices;
            current_indices.push_back(i);
            if ((*this)(current_indices) > 0) std::cout << " ";
            std::cout << std::fixed << std::setprecision(8) << (*this)(current_indices) << " ";  // Call to const version of operator()
        }
        std::cout << "]";
    } else {
        std::cout << "[ ";
        for (size_t i = 0; i < shape[depth]; ++i) {
            auto current_indices = indices;
            current_indices.push_back(i);
            print(current_indices, depth + 1);  // Recursively call print()
            if (i < shape[depth] - 1) {
                std::cout << "\n";  // Add newline between matrix rows
                for (size_t s = 0; s <= depth; s++) {
                	std::cout << "  ";
                }
            }
        }
        std::cout << " ]";
    }

    if (depth == 0) {
        std::cout << "\n";
    }
}