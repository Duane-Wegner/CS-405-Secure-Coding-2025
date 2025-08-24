// Duane Wegner
// July 3, 2025
// CS-405 Module 1 
// 1-3 Activity: Numeric Overflow Coding
// SNHU


// NumericOverflows.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>     // std::cout
#include <limits>       // std::numeric_limits
#include <typeinfo>     // typeid

/// <summary>
/// Template function to abstract away the logic of:
///   start + (increment * steps)
/// </summary>
/// <typeparam name="T">A type that with basic math functions</typeparam>
/// <param name="start">The number to start with</param>
/// <param name="increment">How much to add each step</param>
/// <param name="steps">The number of steps to iterate</param>
/// <param name="success">Output flag indicating if addition completed without overflow</param>
/// <returns>start + (increment * steps), or partial result if overflow prevented</returns>
template <typename T>
T add_numbers(T const& start, T const& increment, unsigned long int const& steps, bool& success)
{
    T result = start;
    success = true; // Assume success until overflow detected

    for (unsigned long int i = 0; i < steps; ++i)
    {
        // Check if next addition would cause overflow
        // For signed and unsigned integers and floating point,
        // the condition differs slightly.
        // Use numeric_limits to check max, min accordingly

        if (increment > 0)
        {
            // Prevent overflow:
            // If result > max - increment, next addition would overflow
            if (result > std::numeric_limits<T>::max() - increment)
            {
                success = false; // Overflow detected
                return result;   // Return early to prevent overflow
            }
        }
        else if (increment < 0)
        {
            // Prevent underflow in addition of negative increment:
            // If result < min - increment, next addition would underflow
            if (result < std::numeric_limits<T>::min() - increment)
            {
                success = false; // Underflow detected
                return result;
            }
        }
        // else increment == 0, safe to add

        result += increment;
    }

    return result;
}

/// <summary>
/// Template function to abstract away the logic of:
///   start - (increment * steps)
/// </summary>
/// <typeparam name="T">A type that with basic math functions</typeparam>
/// <param name="start">The number to start with</param>
/// <param name="decrement">How much to subtract each step</param>
/// <param name="steps">The number of steps to iterate</param>
/// <param name="success">Output flag indicating if subtraction completed without underflow</param>
/// <returns>start - (decrement * steps), or partial result if underflow prevented</returns>
template <typename T>
T subtract_numbers(T const& start, T const& decrement, unsigned long int const& steps, bool& success)
{
    T result = start;
    success = true; // Assume success until underflow detected

    for (unsigned long int i = 0; i < steps; ++i)
    {
        // Check if next subtraction would cause underflow

        if (decrement > 0)
        {
            // Prevent underflow:
            // If result < min + decrement, next subtraction would underflow
            if (result < std::numeric_limits<T>::min() + decrement)
            {
                success = false; // Underflow detected
                return result;   // Return early to prevent underflow
            }
        }
        else if (decrement < 0)
        {
            // If decrement is negative, subtracting negative is addition,
            // so check for overflow instead
            if (result > std::numeric_limits<T>::max() + decrement)
            {
                success = false; // Overflow detected in this case
                return result;
            }
        }
        // else decrement == 0, safe to subtract

        result -= decrement;
    }

    return result;
}


//  NOTE:
//    You will see the unary ('+') operator used in front of the variables in the test_XXX methods.
//    This forces the output to be a number for cases where cout would assume it is a character. 

template <typename T>
void test_overflow()
{
    // TODO: The add_numbers template function will overflow in the second method call
    //        You need to change the add_numbers method to:
    //        1. Detect when an overflow will happen
    //        2. Prevent it from happening
    //        3. Return the correct value when no overflow happened or
    //        4. Return something to tell test_overflow the addition failed
    //        NOTE: The add_numbers method must remain a template in the NumericFunctions header.
    //
    //        You need to change the test_overflow method to:
    //        1. Detect when an add_numbers failed
    //        2. Inform the user the overflow happened
    //        3. A successful result displays the same result as before you changed the method
    //        NOTE: You cannot change anything between START / END DO NOT CHANGE
    //              The test_overflow method must remain a template in the NumericOverflows source file
    //
    //  There are more than one possible solution to this problem. 
    //  The solution must work for all of the data types used to call test_overflow() in main().

    // START DO NOT CHANGE
    //  how many times will we iterate
    const unsigned long int steps = 5;
    // how much will we add each step (result should be: start + (increment * steps))
    const T increment = std::numeric_limits<T>::max() / steps;
    // whats our starting point
    const T start = 0;

    std::cout << "Overflow Test of Type = " << typeid(T).name() << std::endl;
    // END DO NOT CHANGE

    std::cout << "\tAdding Numbers Without Overflow (" << +start << ", " << +increment << ", " << steps << ") = ";
    bool success = true;
    T result = add_numbers<T>(start, increment, steps, success);
    std::cout << +result << std::endl;

    // Added this line to clearly show the overflow status after each operation 
    std::cout << "\t\tOverflow Detected? " << (success ? "No" : "Yes") << std::endl;

    std::cout << "\tAdding Numbers With Overflow (" << +start << ", " << +increment << ", " << (steps + 1) << ") = ";
    success = true;
    T result2 = add_numbers<T>(start, increment, steps + 1, success);
    std::cout << +result2 << std::endl;

    // Added this line to clearly show the overflow status after each operation
    std::cout << "\t\tOverflow Detected? " << (success ? "No" : "Yes") << std::endl;
}

template <typename T>
void test_underflow()
{
    // TODO: The subtract_numbers template function will underflow in the second method call
    //        You need to change the subtract_numbers method to:
    //        1. Detect when an underflow will happen
    //        2. Prevent it from happening
    //        3. Return the correct value when no underflow happened or
    //        4. Return something to tell test_underflow the subtraction failed
    //        NOTE: The subtract_numbers method must remain a template in the NumericFunctions header.
    //
    //        You need to change the test_underflow method to:
    //        1. Detect when an subtract_numbers failed
    //        2. Inform the user the underflow happened
    //        3. A successful result displays the same result as before you changed the method
    //        NOTE: You cannot change anything between START / END DO NOT CHANGE
    //              The test_underflow method must remain a template in the NumericOverflows source file
    //
    //  There are more than one possible solution to this problem. 
    //  The solution must work for all of the data types used to call test_overflow() in main().

    // START DO NOT CHANGE
    //  how many times will we iterate
    const unsigned long int steps = 5;
    // how much will we subtract each step (result should be: start - (increment * steps))
    const T decrement = std::numeric_limits<T>::max() / steps;
    // whats our starting point
    const T start = std::numeric_limits<T>::max();

    std::cout << "Underflow Test of Type = " << typeid(T).name() << std::endl;
    // END DO NOT CHANGE

    std::cout << "\tSubtracting Numbers Without Overflow (" << +start << ", " << +decrement << ", " << steps << ") = ";
    bool success = true;
    auto result = subtract_numbers<T>(start, decrement, steps, success);
    std::cout << +result << std::endl;
    std::cout << "\t\tUnderflow Detected? " << (success ? "No" : "Yes") << std::endl;

    std::cout << "\tSubtracting Numbers With Overflow (" << +start << ", " << +decrement << ", " << (steps + 1) << ") = ";
    success = true;
    auto result2 = subtract_numbers<T>(start, decrement, steps + 1, success);
    std::cout << +result2 << std::endl;
    std::cout << "\t\tUnderflow Detected? " << (success ? "No" : "Yes") << std::endl;
}

void do_overflow_tests(const std::string& star_line)
{
    std::cout << std::endl << star_line << std::endl;
    std::cout << "*** Running Overflow Tests ***" << std::endl;
    std::cout << star_line << std::endl;

    // Testing C++ primative times see: https://www.geeksforgeeks.org/c-data-types/
    // signed integers
    test_overflow<char>();
    test_overflow<wchar_t>();
    test_overflow<short int>();
    test_overflow<int>();
    test_overflow<long>();
    test_overflow<long long>();

    // unsigned integers
    test_overflow<unsigned char>();
    test_overflow<unsigned short int>();
    test_overflow<unsigned int>();
    test_overflow<unsigned long>();
    test_overflow<unsigned long long>();

    // real numbers
    test_overflow<float>();
    test_overflow<double>();
    test_overflow<long double>();
}

void do_underflow_tests(const std::string& star_line)
{
    std::cout << std::endl << star_line << std::endl;
    std::cout << "*** Running Undeflow Tests ***" << std::endl;
    std::cout << star_line << std::endl;

    // Testing C++ primative times see: https://www.geeksforgeeks.org/c-data-types/
    // signed integers
    test_underflow<char>();
    test_underflow<wchar_t>();
    test_underflow<short int>();
    test_underflow<int>();
    test_underflow<long>();
    test_underflow<long long>();

    // unsigned integers
    test_underflow<unsigned char>();
    test_underflow<unsigned short int>();
    test_underflow<unsigned int>();
    test_underflow<unsigned long>();
    test_underflow<unsigned long long>();

    // real numbers
    test_underflow<float>();
    test_underflow<double>();
    test_underflow<long double>();
}

/// <summary>
/// Entry point into the application
/// </summary>
/// <returns>0 when complete</returns>
int main()
{
    //  create a string of "*" to use in the console
    const std::string star_line = std::string(50, '*');

    std::cout << "Starting Numeric Underflow / Overflow Tests!" << std::endl;

    // run the overflow tests
    do_overflow_tests(star_line);

    // run the underflow tests
    do_underflow_tests(star_line);

    std::cout << std::endl << "All Numeric Underflow / Overflow Tests Complete!" << std::endl;

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

