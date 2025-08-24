// 4-1 Activity: Exceptions
// Duane Wegner
// Southern New Hampshire University
// CS - 405 Secure Coding
// Alan Spencer, Adjunct Instructor(M.S)
// July 22, 2025

// Exceptions.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdexcept>  // [ADDED] For standard exception classes like runtime_error and invalid_argument
#include <string>     // [ADDED] For std::string used in the custom exception message

// [ADDED] Custom exception class derived from std::exception
class CustomException : public std::exception {
private:
    std::string message;  // [ADDED] Message to store custom error description
public:
    // [ADDED] Constructor to initialize the error message
    CustomException(const std::string& msg) : message(msg) {}

    // [ADDED] Override the what() method to return the custom error message
    const char* what() const noexcept override {
        return message.c_str();
    }
};

bool do_even_more_custom_application_logic()
{
    // TODO: Throw any standard exception

    std::cout << "Running Even More Custom Application Logic." << std::endl;

    // [ADDED] Throwing a standard exception (runtime_error) as required
    throw std::runtime_error("Standard Exception: Failure in deeper application logic.");

    return true;
}

void do_custom_application_logic()
{
    // TODO: Wrap the call to do_even_more_custom_application_logic()
    //  with an exception handler that catches std::exception, displays
    //  a message and the exception.what(), then continues processing
    std::cout << "Running Custom Application Logic." << std::endl;

    try {
        // [ADDED] Try block wrapping the call to catch standard exceptions
        if (do_even_more_custom_application_logic())
        {
            std::cout << "Even More Custom Application Logic Succeeded." << std::endl;
        }
    }
    catch (const std::exception& e) {
        // [ADDED] Catch and report the exception using the what() method
        std::cerr << "Caught standard exception in custom logic: " << e.what() << std::endl;
    }

    // TODO: Throw a custom exception derived from std::exception
    //  and catch it explictly in main

    // [ADDED] Throwing custom exception to be caught later in main()
    throw CustomException("Custom Exception: Issue in custom application logic.");

    std::cout << "Leaving Custom Application Logic." << std::endl;  // [NOTE] This line won't execute due to the exemption
}

float divide(float num, float den)
{
    // TODO: Throw an exception to deal with divide by zero errors using
    //  a standard C++ defined exception

    // [ADDED] clause to check for division by zero
    if (den == 0.0f) {
        throw std::invalid_argument("Standard Exception: Division by zero is not allowed.");
    }

    return (num / den);
}

void do_division() noexcept
{
    //  TODO: create an exception handler to capture ONLY the exception thrown
    //  by divide.

    float numerator = 10.0f;
    float denominator = 0;

    try {
        // [ADDED] Try block to catch only divide-related exceptions
        auto result = divide(numerator, denominator);
        std::cout << "divide(" << numerator << ", " << denominator << ") = " << result << std::endl;
    }
    catch (const std::invalid_argument& e) {
        // [ADDED] Catch and report invalid_argument exceptions
        std::cerr << "Caught divide() exception: " << e.what() << std::endl;
    }
}

int main()
{
    std::cout << "Exceptions Tests!" << std::endl;

    // TODO: Create exception handlers that catch (in this order):
    //  your custom exception
    //  std::exception
    //  uncaught exception 
    //  that wraps the whole main function, and displays a message to the console.

    try {
        // [ADDED] Wrapping main logic in a try block to handle multiple exception types
        do_division();
        do_custom_application_logic();
    }
    catch (const CustomException& ce) {
        // [ADDED] Catching the custom exception thrown earlier
        std::cerr << "Caught CustomException in main: " << ce.what() << std::endl;
    }
    catch (const std::exception& e) {
        // [ADDED] Catching any remaining standard exceptions
        std::cerr << "Caught std::exception in main: " << e.what() << std::endl;
    }
    catch (...) {
        // [ADDED] Catch-all block for any unknown or uncaught exceptions
        std::cerr << "Caught unknown exception in main." << std::endl;
    }

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
