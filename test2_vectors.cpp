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

class Tensor
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
} Tensor;


void run() {
	// vector<vector<vector<float>>> t = Tensor.generate_random<float, 5, 5, 5>();

	// Tensor.print<float>(t);

    tens4 mat1 = Tensor.generate_random<5, 3, 3, 3>();
    Tensor.print(mat1);
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
// TENSOR

template<size_t x, size_t y>
mat Tensor::generate_random() {
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
tens3 Tensor::generate_random() {
    tens3 random_tensor(x, mat(y, vec(z)));

    // Generate and insert random value from the normal distribution to the matrix
    for (int i = 0; i < x; i++) {
        random_tensor[i] = generate_random<y, z>();
    }

    return random_tensor;
}

template<size_t batch_size, size_t height, size_t width, size_t color>
tens4 Tensor::generate_random() {
    tens4 random_tensor(batch_size, tens3(height, mat(width, vec(color))));

    // Generate and insert random value from the normal distribution to the matrix
    for (int i = 0; i < batch_size; i++) {
        random_tensor[i] = generate_random<height, width, color>();
    }

    return random_tensor;
}

void Tensor::print(mat matrix) {
    int x = matrix.size();
    int y = matrix[0].size();
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            cout << fixed << setprecision(8) << matrix[i][j] << "\t";
        }
        cout << endl;
    }
}

void Tensor::print(tens3 tensor) {
    int x = tensor.size();
    for (int i = 0; i < x; i++) {
        cout << "[" << i << ":;:;]" << endl;
        print(tensor[i]);
        cout << endl;
    }
}

void Tensor::print(tens4 tensor) {
    int x = tensor.size();
    for (int i = 0; i < x; i++) {
        cout << "[" << i << ":;:;:;]" << endl;
        print(tensor[i]);
        cout << endl;
    }
}