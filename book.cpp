#include "book.hpp"

using namespace std;

book::book(int id, string name, string author, BookAvailability available)
{
    BookId = id;
    BookName = name;
    AuthorName = author;
    AvailabilityStatus = available;
    BorrowedBy = -1;
    ReservationHeap = priority_queue<reservation, vector<reservation>, Compare>();
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
    cout << "Borrowed By: " << BorrowedBy << endl;
    printReservations();
}

void book::printReservations()
{
    priority_queue<reservation, vector<reservation>, Compare> temp = ReservationHeap;
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

void book::AddReservation(reservation newReservation)
{
    ReservationHeap.push(newReservation);
    cout << "Book " << BookId << " reserved by Patron " << newReservation.PatronId << endl;
    //cout << endl;
}
