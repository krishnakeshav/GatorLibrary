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
    cout << "Book ID: " << BookId << endl;
    cout << "Book Name: " << BookName << endl;
    cout << "Author Name: " << AuthorName << endl;
    cout << "Availability Status: " << utilities::status_tostring(AvailabilityStatus) << endl;
    cout << "Borrowed By: " << BorrowedBy << endl;
}

void book::AddReservation(reservation newReservation)
{
    ReservationHeap.push(newReservation);
}
