#pragma once

#include <string>
#include <queue>

#include <iostream>

#include "reservation.hpp"
#include "utilities.hpp"
#include "priority_queue.hpp"

using namespace std;

/*
    @file book.hpp
    @class book
    @brief represents the book and details about the book.
    @details
    BookId: Unique identifier for the book.
    BookName: Name of the book.
    AuthorName: Name of the author.
    AvailabilityStatus: Availability status of the book.
    BorrowedBy: PatronId of the patron who borrowed the book.
    ReservationHeap: Priority queue of reservations for the book.

*/
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

    // priority queue for reservations
    pq_reservation ReservationHeap;

    void AddReservation(reservation newReservation);
    void DeleteReservation(int patronID);
    void PrintBook();
    
    book(int id, string name, string author, string availabilityStatus);
    book(int id, string name, string author, BookAvailability available);

    ~book();
};
