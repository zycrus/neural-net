#include "Tensor.hpp"

using namespace std;

Tensor(vector<int> shape): shape(shape){}

template<typename T>
Tensor<T> Tensor<T>::generate_random(vector<int> _shape) {
    Tensor tensor(_shape);

    return tensor;
}

// vector<vector<T>> Tensor::generate_random() {
//     static thread_local mt19937 gen{random_device{}()};
//     normal_distribution<T> d(0.0, 1.0);  // Specify mean and stddev

//     vector<vector<T>> random_matrix(x, vector<T>(y));

//     // Genrate and insert random value from the normal distribution to the matrix
//     for (int i = 0; i < x; i++) {
//         for (int j = 0; j < y; j++) {
//             random_matrix[i][j] = d(gen);
//         }
//     }

//     return random_matrix;
// }

// template<typename T>
// vector<vector<vector<T>>> Tensor::generate_random() {
// 	vector<vector<vector<T>>> random_tensor(x, vector<vector<T>>(y, vector<T>(z)));

//     // Generate and insert random value from the normal distribution to the matrix
//     for (int i = 0; i < x; i++) {
//         random_tensor[i] = generate_random<T, dims[0], z>();
//     }

//     return random_tensor;
// }

// template<typename T>
// vector<vector<vector<vector<T>>>> Tensor::generate_random() {
// 	vector<vector<vector<vector<T>>>> random_tensor(dims[0], vector<vector<vector<T>>>(dims[1], vector<vector<T>>(dims[2], vector<T>(dims[3]))));

//     // Generate and insert random value from the normal distribution to the matrix
//     for (int i = 0; i < dims[0]; i++) {
//         random_tensor[i] = generate_random<T>();
//     }

//     return random_tensor;
// }

// template<typename T>
// void Tensor::print(vector<vector<T>> matrix) {
// 	int x = matrix.size();
// 	int y = matrix[0].size();
// 	for (int i = 0; i < x; i++) {
//         for (int j = 0; j < y; j++) {
//             cout << fixed << setprecision(8) << matrix[i][j] << "\t";
//         }
//         cout << endl;
//     }
// }

// template<typename T>
// void Tensor::print(vector<vector<vector<T>>> tensor) {
// 	int x = tensor.size();
// 	for (int i = 0; i < x; i++) {
//         cout << "[" << i << ":;:;]" << endl;
//         print<T>(tensor[i]);
//         cout << endl;
//     }
// }

// template<typename T>
// void Tensor::print(vector<vector<vector<vector<T>>>> tensor) {
// 	int x = tensor.size();
// 	for (int i = 0; i < x; i++) {
//         cout << "[" << i << ":;:;:;]" << endl;
//         print<T>(tensor[i]);
//         cout << endl;
//     }
// }