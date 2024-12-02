#include <iostream>
#include <Eigen/Dense>
#include <cmath>
#include <vector>
#include <random>

using namespace std;
using namespace Eigen;

MatrixXd positional_encoding(int max_len, int d_model) {
    MatrixXd pos_enc(max_len, d_model);
    for (int pos = 0; pos < max_len; pos++) {
        for (int i = 0; i < d_model; i += 2) {
            pos_enc(pos, i) = std::sin(pos / std::pow(10000.0, (2 * i) / d_model));
            if (i + 1 < d_model) {
                pos_enc(pos, i + 1) = std::cos(pos / std::pow(10000.0, (2 * i) / d_model));
            }
        }
    }
    return pos_enc;
}

MatrixXd softmax(const MatrixXd &x) {
    MatrixXd exp_x = x.array().exp();
    return exp_x.array().colwise() / exp_x.rowwise().sum().array();
}

MatrixXd scaled_dot_product_attention(const MatrixXd &Q, const MatrixXd &K, const MatrixXd &V, double scale_factor) {
    MatrixXd scores = (Q * K.transpose()) / std::sqrt(scale_factor);
    MatrixXd attention_weights = softmax(scores);
    return attention_weights * V;
}

MatrixXd random_matrix(int rows, int cols) {
    // Initialize random number generator with a random seed
    std::random_device rd;
    std::mt19937 gen(rd());
    
    // Standard normal distribution (mean = 0, stddev = 1)
    std::normal_distribution<> dist(0.0, 1.0);
    
    // Create a matrix of given size
    MatrixXd matrix(rows, cols);
    
    // Fill the matrix with random numbers
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix(i, j) = dist(gen);  // Sample from the standard normal distribution
        }
    }
    
    return matrix;
}



int main(){
    cout << "test" << endl;

    int l = 4;
    int dv = 8;
    int dk = 8;
    MatrixXd q = random_matrix(l, dk);
    MatrixXd k = random_matrix(l, dk);
    MatrixXd v = random_matrix(l, dv);

    cout << "Q\n";
    cout << q << "\n\n";
    cout << "K\n";
    cout << k << "\n\n";
    cout << "V\n";
    cout << v << "\n\n";

    cout << "Scaled Attention\n";
    MatrixXd attention = scaled_dot_product_attention(q, k, v, dk);
    
    cout << attention << "\n\n";

    return 0;
}