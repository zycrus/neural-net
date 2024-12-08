#include <iostream>
#include <vector>
#include <random>
#include <iomanip>
#include <chrono>

using namespace std;

#define T float

typedef vector<T> vec;
typedef vector<vector<T>> mat;
typedef vector<vector<vector<T>>> tens3;
typedef vector<vector<vector<vector<T>>>> tens4;

class TensorOps
{
public:
    template<size_t x, size_t y>
    mat generate_random();

    template<size_t x, size_t y, size_t z>
    tens3 generate_random();

    template<size_t batch_size, size_t height, size_t width, size_t color>
    tens4 generate_random();

    void print(mat matrix);

    void print(tens3 tensor);

    void print(tens4 tensor);
} TensorOps;

class Tensor {
private:
    vector<T> data;     // Flat Data Storage
    vector<size_t> shape;  // Tensor Dimensions
    size_t total_size;  // Total number of elements in the Tensor

    // Helper function to calculate total size
    size_t get_size(const vector<size_t>& dims) {
        size_t size = 1;
        for (auto dim : dims)
            size *= dim;
        return size;
    }

    // Helper function to compute flat index from multi-dimensional indices
    size_t get_flat_index(const vector<size_t>& indices) const {
        size_t index = 0;
        size_t stride = 1;
        for (int i = shape.size() - 1; i >= 0; i--) {
            index += indices[i] * stride;
            stride *= shape[i];
        }
        return index;
    }
public:
    // Constructor with shape
    Tensor(const vector<size_t>& dims) : shape(dims) {
        total_size = get_size(dims);
        data.resize(total_size);
    }

     // Fill tensor with a specific value
    void fill(const T& value) {
        std::fill(data.begin(), data.end(), value);
    }

    // Print tensor data
    void print() const {
        size_t rows = 1;
        size_t cols = shape[shape.size() - 1];
        if (shape.size() > 0) {
            rows = shape[shape.size() - 2];
        }
        for (size_t i = 0; i < total_size; ++i) {
            if (i >= cols*rows && i % (cols*rows) == 0) {
                // cout << endl;
                // cout << i << " : " << cols << " x " << rows << " = " << cols*rows << ", " << i % cols*rows;
                cout << endl;
            }
            if (i >= cols && i % cols == 0) {
                // cout << endl;
                // cout << i << " : " << cols;
                cout << endl;
            }
            cout << data[i] << " ";
        }

        cout << endl;
    }
};

void run() {
	// vector<vector<vector<float>>> t = Tensor.generate_random<float, 5, 5, 5>();

	// Tensor.print<float>(t);

    // tens4 mat1 = TensorOps.generate_random<5, 3, 3, 3>();
    // TensorOps.print(mat1);

    Tensor t({2, 2, 3, 5});
    t.fill(1);
    t.print();

}

int main() {

	auto start = chrono::high_resolution_clock::now();

    // Call the function or block of code whose runtime you want to measure
    run();

    // Get the end point of the timer
    auto end = chrono::high_resolution_clock::now();

    // Calculate the duration (end - start) in milliseconds
    chrono::duration<double, std::milli> duration = end - start;

    // Print the runtime in milliseconds
    cout << "Execution time: " << duration.count() << " ms" << endl;

	return 0;
}













// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// TENSOR OPERATIONS

template<size_t x, size_t y>
mat TensorOps::generate_random() {
    static thread_local mt19937 gen{random_device{}()};
    normal_distribution<T> d(0.0, 1.0);  // Specify mean and stddev

    mat random_matrix(x, vec(y));

    // Genrate and insert random value from the normal distribution to the matrix
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            random_matrix[i][j] = d(gen);
        }
    }

    return random_matrix;
}

template<size_t x, size_t y, size_t z>
tens3 TensorOps::generate_random() {
    tens3 random_tensor(x, mat(y, vec(z)));

    // Generate and insert random value from the normal distribution to the matrix
    for (int i = 0; i < x; i++) {
        random_tensor[i] = generate_random<y, z>();
    }

    return random_tensor;
}

template<size_t batch_size, size_t height, size_t width, size_t color>
tens4 TensorOps::generate_random() {
    tens4 random_tensor(batch_size, tens3(height, mat(width, vec(color))));

    // Generate and insert random value from the normal distribution to the matrix
    for (int i = 0; i < batch_size; i++) {
        random_tensor[i] = generate_random<height, width, color>();
    }

    return random_tensor;
}

void TensorOps::print(mat matrix) {
    int x = matrix.size();
    int y = matrix[0].size();
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            cout << fixed << setprecision(8) << matrix[i][j] << "\t";
        }
        cout << endl;
    }
}

void TensorOps::print(tens3 tensor) {
    int x = tensor.size();
    for (int i = 0; i < x; i++) {
        cout << "[" << i << ":;:;]" << endl;
        print(tensor[i]);
        cout << endl;
    }
}

void TensorOps::print(tens4 tensor) {
    int x = tensor.size();
    for (int i = 0; i < x; i++) {
        cout << "[" << i << ":;:;:;]" << endl;
        print(tensor[i]);
        cout << endl;
    }
}