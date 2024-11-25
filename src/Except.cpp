#include "Except.hpp"

// Define a new exception class that inherits from
// std::exception
Exception::Exception(const char* msg)
    : message(msg)
{
}

// Override the what() method to return our message
const char* Exception::what() const throw()
{
    return message.c_str();
}

// Usage
// int main()
// {
//     try {
//         // Throw our custom exception
//         throw Exception("This is a custom exception");
//     }
//     catch (Exception& e) {
//         // Catch and handle our custom exception
//         cout << "Caught an exception: " << e.what() << endl;
//     }

//     return 0;
// }