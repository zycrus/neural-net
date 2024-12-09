#include <iostream>
#include <chrono>
#include <random>
#include <iomanip>
#include <assert.h>

#include "tens.hpp"



void run() {
	Tensor x({2, 5});
	Tensor y({4, 10});
	x.generate_random();
	y.generate_random();
	x.print();
	y.print();
	// x.matmul(x, y).print();


    // Tensor new_tensor = x * y;

    // std::cout << x.get_shape().size() << " " << y.get_shape().size() << std::endl;
    // for (size_t x : new_tensor.get_shape()) {
    //     std::cout << x << " ";
    // }
    // std::cout << std::endl;

    // new_tensor.fill(0);

    // new_tensor.print();
    
    // for (size_t i = 0; i < x.get_size(x.get_shape() ); i++) {
    //     std::vector<size_t> new_idx = x.get_indices(i);
    //     for (size_t x : new_idx) {
    //         std::cout << x << " ";
    //     }   
    //     std::cout << std::endl;
    // }

    (x * y).print();
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

// Convert flat index to tensor indices
std::vector<size_t> Tensor::get_indices(const size_t flat_index) const {
    std::vector<size_t> result(shape.size());
    size_t temp = flat_index;

    for (int i = shape.size() - 1; i >= 0; i--) {
        result[i] = temp % shape[i];
        temp = flat_index / shape[i];
    }
    return result;
}


// Getter for row
const std::vector<T> Tensor::get_row(size_t row) const {
    assert (this->shape.size() == 2);
    std::vector<T> result(this->shape[1]);
    for (size_t i = 0; i < this->shape[1]; i++) {
        result[i] = (*this)({row, i});
    }
    return result;
}

// Getter for column
const std::vector<T> Tensor::get_column(size_t col) const {
    assert (this->shape.size() == 2);
    std::vector<T> result(this->shape[0]);
    for (size_t i = 0; i < this->shape[0]; i++) {
        result[i] = (*this)({i, col});
    }
    return result;
}

 // Fill tensor with a specific value
void Tensor::fill(const T& value) {
    std::fill(this->data.begin(), this->data.end(), value);
}

void Tensor::generate_random() {
    static thread_local std::mt19937 gen{std::random_device{}()};
    std::normal_distribution<T> d(0.0, 1.0);  // Specify mean and stddev

    // Genrate and insert random value from the normal distribution to the matrix
    for (int i = 0; i < data.size(); i++) {
            this->data[i] = d(gen);
    }
}


// OPERATORS

// Add Tensors(element-wise)
Tensor Tensor::operator+(const Tensor other) const{	
    // Check if shapes match
    assert (this->shape == other.get_shape());

    // Create a new tensor to hold the result
    Tensor result(this->shape);

    // Perform element-wise addition
    for (size_t i = 0; i < total_size; ++i) {
        result.data[i] = this->data[i] + other.data[i];
    }

    return result;
}

// Multiply Scalar to Tensor
Tensor Tensor::operator*(const T other) const {
    Tensor result(this->shape);

    for (size_t i = 0; i < get_size(this->shape); i++) {
        std::vector<size_t> idx = result.get_indices(i);
        result(idx) = (*this)(idx) * other;
    }

    return result;
}



// Multiply Tensors
Tensor Tensor::operator*(const Tensor other) const {
    std::vector<size_t> result_shape;
    // Concatenate both tensor shape to a new vector
    for (size_t dim : this->shape) {
        result_shape.insert(result_shape.end(), dim);
    }
    for (size_t dim : other.get_shape()) {
        result_shape.insert(result_shape.end(), dim);
    }

    // Create new Tensor object
    Tensor result(result_shape);
    std::vector<size_t> indices(result_shape.size());

    
    for (size_t i = 0; i < get_size(this->shape); i++) {
        std::vector<size_t> idx_outer = get_indices(i);
        for (size_t j = 0; j < get_size(other.get_shape()); j++) {
            std::vector<size_t> idx;
            idx = idx_outer;
            std::vector<size_t> idx_inner = other.get_indices(j);
            for (size_t dim : idx_inner) {
                idx.insert(idx.end(), dim);
            }

            result(idx) = (*this)(idx_outer) * other(idx_inner);
        }
    }


    return result;
}

// Access operator (for both getting and setting values)
T& Tensor::operator()(const std::vector<size_t>& indices) {
    size_t flat_idx = get_flat_index(indices);
    return this->data[flat_idx];
}

// Const version of the access operator (for getting values)
const T& Tensor::operator()(const std::vector<size_t>& indices) const {
    size_t flat_idx = get_flat_index(indices);
    return this->data[flat_idx];
}

// Vector Dot Product
const T Tensor::vecdot(const std::vector<T> t1, const std::vector<T> t2) const {
    T result = 0;
    for (size_t i = 0; i < t1.size(); i++) {
        result += t1[i] * t2[i];
    }
    return result;
}

// Multiply Matrix
const Tensor Tensor::matmul(const Tensor t1, const Tensor t2, size_t depth1, size_t depth2) const {
    assert (t1.get_shape().size() == 2 && t2.get_shape().size() == 2);
    assert (t1.get_shape()[1] == t2.get_shape()[0]);

    Tensor result({t1.get_shape()[1], t2.get_shape()[0]});

    for (size_t i = 0; i < t1.get_shape()[1]; i++) {
        for (size_t j = 0; j < t2.get_shape()[0]; j++) {
            result({i, j}) = vecdot(t1.get_column(i), t2.get_row(j));
        }
    }

    return result;

}

void Tensor::print(const std::vector<size_t>& indices, size_t depth) const {
    if (depth == this->shape.size() - 1) {
        std::cout << "[ ";
        for (size_t i = 0; i < this->shape[depth]; ++i) {
            auto current_indices = indices;
            current_indices.push_back(i);
            if ((*this)(current_indices) > 0) std::cout << " ";
            std::cout << std::fixed << std::setprecision(8) << (*this)(current_indices) << " ";  // Call to const version of operator()
        }
        std::cout << "]";
    } else {
        std::cout << "[ ";
        for (size_t i = 0; i < this->shape[depth]; ++i) {
            auto current_indices = indices;
            current_indices.push_back(i);
            print(current_indices, depth + 1);  // Recursively call print()
            if (i < this->shape[depth] - 1) {
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