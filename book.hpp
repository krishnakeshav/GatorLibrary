#pragma once

#include <string>
#include <queue>

#include <iostream>

#include "reservation.hpp"
#include "utilities.hpp"

using namespace std;

class book
{

private:
    void printReservations();

public:
    int BookId;
    string BookName;
    string AuthorName;
    BookAvailability AvailabilityStatus;
    int BorrowedBy;

    priority_queue<reservation, vector<reservation>, Compare> ReservationHeap;

    void AddReservation(reservation newReservation);
    void DeleteReservation(int patronID);
    void PrintBook();
    
    book(int id, string name, string author, string availabilityStatus);
    book(int id, string name, string author, BookAvailability available);

    ~book();
};
