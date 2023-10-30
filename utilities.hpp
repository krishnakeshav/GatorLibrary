#pragma once

#include <string>

#define Yes "Yes"
#define No "No"
#define INVALID_STATUS "Invalid Status"

using namespace std;

enum BookAvailability
{
    YES,
    NO
};

class utilities
{
private:
    /* data */
public:
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
