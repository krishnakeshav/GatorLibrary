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

class gl_input
{
    private:
        GatorLibrary library;
        // Function to parse and store parameters for InsertBook
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

        // Function to parse and store parameters for PrintBook
        void parse_print(const std::string& input) {
            int bookID;
            std::istringstream iss(input);
            char discard;  // To discard '('

            // Skip the macro name "PrintBook" and the opening parenthesis
            iss.ignore(PB.length());

            iss >> bookID >> discard;  // Discard '(' and read bookID

            library.PrintBook(bookID);
            cout << endl;
        }

        // Function to parse and store parameters for BorrowBook
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

        // Function to parse and store parameters for PrintBooks
        void parse_prints(const std::string& input) {
            int bookID1, bookID2;
            std::istringstream iss(input);
            char discard;  // To discard '('

            // Skip the macro name "PrintBooks" and the opening parenthesis
            iss.ignore(PBS.length());
            iss >> bookID1 >> discard >> bookID2 >> discard;  // Discard '(' and read bookID1 and bookID2

            library.PrintBooks(bookID1, bookID2);
        }

        // Function to parse and store parameters for ReturnBook
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

        void parse_colorflip(const std::string& input) {
            library.ColorFlipCount();
        }

        void parse_findclosest(const std::string& input) {
            int targetId;
            std::istringstream iss(input);
            char discard;  // To discard '('

            // Skip the macro name "FindClosestBook" and the opening parenthesis
            iss.ignore(FCB.length());

            iss >> targetId >> discard;  // Discard '(' and read targetId
            library.FindClosestBook(targetId);
        }

        // Function to parse Quit command
        void parse_quit(const std::string& command) {
            cout << "Program Terminated!!" << endl;
        }

        void parse_input(const string& input)
        {
            //InsertBook(bookID, title, author, availability) 
            //PrintBook(bookID) 
            //PrintBooks(bookID1, bookID2) 
            //BorrowBook(patronID, bookID, patronPriority) 
            // ReturnBook(patronID, bookID) 
            //Quit()

            //istringstream iss(input);
            //string op;
            //iss >> op;
            //cout << "Operation: " << op << " command: " << input << endl;

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
            }
            else
            {
                cout << "Invalid command" << endl;
            }
        }
    public:
        gl_input()
        {
            library = GatorLibrary();
        }
        void runwith_file(string filename)
        {
            ifstream file(filename);
            string line;
            while (getline(file, line))
            {
                parse_input(line);
            }
        }
        void run(string input)
        {
            parse_input(input);
        }
};