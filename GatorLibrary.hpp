#include <string>
#include <set>
#include <unordered_map>

#include "book.hpp"
#include "RedBlackTree.hpp"

using namespace std;

class GatorLibrary
{
private:
    unordered_map<int, book> mBooks;
    rbtree rbtBooks;

public:
    void PrintBook(int bookID);
    void PrintBooks(int bookID1, int bookID2);
    void InsertBook(int bookID, string bookName, string authorName, bool availabilityStatus, int borrowedBy);
    void BorrowBook(int patronID, int bookID, int patronPriority);
    void ReturnBook(int patronID, int bookID);
    void DeleteBook(int bookID);
};
