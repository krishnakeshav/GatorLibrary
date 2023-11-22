/**
    @file: book.cpp
    @brief: This file contains the implementation of the book class.
    @details:
    BookId: Unique identifier for the book.
    BookName: Name of the book.
    AuthorName: Name of the author.
    AvailabilityStatus: Availability status of the book.
    BorrowedBy: PatronId of the patron who borrowed the book.
    ReservationHeap: Priority queue of reservations for the book.

*/
#include "book.hpp"

using namespace std;


book::book(int id, string name, string author, BookAvailability available)
{
    BookId = id;
    BookName = name;
    AuthorName = author;
    AvailabilityStatus = available;
    BorrowedBy = -1;
    ReservationHeap = pq_reservation();
}

book::book(int id, string name, string author, string availabilityStatus)
        : book(id, name, author, utilities::status_toenum(availabilityStatus))
{
}

book::~book()
{
}

void book::PrintBook()
{
    cout << "BookID = " << BookId << endl;
    cout << "Title = " << BookName << endl;
    cout << "Author = " << AuthorName << endl;
    cout << "Availability = " << utilities::status_tostring(AvailabilityStatus) << endl;
    string bby = BorrowedBy == -1 ? "None" : to_string(BorrowedBy);
    cout << "Borrowed By =  " << bby << endl;
    printReservations();
}

void book::printReservations()
{
    pq_reservation temp = ReservationHeap;

    cout << "Reservations = [";
    
    while (!temp.empty())
    {
        reservation top = temp.top();
        cout << top.PatronId;
        temp.pop();
        if (!temp.empty()) {
            std::cout << ", ";
        }
    }
    cout << "]" << endl;
}

/// @details Add the reservation to the reservation heap.
/// Reservation heap is a min heap based on priority number and time of reservation.
void book::AddReservation(reservation newReservation)
{
    ReservationHeap.push(newReservation);
    cout << "Book " << BookId << " reserved by Patron " << newReservation.PatronId << endl;
    //cout << endl;
}
