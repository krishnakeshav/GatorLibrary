#include "book.hpp"

using namespace std;

book::book(int id, string name, string author)
{
    BookId = id;
    BookName = name;
    AuthorName = author;
    AvailabilityStatus = true;
    ReservationHeap = priority_queue<reservation, vector<reservation>, Compare>();
}

void book::PrintBook()
{
    cout << "Book ID: " << BookId << endl;
    cout << "Book Name: " << BookName << endl;
    cout << "Author Name: " << AuthorName << endl;
    cout << "Availability Status: " << AvailabilityStatus << endl;
    cout << "Borrower By: " << BorrowedBy << endl;
}

void book::AddReservation(reservation newReservation)
{
    ReservationHeap.push(newReservation);
}
