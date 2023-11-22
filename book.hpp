#pragma once

#include <string>
#include <queue>

#include <iostream>

#include "reservation.hpp"
#include "utilities.hpp"
#include "priority_queue.hpp"

using namespace std;

/**
 * @file book.hpp
 * @class book
 * @brief Represents a book in the library.
 * 
 * This class provides functionality to manage reservations, borrowings, and information about a book.
 * It contains member variables to store the book's ID, name, author, availability status, and borrower.
 * The class also includes a priority queue for managing reservations.
 * @see reservation pq_reservation
 */
class book {
private:
    /**
     * @brief Prints the reservations for the book.
     */
    void printReservations();

public:
    int BookId; /**< The ID of the book. */
    string BookName; /**< The name of the book. */
    string AuthorName; /**< The name of the author of the book. */
    BookAvailability AvailabilityStatus; /**< The availability status of the book. */
    int BorrowedBy; /**< The ID of the patron who borrowed the book. */

    pq_reservation ReservationHeap; /**< The priority queue for managing reservations. */

    /**
     * @brief Adds a new reservation for the book.
     * @param newReservation The reservation to be added.
     * @see reservation
     */
    void AddReservation(reservation newReservation);

    /**
     * @brief Deletes a reservation for the book.
     * @param patronID The ID of the patron whose reservation needs to be deleted.
     */
    void DeleteReservation(int patronID);

    /**
     * @brief Prints the details of the book.
     */
    void PrintBook();

    /**
     * @brief Constructs a book object with the given parameters.
     * @param id The ID of the book.
     * @param name The name of the book.
     * @param author The name of the author of the book.
     * @param availabilityStatus The availability status of the book as a string.
     */
    book(int id, string name, string author, string availabilityStatus);

    /**
     * @brief Constructs a book object with the given parameters.
     * @param id The ID of the book.
     * @param name The name of the book.
     * @param author The name of the author of the book.
     * @param available The availability status of the book as an enum value.
     */
    book(int id, string name, string author, BookAvailability available);

    /**
     * @brief Destructs the book object.
     */
    ~book();
};
