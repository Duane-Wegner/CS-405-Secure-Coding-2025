// 2 - 3 Activity: Buffer Overflow Coding
// Duane Wegner
// Southern New Hampshire University
// CS - 405 Secure Coding
// Alan Spencer, Adjunct Instructor(M.S)
// July 10, 2025

// BufferOverflow.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iomanip>
#include <iostream>
#include <limits>  // Needed for numeric_limits 
#include <cctype>  // Needed for std::tolower() \

int main()
{
    std::cout << "Buffer Overflow Example" << std::endl;

    // TODO: The user can type more than 20 characters and overflow the buffer, resulting in account_number being replaced -
    //  even though it is a constant and the compiler buffer overflow checks are on.
    //  You need to modify this method to prevent buffer overflow without changing the account_number
    //  variable, and its position in the declaration. It must always be directly before the variable used for input.
    //  You must notify the user if they entered too much data.

    // Requirement: Do not change position of account_number and user_input
    const std::string account_number = "CharlieBrown42";
    char user_input[20];

    char try_again = 'y';

    while (std::tolower(try_again) == 'y')  // Loop until the user decides to stop
    {
        bool valid_input = false;

        while (!valid_input)
        {
            std::cout << "\nEnter a value: ";

            // Changed from simple std::cin >> user_input to std::cin.getline()
            // to limit input length and prevent buffer overflow by reading at most 19 chars + null terminator
            std::cin.getline(user_input, sizeof(user_input));

            if (std::cin.fail()) {  // Detect if input was too long for the buffer
                std::cin.clear();  // Clear the error state to allow further input operations
                // Discard any remaining characters left in the input buffer
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                // Inform the user about the overflow attempt and prompt for correct input
                std::cout << "Input too long! Please enter 19 characters or fewer." << std::endl;
            }
            else {
                valid_input = true;  // Input fits in buffer, so proceed

                // Output the entered value and confirm that account_number remains unchanged
                std::cout << "You entered: " << user_input << std::endl;
                std::cout << "Account Number = " << account_number << std::endl;
            }
        }

        // Ask user if they want to enter another value; using std::tolower to accept 'Y' or 'y'
        std::cout << "\nDo you want to enter another value? (y/n): ";
        std::cin >> try_again;

        // Remove newline leftover in the input buffer to prevent it affecting next getline call
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "Program ended. Goodbye!" << std::endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
