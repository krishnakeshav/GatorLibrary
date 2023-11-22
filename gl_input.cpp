/*
    @file gl_input.cpp
    @brief Implementation of the gl_input class
    @details This file contains the implementation of the gl_input class.
    The gl_input class represents the input to the library system.
    This class provides functionality to parse the input and call the corresponding function.
*/
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>

#include "gator_library.hpp"


#define INB string("InsertBook(")
#define PB string("PrintBook(")
#define PBS string("PrintBooks(")
#define BB string("BorrowBook(")
#define RB string("ReturnBook(")
#define Q string("Quit(")
#define DB string("DeleteBook(")
#define CFC string("ColorFlipCount(")
#define FCB string("FindClosestBook(")


using namespace std;

/*
    @brief Class to parse the input and call the appropriate functions
    @class gl_input
    This class provides functionality to parse the input and call the appropriate functions.
*/

class gl_input
{
    private:
        GatorLibrary library;

        // @brief Insert a new book into the library
        // @param input String.
        // @return void
        // @details This function inserts a new book into the library.
        // It takes the book ID, book name, author name, and availability status as parameters.
        // It creates a new book object and inserts it into the red-black tree.
        // The double quotes are ignored while reading the book name, author name, and availability status.
        void parse_insert(string input) {
            std::istringstream iss(input);
            
            int bookId;
            string title, author, availability;
            string skip; // to skip the double quotes

            char discard;  // To discard '('
            
            iss.ignore(INB.length());  // Ignore the macro name "InsertBook("
            
            iss >> bookId >> discard;  // Discard '(' and read bookID

            getline(getline(iss, skip, '"'), title, '"');  // Read title until the next '"' and ignore the '"'
            getline(getline(iss, skip, '"'), author, '"');  // Read author until the next '"' and ignore the '"'
            getline(getline(iss, skip, '"'), availability, '"');  // Read availability until the next '"' and ignore the '"'

            library.InsertBook(bookId, title, author, availability);
        }

        // @brief Display the book details
        // @param input String.
        // @return void
        // @details This function displays the details of a book.
        // It takes the book ID as a parameter and prints the details of the book with the given ID.
        void parse_print(const std::string& input) {
            int bookID;
            std::istringstream iss(input);
            char discard;  // To discard '('

            // Skip the macro name "PrintBook" and the opening parenthesis
            iss.ignore(PB.length());

            iss >> bookID >> discard;  // Discard '(' and read bookID

            library.PrintBook(bookID);
        }

        // @brief Borrow a book from the library
        // @param input String.
        // @return void
        // @details This function borrows a book from the library.
        // It takes the patron ID, book ID, and patron priority as parameters.
        void parse_borrow(const std::string& input) {
            int patronID, bookID, patronPriority;
            
            std::istringstream iss(input);
            char discard;  // To discard '('

            // Skip the macro name "BorrowBook" and the opening parenthesis
            iss.ignore(BB.length());

            iss >> patronID >> discard >> bookID >> discard >> patronPriority >> discard;  // Discard '(' and read patronID
            
            if (library.BorrowBook(patronID, bookID, patronPriority))
            {
                cout << "Book " << bookID << " Allocated to Patron " << patronID << endl;
            }
            cout << endl;
        }
        
        // @brief Display the book details for all books in the range
        // @param input String.
        // @return void
        // @details This function displays the details of all books in the range.
        // It takes the book ID range as parameters and prints the details of all books in the range.
        void parse_prints(const std::string& input) {
            int bookID1, bookID2;
            std::istringstream iss(input);
            char discard;  // To discard '('

            // Skip the macro name "PrintBooks" and the opening parenthesis
            iss.ignore(PBS.length());
            iss >> bookID1 >> discard >> bookID2 >> discard;  // Discard '(' and read bookID1 and bookID2

            library.PrintBooks(bookID1, bookID2);
        }

        // @brief Return a book to the library
        // @param input String.
        // @return void
        // @details This function returns a book to the library.
        // It produces the patron ID and book ID as parameters.
        void parse_return(const std::string& input) {
            int patronID, bookID;
            std::istringstream iss(input);
            char discard; // To discard '('

            // Skip the macro name "ReturnBook" and the opening parenthesis
            iss.ignore(RB.length());

            iss >> patronID >> discard >> bookID >> discard; // Discard '(' and read patronID
            library.ReturnBook(patronID, bookID);

            cout << endl;
        }

        // @brief Delete a book from the library
        // @param input String.
        // @return void
        // @details This function deletes a book from the library.
        // It produces the book ID as a parameter and deletes the book with the given ID.
        void parse_delete(const std::string& input) {
            int bookID;
            std::istringstream iss(input);
            char discard;  // To discard '('

            // Skip the macro name "DeleteBook" and the opening parenthesis
            iss.ignore(DB.length());

            iss >> bookID >> discard;  // Discard '(' and read bookID

            library.DeleteBook(bookID);
            cout << endl;
        }

        // @brief Count the number of color flips in the red-black tree
        // @param input String.
        // @return void
        // @details This function counts the number of color flips in the red-black tree.
        void parse_colorflip(const std::string& input) {
            library.ColorFlipCount();
            cout << endl;
        }

        // @brief Find the book Id closest to the targetId
        // @param input String.
        // @return void
        // @details This function finds the book ID closest to the target ID.
        // It takes the target ID as a parameter and prints the details of the book closest to the target ID.
        void parse_findclosest(const std::string& input) {
            int targetId;
            std::istringstream iss(input);
            char discard;  // To discard '('

            // Skip the macro name "FindClosestBook" and the opening parenthesis
            iss.ignore(FCB.length());

            iss >> targetId >> discard;  // Discard '(' and read targetId
            library.FindClosestBook(targetId);
        }
        
        // @brief Terminate the program
        // @param input String.
        // @return void
        // @details This function terminates the program.
        void parse_quit(const std::string& command) {
            cout << "Program Terminated!!" << endl;
        }

        // @brief Parse the input and call the appropriate functions
        // @param input String.
        // @return void
        // @details This function parses the input and calls the corresponding function based on the operation request on the library.
        void parse_input(const string& input)
        {

            if (input.find(INB) != string::npos) {
                parse_insert(input);
            }
            else if (input.find(DB) != string::npos) {
                parse_delete(input);
            }
            else if (input.find(CFC) != string::npos)
            {
                parse_colorflip(input);
            }
            else if (input.find(FCB) != string::npos)
            {
                parse_findclosest(input);
            }
            else if (input.find(PBS) != string::npos)
            {
                parse_prints(input);
            }
            else if (input.find(PB) != string::npos)
            {
                parse_print(input);
            }
            else if (input.find(BB) != string::npos)
            {
                parse_borrow(input);
            }
            else if (input.find(RB) != string::npos)
            {
                parse_return(input);
            }
            else if (input.find(Q) != string::npos)
            {
                parse_quit(input);
                exit(0);
            }
            else
            {
                cout << "Invalid command" << endl;
            }
        }
    public:
        // @brief Constructor for gl_input class
        gl_input()
        {
            library = GatorLibrary();
        }

        // @brief Run the program with the given file
        // @param filename String.
        // @return void
        // @details This function runs the program with the given file.
        // @see runwith_stdin run
        void runwith_file(string filename)
        {
            ifstream file(filename);
            string line;
            while (getline(file, line))
            {
                parse_input(line);
            }
        }

        // @brief Run the program with the given input
        // @param input String.
        // @return void
        // @details This function runs the program with the given input.
        // @see runwith_stdin run_with_file
        void run(string input)
        {
            parse_input(input);
        }

        // @brief Run the program with the standard input
        // @return void
        // @details This function runs the program with the standard input.
        // @see run run_with_file
        void runwith_stdin()
        {
            string input;
            while (getline(cin, input))
            {
                parse_input(input);
            }
        }
};