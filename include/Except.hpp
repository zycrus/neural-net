#ifndef EXCEPT_HPP
#define EXCEPT_HPP

#pragma once

#include <exception>
#include <iostream>
#include <string>

using namespace std;

// Define a new exception class that inherits from
// std::exception
class Exception : public exception {
private:
    string message;

public:
    // Constructor accepts a const char* that is used to set
    // the exception message
    Exception(const char* msg);

    // Override the what() method to return our message
    const char* what() const throw();
};

#endif