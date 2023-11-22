
#pragma once

#include <string>
#include <queue>

using namespace std;

/**
 * @file reservation.hpp
 * @class reservation
 * @brief The reservation class stores the priority number, patron id, and the time of reservation.
 */
class reservation
{
private:
    /* data */
public:
    int PatronId; /**< The ID of the patron. */
    int PriorityNumber; /**< The priority number of the reservation. */
    string TimeOfReservation; /**< The time of the reservation. */

    /**
     * @brief Constructs a new reservation object.
     * 
     * @param patronId The ID of the patron.
     * @param priorityNumber The priority number of the reservation.
     */
    reservation(int patronId, int priorityNumber);
};

/**
 * @brief The Compare class is used as a comparison function for the reservation class.
 */
class Compare
{
private:
    /* data */
public:
    /**
     * @brief Overloaded function call operator to compare two reservations.
     * 
     * @param a The first reservation to compare.
     * @param b The second reservation to compare.
     * @return true if a has higher priority than b, false otherwise.
     */
    bool operator () (reservation a, reservation b)
    {
        if (a.PriorityNumber > b.PriorityNumber)
        {
            return true;
        }
        else if (a.PriorityNumber == b.PriorityNumber)
        {
            if (a.TimeOfReservation > b.TimeOfReservation)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
};
