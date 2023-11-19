#include "gator_library.hpp"

using namespace std;

void GatorLibrary::PrintBook(int bookID)
{
    rbtnode* bookToPrint = rbtBooks.find(bookID);
    if (bookToPrint == nullptr)
    {
        //cout << "BookID " << bookID << " not found in library" << endl;
        return;
    }
    bookToPrint->value.PrintBook();
    cout << endl;
}

void GatorLibrary::PrintBooks(int bookID1, int bookID2)
{
    for (size_t bookId = bookID1; bookId <= bookID2; bookId++)
    {
        PrintBook(bookId);
    }
}

void GatorLibrary::FindClosestBook(int targetId)
{
    vector<int> closestBooks = rbtBooks.findclosest(targetId);
    //cout << "Closes book(s) to " << targetId << " is/are = [";
    for (size_t i = 0; i < closestBooks.size(); i++)
    {
        PrintBook(closestBooks[i]);
        cout << endl;
    }
}

void GatorLibrary::InsertBook(int bookID, string bookName, string authorName, string availabilityStatus)
{
    book newBook(bookID, bookName, authorName, availabilityStatus);
    rbtBooks.add(newBook);
}

bool GatorLibrary::BorrowBook(int patronID, int bookID, int patronPriority)
{
    bool ret = true;
    rbtnode* bookToBorrow = rbtBooks.find(bookID);
    if (bookToBorrow == nullptr)
    {
        //cout << "Book " << bookID << " not found in library" << endl;
        ret = false;
    }
    else if (bookToBorrow->value.BorrowedBy == patronID)
    {
        //cout << "Book " << bookID << " reserved by Patron " << patronID << endl;
        ret = false;
    }
    else if (bookToBorrow->value.AvailabilityStatus == YES)
    {
        bookToBorrow->value.AvailabilityStatus = NO;
        bookToBorrow->value.BorrowedBy = patronID;
        //cout << "Book " << bookID << " Borrowed by Patron " << patronID << endl;
    }
    else
    {
        reservation newReservation(patronID, patronPriority);
        bookToBorrow->value.AddReservation(newReservation);
        ret = false;
    }
    //cout << endl;
    return ret;
}

void GatorLibrary::ReturnBook(int patronID, int bookID)
{
    rbtnode* bookToReturn = rbtBooks.find(bookID);
    if (bookToReturn == nullptr)
    {
        cout << "Book " << bookID << " not found in library" << endl;
        return;
    }
    if (bookToReturn->value.AvailabilityStatus == NO)
    {
        bookToReturn->value.AvailabilityStatus = YES;
        bookToReturn->value.BorrowedBy = -1;
        cout << "Book " << bookID << " Returned by Patron " << patronID << endl;
        if (!bookToReturn->value.ReservationHeap.empty())
        {
            reservation nextReservation = bookToReturn->value.ReservationHeap.top();
            bookToReturn->value.ReservationHeap.pop();
            if (BorrowBook(nextReservation.PatronId, bookID, nextReservation.PriorityNumber))
            {
                cout << "Book " << bookID << " Alloted by Patron " << patronID << endl;
            }
        }
    }
    else
    {
        cout << "BookID " << bookID << " is not borrowed" << endl;
    }
}

void GatorLibrary::DeleteBook(int bookID)
{
    rbtnode* bookToDelete = rbtBooks.find(bookID);
    if (bookToDelete == nullptr)
    {
        cout << "Book " << bookID << " not found in library" << endl;
        return;
    }
    
    priority_queue<reservation, vector<reservation>, Compare> patrons = bookToDelete->value.ReservationHeap;
    vector<int> patronsToCancel;

    bool occupied = bookToDelete->value.AvailabilityStatus == NO;
    int currentBorrower = bookToDelete->value.BorrowedBy;

    rbtBooks.remove(bookID);
    
    cout << "Book " << bookID << " is no longer available.";
    if (occupied)
    {
        //cout << " Reservation made by Patron " << currentBorrower << " is cancelled!";
        patronsToCancel.push_back(currentBorrower);
    }
    while (!patrons.empty())
    {
        reservation nextReservation = patrons.top();
        patrons.pop();
        patronsToCancel.push_back(nextReservation.PatronId);
    }
    if (patronsToCancel.size() > 0)
    {
        cout << " Reservations made by Patrons ";
        for (size_t i = 0; i < patronsToCancel.size(); i++)
        {
            cout << patronsToCancel[i];
            if (i != patronsToCancel.size() - 1)
            {
                cout << ", ";
            }
        }
        cout << " have been cancelled!" << endl;
    }
}

void GatorLibrary::ColorFlipCount()
{
    cout << "Color Flip Count: " << rbtBooks.ColorFlipCount() << endl;
}