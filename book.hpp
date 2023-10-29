#pragma once

#include <string>
#include <queue>

#include <iostream>

#include "reservation.hpp"

using namespace std;

class book
{
private:
    /* data */
public:
    int BookId;
    string BookName;
    string AuthorName;
    bool AvailabilityStatus;
    int BorrowedBy;

    priority_queue<reservation, vector<reservation>, Compare> ReservationHeap;

    void AddReservation(reservation newReservation);
    void DeleteReservation(int patronID);
    void PrintBook();
    
    book(int id, string name, string author);
};
