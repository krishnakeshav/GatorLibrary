#include "reservation.hpp"

#include <ctime>
#include <iostream>

/// @brief 
/// @param patronId 
/// @param priorityNumber 
reservation::reservation(int patronId, int priorityNumber)
{
    PatronId = patronId;
    PriorityNumber = priorityNumber;
    time_t now = time(0);
    //cout << "New reservation created at " << ctime(&now) << " for patron " << patronId << endl;
    TimeOfReservation = ctime(&now);
}