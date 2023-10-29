#include "reservation.hpp"

reservation::reservation(int patronId, int priorityNumber, string timeOfReservation)
{
    PatronId = patronId;
    PriorityNumber = priorityNumber;
    TimeOfReservation = timeOfReservation;
}