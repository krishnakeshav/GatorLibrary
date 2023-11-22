#include "reservation.hpp"

#include <ctime>
#include <iostream>


reservation::reservation(int patronId, int priorityNumber)
{
    PatronId = patronId;
    PriorityNumber = priorityNumber;
    time_t now = time(0);
    TimeOfReservation = ctime(&now);
}