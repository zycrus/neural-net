#include <iostream>
#include <vector>
#include <random>
#include <iomanip>
#include <chrono>

#include "Tensor.hpp"

using namespace std;




void run() {
	Tensor tens;
	vector<vector<float>> t = tens.generate_random<float, 5, 5>();

	// Tensor.print<float>(tensor);
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