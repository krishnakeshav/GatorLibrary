
/**
 * @file utilities.hpp
 * @brief This file contains the declaration of the utilities class and the BookAvailability enum.
 */

#pragma once

#include <string>

/// @brief String representation of the YES enum value.
#define Yes "Yes"

/// @brief String representation of the NO enum value.
#define No "No"


/// @brief String representation of the NO enum value.
#define INVALID_STATUS "Invalid Status"

using namespace std;

/**
 * @enum BookAvailability
 * @brief Enum representing the availability status of a book.
 */
enum BookAvailability
{
    YES, /**< The book is available. */
    NO /**< The book is not available. */
};

/**
 * @class utilities
 * @brief A utility class providing conversion functions for the BookAvailability enum.
 */
class utilities
{
private:
    /* data */
public:
    /**
     * @brief Converts a BookAvailability enum value to its corresponding string representation.
     * @param status The BookAvailability enum value.
     * @return The string representation of the BookAvailability enum value.
     * @throws string Thrown if an invalid BookAvailability enum value is provided.
     */
    static const string status_tostring(BookAvailability status)
    {
        if (status == YES)
        {
            return Yes;
        }
        else if (status == NO)
        {
            return No;
        }
        else
        {
            throw INVALID_STATUS;
        }
    }

    /**
     * @brief Converts a string representation of a BookAvailability enum value to the corresponding enum value.
     * @param status The string representation of the BookAvailability enum value.
     * @return The BookAvailability enum value.
     * @throws string Thrown if an invalid string representation is provided.
     */
    static const BookAvailability status_toenum(string status)
    {
        if (status == Yes)
        {
            return YES;
        }
        else if (status == No)
        {
            return NO;
        }
        else
        {
            throw INVALID_STATUS;
        }
    }
};
