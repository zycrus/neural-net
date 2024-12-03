#include <iostream>
// #include <Eigen/Dense>
#include <Fastor.h>
#include <cmath>
#include <vector>
#include <random>
#include <memory>
#include <omp.h>


#include <chrono>

using namespace std;
using namespace Fastor;


template<size_t x , size_t y>
Tensor<float, x, y> RandomMatrix() {
    // Define the mean and standard deviation
    double mean = 0.0;
    double stddev = 1.0;

    // Create a random device and seed the generator
    random_device rd;
    mt19937 gen(rd());

    // Create a normal distribution with the specified mean and standard deviation
    normal_distribution<> d(mean, stddev);

    Tensor<float, x, y> random_matrix;

    // Genrate and insert random value from the normal distribution to the matrix
    for (int i = 0; i < x; i++){
        for (int j = 0; j < y; j++){
            random_matrix(i, j) = d(gen);
        }
    }

    return random_matrix;
}

template<size_t x , size_t y, size_t z>
Tensor<float, x, y, z> RandomMatrix() {
    // Define the mean and standard deviation
    double mean = 0.0;
    double stddev = 1.0;

    // Create a random device and seed the generator
    random_device rd;
    mt19937 gen(rd());

    // Create a normal distribution with the specified mean and standard deviation
    normal_distribution<> d(mean, stddev);

    Tensor<float, x, y, z> random_matrix;

    // Genrate and insert random value from the normal distribution to the matrix
    for (int i = 0; i < x; i++){
        for (int j = 0; j < y; j++){
            for (int k = 0; k < z; k++){
                random_matrix(i, j, k) = d(gen);
            }
        }
    }

    return random_matrix;
}

template<size_t x, size_t y>
Tensor<float, x, y> Mask(float lower=0, float upper=-numeric_limits<float>::infinity()) {
    Tensor<float, x, y> mask;
    for (int i = 0; i < x; i++){
        for (int j = 0; j < y; j++){
            if (i < j) mask(i, j) = upper;
            else mask(i, j) = lower;
        }
    }
    return mask;
}

/*
    Softmax
*/
template<size_t x, size_t y>
Tensor<float, x, y> Softmax(const Tensor<float, x, y>& scaled) {
    Tensor<float, x, y> expScaled = exp(scaled);
    Tensor<float, x, y> sumExpScaled = sum(expScaled);
    Tensor<float, x, y> softmax = expScaled/sumExpScaled;

    return softmax;
}

/*
    Single-Headed Attention
*/
template<size_t L, size_t dk, size_t dv>
Tensor<float, L, dv> SingleHeadAttention(const Tensor<float, L, dk>& q,const Tensor<float, L, dk>& k, const Tensor<float, L, dv>& v, bool isMasked=false, bool display=false) {
    // Scaled
    Tensor<float, L, L> scaled = matmul(q, transpose(k)) / sqrt(dk);
    if (isMasked) scaled += Mask<L, L>();

    // Softmax
    Tensor<float, L, L> softmax = Softmax<L, L>(scaled);

    // Attention
    Tensor<float, L, dv> attention = matmul(softmax, v);

    if (display) {
        cout << "Q:\n";
        cout << q << "\n\n";

        cout << "K:\n";
        cout << k << "\n\n";

        cout << "V:\n";
        cout << v << "\n\n";

        cout << "Softmax\n";
        cout << softmax << "\n\n";

        cout << "Single-headed Attention:\n";
        cout << attention << "\n\n";
    }

    return attention;
}

template<size_t in, size_t out>
class Linear {
public:
    vector<vector<float>> weights;
    vector<float> bias;


    Linear(){
        weights.resize(out, vector<float>(in));
        bias.resize(out);

        random_device rd;
        mt19937 gen(rd());
        normal_distribution<> dist(0.0, 1.0 / sqrt(in));

        // Initialize weights
        for (size_t i = 0; i < out; ++i) {
            for (size_t j = 0; j < in; ++j) {
                weights[i][j] = dist(gen);
            }
        }

        // Initialize biases
        for (size_t i = 0; i < out; ++i) {
            bias[i] = dist(gen);
        }
    }

    template<size_t batch_size, size_t sequence_length, size_t input_dim>
    Tensor<float, batch_size, sequence_length, out> forward(const Tensor<float, batch_size, sequence_length, input_dim>& input) {
        if (input.dimension(2) != in) {
            throw std::invalid_argument("Input size does not match the size of the weight matrix.");
        }

        Tensor<float, batch_size, sequence_length, out> output;
        output.zeros();

        // Matrix multiplication between input and weights
        #pragma omp parallel for collapse(3) schedule(static)
        for (size_t b = 0; b < batch_size; b++) {
            for (size_t s = 0; s < sequence_length; s++) {
                for (size_t i = 0; i < out; i++) {
                    float temp = bias[i];  // Initialize with bias to avoid extra addition
                    #pragma omp simd
                    for (size_t j = 0; j < in; j++) {
                        temp += weights[i][j] * input(b, s, j);
                    }
                    output(b, s, i) = temp;
                }
            }
        }

        return output;
    }
};


template<size_t ... Rest>
constexpr size_t get_dim(const Tensor<float, Rest...>& tensor, size_t dim) {
    return tensor.dimension(dim);
}

// General chunking function for any rank of tensor
template<size_t FirstDim, size_t... Rest>
vector<Tensor<float, FirstDim / 2, Rest...>> chunk_tensor(const Tensor<float, FirstDim, Rest...>& tensor, int num_chunks) {
    // Calculate the size of each chunk along the first dimension
    size_t chunk_size = FirstDim / num_chunks;
    size_t remainder = FirstDim % num_chunks;

    // Store chunks
    vector<Tensor<float, chunk_size, Rest...>> chunks;

    // Slice along the first dimension while keeping other dimensions intact
    for (int i = 0; i < num_chunks; ++i) {
        if (i == num_chunks - 1 && remainder != 0) {
            // Last chunk with remainder handling
            Tensor<float, chunk_size + remainder, Rest...> chunk = tensor(range(i * chunk_size, FirstDim), All...);
            chunks.push_back(chunk);
        } else {
            // Regular chunk
            Tensor<float, chunk_size, Rest...> chunk = tensor(range(i * chunk_size, (i + 1) * chunk_size), All...);
            chunks.push_back(chunk);
        }
    }
    return chunks;
}



// void test1() {
//     const int L = 4; const int dk = 8; const int dv = 8;
//     Tensor<float, L, dk> q = RandomMatrix<L, dk>();
//     Tensor<float, L, dk> k = RandomMatrix<L, dk>();
//     Tensor<float, L, dv> v = RandomMatrix<L, dv>();

//     Single-headed Attention
//     auto attention = SingleHeadAttention<L, dk, dv>(q, k, v, false, true);
// }


void test2() {
    const int sequence_length = 4;
    const int batch_size = 1;
    const int input_dim = 512;
    const int d_model = 512;

    Tensor<float, batch_size, sequence_length, input_dim> x = RandomMatrix<batch_size, sequence_length, input_dim>();

    Linear<input_dim, 3 * d_model> qkv_layer = Linear<input_dim, 3 * d_model>();

    cout << x.dimension(0) << " " << x.dimension(1) << " " << x.dimension(2) << endl;

    Tensor<float, batch_size, sequence_length, 3 * d_model> qkv = qkv_layer.forward<batch_size, sequence_length, input_dim>(x);

    cout << qkv.dimension(0) << " " << qkv.dimension(1) << " " << qkv.dimension(2) << endl;

    const int num_heads = 8;
    const int head_dim = d_model / num_heads;
    Tensor<float, batch_size, sequence_length, num_heads, 3 * head_dim> qkv_reshaped = reshape<batch_size, sequence_length, num_heads, 3 * head_dim>(qkv);

    cout << qkv_reshaped.dimension(0) << " " << qkv_reshaped.dimension(1) << " " << qkv_reshaped.dimension(2) << " " << qkv_reshaped.dimension(3) << endl;

    Tensor<float, batch_size, num_heads, sequence_length, 3 * head_dim> qkv_permuted = permute<Index<0, 2, 1, 3>>(qkv_reshaped);

    cout << qkv_permuted.dimension(0) << " " << qkv_permuted.dimension(1) << " " << qkv_permuted.dimension(2) << " " << qkv_permuted.dimension(3) << endl;

    // vector<Tensor<float, batch_size, num_heads, sequence_length, head_dim>> = chunk<float, batch_size, num_heads, sequence_length, head_dim>(qkv_permuted, 3, 3);



    // cout << mask << endl;
}


int main(){

    auto start = chrono::high_resolution_clock::now();

    // Call the function or block of code whose runtime you want to measure
    test2();

    // Get the end point of the timer
    auto end = chrono::high_resolution_clock::now();

    // Calculate the duration (end - start) in milliseconds
    chrono::duration<double, std::milli> duration = end - start;

    // Print the runtime in milliseconds
    cout << "Execution time: " << duration.count() << " ms" << endl;

    return 0;
}