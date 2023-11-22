/*
    @file: gator_library.cpp
    @class: GatorLibrary
    @brief: Implementation of the GatorLibrary class
    @details: This file contains the implementation of the GatorLibrary class.
    The GatorLibrary class represents a library system.
    This class provides functionality to manage books in the library,
    including inserting, borrowing, returning, and deleting books.
    It also provides functions to print book information, count color flips in the red-black tree,
    and find the closest book to a given book ID.
*/

#include "gator_library.hpp"

using namespace std;

/// @brief Display the book details
/// @param bookID Integer.
void GatorLibrary::PrintBook(int bookID)
{
    rbtnode* bookToPrint = rbtBooks.find(bookID);
    if (bookToPrint == nullptr)
    {
        return;
    }
    bookToPrint->value.PrintBook();
    cout << endl;
}

/// @brief Display the book details for all books in the range
/// @param bookID1
/// @param bookID2
void GatorLibrary::PrintBooks(int bookID1, int bookID2)
{
    for (size_t bookId = bookID1; bookId <= bookID2; bookId++)
    {
        PrintBook(bookId);
    }
}

/// @brief Find the book Id closest to the targetId
/// @param targetId Integer.
void GatorLibrary::FindClosestBook(int targetId)
{
    vector<int> closestBooks = rbtBooks.findclosest(targetId);
    for (size_t i = 0; i < closestBooks.size(); i++)
    {
        PrintBook(closestBooks[i]);
        cout << endl;
    }
}

/// @brief Insert a new book into the library
/// @param bookID String.
/// @param bookName String.
/// @param authorName String.
/// @param availabilityStatus String.
void GatorLibrary::InsertBook(int bookID, string bookName, string authorName, string availabilityStatus)
{
    book newBook(bookID, bookName, authorName, availabilityStatus);
    rbtBooks.add(newBook);
}

/// @brief Borrow a book from the library
/// @param patronID Integer.
/// @param bookID Integer.
/// @param patronPriority Integer.
/// @return True if the book is borrowed, false otherwise.
/// @details If the book is not available, add the reservation to the book's reservation heap.
///          Reservation heap is a priority queue of reservations.
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

/// @brief Return a book to the library
/// @param patronID Integer.
/// @param bookID Integer.
/// @details If the book is reserved, the book is borrowed by the next patron in the reservation heap.
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
                cout << "Book " << bookID << " Allotted to Patron " << patronID << endl;
            }
        }
    }
    else
    {
        cout << "BookID " << bookID << " is not borrowed" << endl;
    }
}

/// @brief Delete a book from the library
/// @param bookID Integer.
/// @details If the book is borrowed, the reservation is cancelled for all the patrons.
void GatorLibrary::DeleteBook(int bookID)
{
    rbtnode* bookToDelete = rbtBooks.find(bookID);
    if (bookToDelete == nullptr)
    {
        cout << "Book " << bookID << " not found in library" << endl;
        return;
    }
    
    pq_reservation patrons = bookToDelete->value.ReservationHeap;
    vector<int> patronsToCancel;

    bool occupied = bookToDelete->value.AvailabilityStatus == NO;
    int currentBorrower = bookToDelete->value.BorrowedBy;

    rbtBooks.remove(bookID);
    
    cout << "Book " << bookID << " is no longer available.";

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
        cout << " have been cancelled!";
    }
    cout << endl;
}

/// @brief Display the number of color flips in the red black tree
/// @details Color flip count is the number of times the color of a node is flipped from red to black or vice versa.
void GatorLibrary::ColorFlipCount()
{
    cout << "Color Flip Count: " << rbtBooks.ColorFlipCount() << endl;
}