#include "Tensor.hpp"

using namespace std;

template<typename T, size_t x, size_t y>
vector<vector<T>> Tensor::generate_random() {
    static thread_local mt19937 gen{random_device{}()};
    normal_distribution<T> d(0.0, 1.0);  // Specify mean and stddev

    vector<vector<T>> random_matrix(x, vector<T>(y));

    // Genrate and insert random value from the normal distribution to the matrix
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            random_matrix[i][j] = d(gen);
        }
    }

    return random_matrix;
}

// template<typename T, size_t x, size_t y, size_t z>
// vector<vector<vector<T>>> Tensor::generate_random() {
// 	vector<vector<vector<T>>> random_tensor(x, vector<vector<T>>(y, vector<T>(z)));

//     // Generate and insert random value from the normal distribution to the matrix
//     for (int i = 0; i < x; i++) {
//         random_tensor[i] = generate_random<T, y, z>();
//     }

//     return random_tensor;
// }

// template<typename T, size_t batch_size, size_t height, size_t width, size_t color>
// vector<vector<vector<vector<T>>>> Tensor::generate_random() {
// 	vector<vector<vector<vector<T>>>> random_tensor(batch_size, vector<vector<vector<T>>>(height, vector<vector<T>>(width, vector<T>(color))));

//     // Generate and insert random value from the normal distribution to the matrix
//     for (int i = 0; i < batch_size; i++) {
//         random_tensor[i] = generate_random<T, height, width, color>();
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