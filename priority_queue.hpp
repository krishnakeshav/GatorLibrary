
/**
 * @brief A priority queue implementation for reservations.
 * @class pq_reservation
 * This class represents a priority queue that stores reservations. Reservations are
 * stored in a heap data structure, where the highest priority reservation is always
 * at the top. Reservations are ordered based on their priority.
 */
#pragma once

#include <vector>

#include "reservation.hpp"

class pq_reservation {
    private:
        /**
         * @brief Heapify the heap starting from the given index.
         * 
         * This function rearranges the elements in the heap to maintain the heap property.
         * It compares the element at the given index with its children and swaps them if necessary.
         * 
         * @param index The index to start heapifying from.
         */
        void heapify(int index);
        
        std::vector<reservation> heap; /**< The heap storing the reservations. */
    
    public:
        /**
         * @brief Push a new reservation into the priority queue.
         * 
         * This function adds a new reservation to the priority queue and maintains the heap property.
         * 
         * @param newReservation The reservation to be added.
         */
        void push(reservation newReservation);
        
        /**
         * @brief Remove the highest priority reservation from the priority queue.
         * 
         * This function removes the highest priority reservation from the priority queue
         * and maintains the heap property.
         */
        void pop();
        
        /**
         * @brief Get the highest priority reservation from the priority queue.
         * 
         * This function returns the highest priority reservation from the priority queue
         * without removing it.
         * 
         * @return The highest priority reservation.
         */
        reservation top();
        
        /**
         * @brief Check if the priority queue is empty.
         * 
         * This function checks if the priority queue is empty.
         * 
         * @return True if the priority queue is empty, false otherwise.
         */
        bool empty();
        
        /**
         * @brief Get the size of the priority queue.
         * 
         * This function returns the number of reservations in the priority queue.
         * 
         * @return The size of the priority queue.
         */
        int size();
        
        /**
         * @brief Construct a new pq_reservation object.
         * 
         * This is the constructor for the pq_reservation class.
         */
        pq_reservation();
        
        /**
         * @brief Destroy the pq_reservation object.
         * 
         * This is the destructor for the pq_reservation class.
         */
        ~pq_reservation();
};