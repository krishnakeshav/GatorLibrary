
/**
 * @brief The GatorLibrary class represents a library system.
 * @class GatorLibrary
 * This class provides functionality to manage books in the library,
 * including inserting, borrowing, returning, and deleting books.
 * It also provides functions to print book information, count color flips in the red-black tree,
 * and find the closest book to a given book ID.
 */
#pragma once

#include <string>
#include <set>
#include <unordered_map>

#include "book.hpp"
#include "redblack_tree.hpp"

using namespace std;

class GatorLibrary
{
private:
    rbtree rbtBooks;

public:

    // print functions
    void PrintBook(int bookID);
    void PrintBooks(int bookID1, int bookID2);

    // operations
    void InsertBook(int bookID, string bookName, string authorName, string availabilityStatus);
    bool BorrowBook(int patronID, int bookID, int patronPriority);
    void ReturnBook(int patronID, int bookID);
    void DeleteBook(int bookID);

    // info functions
    void ColorFlipCount();
    void FindClosestBook(int targetId);
};
