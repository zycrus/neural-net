#pragma once
#ifndef TENS_HPP
#define TENS_HPP

#include<vector>

#define T float

class Tensor {
private:
	std::vector<T> data;     // Flat Data Storage
   std::vector<size_t> shape;  // Tensor Dimensions
   size_t total_size;  // Total number of elements in the Tensor

	// Helper function to compute flat index from multi-dimensional indices
	size_t get_flat_index(const std::vector<size_t>& indices) const;

 public:
    // Constructor with shape
	Tensor(const std::vector<size_t>& dims);

    // Constructor with data and shape
	Tensor(const std::vector<T>& data, const std::vector<size_t>& dims);

   // Helper function to calculate total size
   size_t get_size(const std::vector<size_t>& dims) const;

   // Convert flat index to tensor indices
   std::vector<size_t> get_indices(const size_t flat_index) const;

	// Getter for shape
	const std::vector<size_t> get_shape() const;

	 // Fill tensor with a specific value
	void fill(const T& value);

	// Generate Random Tensor values
	void generate_random();

	// Get Column
	const std::vector<T> get_row(size_t row) const;

	// Get Column
	const std::vector<T> get_column(size_t col) const;

	// Print Tensor
	void print(const std::vector<size_t>& indices = {}, size_t depth = 0) const;

	// Vector Dot Product
	const T vecdot(const std::vector<T> t1, const std::vector<T> t2) const;

	// Multiply Matrix
	const Tensor matmul(const Tensor t1, const Tensor t2, size_t depth1 = 0, size_t depth2 = 0) const;

	// Add operator
	Tensor operator+(const Tensor other) const;

	// Multiply Scalar to Tensor
	Tensor operator*(const T other) const;

	// Multiply Tensor
	Tensor operator*(const Tensor other) const;

	// Access operator (for both getting and setting values)
    T& operator()(const std::vector<size_t>& indices);

    // Const version of the access operator (for getting values)
    const T& operator()(const std::vector<size_t>& indices) const;
};

#endif
