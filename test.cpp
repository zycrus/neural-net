#include <iostream>
// #include <Eigen/Dense>
#include <Fastor.h>
#include <cmath>
#include <vector>
#include <random>

using namespace std;
// using namespace Eigen;

// MatrixXd Mask(int size, float lower=0, float upper=-numeric_limits<float>::infinity());

// MatrixXd Softmax(const MatrixXd &x) {
//     MatrixXd exp_x = x.array().exp();
//     return exp_x.array().colwise() / exp_x.rowwise().sum().array();
// }

// MatrixXd ScaledDotProductAttention(const MatrixXd &Q, const MatrixXd &K, const MatrixXd &V, double scale_factor, bool isMasked=false) {
//     MatrixXd scores = (Q * K.transpose()) / std::sqrt(scale_factor);
//     if (isMasked) scores += Mask(scores.rows());
//     MatrixXd attention_weights = Softmax(scores);

//     // //Display
//     // if (isMasked) {
//     //     cout << "Mask: \n";
//     //     cout << Mask(attention_weights.rows()) << "\n\n";
//     // }
//     // cout << "Softmax: \n";
//     // cout << attention_weights << "\n\n";

//     return attention_weights * V;
// }

// MatrixXd RandomMatrix(int rows, int cols) {
//     // Initialize random number generator with a random seed
//     random_device rd;
//     mt19937 gen(rd());
    
//     // Standard normal distribution (mean = 0, stddev = 1)
//     normal_distribution<> dist(0.0, 1.0);
    
//     // Create a matrix of given size
//     MatrixXd matrix(rows, cols);
    
//     // Fill the matrix with random numbers
//     for (int i = 0; i < rows; ++i) {
//         for (int j = 0; j < cols; ++j) {
//             matrix(i, j) = dist(gen);  // Sample from the standard normal distribution
//         }
//     }
    
//     return matrix;
// }

// MatrixXd Mask(int size, float lower, float upper) {
//     MatrixXd res = MatrixXd(size, size);
//     for (int i = 0; i < size; i++){
//         for (int j = 0; j < size; j++){
//             if (i >= j) res(i, j) = lower;
//             else res(i, j) = upper;
//         }
//     }
//     return res;
// }

// void test() {
//     cout << "test" << endl;

//     int l = 4;
//     int dv = 8;
//     int dk = 8;
//     MatrixXd q = RandomMatrix(l, dk);
//     MatrixXd k = RandomMatrix(l, dk);
//     MatrixXd v = RandomMatrix(l, dv);

//     cout << "Q\n";
//     cout << q << "\n\n";
//     cout << "K\n";
//     cout << k << "\n\n";
//     cout << "V\n";
//     cout << v << "\n\n";

//     cout << "Scaled Attention\n";
//     MatrixXd attention = ScaledDotProductAttention(q, k, v, dk);

//     cout << attention << "\n\n";

//     cout << "[MASKED] Scaled Attention\n";
//     MatrixXd attentionMasked = ScaledDotProductAttention(q, k, v, dk, true);

//     cout << attentionMasked << "\n\n";
// }

template<size_t x, size_t y, size_t z>
Fastor::Tensor<double, x, y, z> RandomMatrix() {
    // Initialize random number generator with a random seed
    std::random_device rd;
    std::mt19937 gen(rd());
    
    // Standard normal distribution (mean = 0, stddev = 1)
    std::normal_distribution<> dist(0.0, 1.0);
    
    // Create a Fastor tensor of the given size
    Fastor::Tensor<double, x, y, z> tensor;
    
    // Fill the tensor with random numbers
    for (size_t i = 0; i < x; i++) {
        for (size_t j = 0; j < y; j++) {
            for (size_t k = 0; k < z; k++) {
                tensor(i, j, k) = dist(gen);  // Sample from the standard normal distribution
            }
        }
    }
    
    return tensor;
}

void test2() {
    const int sequence_length = 4;
    const int batch_size = 1;
    const int input_dim = 512;
    int d_model = 512;
    auto x = RandomMatrix<batch_size, sequence_length, input_dim>();


}


int main(){
    test2();

    return 0;
}