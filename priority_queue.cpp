
/**
 * @file priority_queue.cpp
 * @brief Implementation of the pq_reservation class, which represents a priority queue for reservations.
 */
#include "priority_queue.hpp"

void pq_reservation::heapify(int index)
{
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int smallest = index;

    if (left < heap.size() && heap[left].PriorityNumber <= heap[index].PriorityNumber)
    {
        if (heap[left].PriorityNumber == heap[index].PriorityNumber)
        {
            if (heap[left].TimeOfReservation < heap[index].TimeOfReservation)
            {
                smallest = left;
            }
        }
        else
        {
            smallest = left;
        }
    
    }

    if (right < heap.size() && heap[right].PriorityNumber < heap[smallest].PriorityNumber)
    {
        if (heap[right].PriorityNumber == heap[smallest].PriorityNumber)
        {
            if (heap[right].TimeOfReservation < heap[smallest].TimeOfReservation)
            {
                smallest = right;
            }
        }
        else
        {
            smallest = right;
        }
    }

    if (smallest != index)
    {
        swap(heap[index], heap[smallest]);
        heapify(smallest);
    }
}

void pq_reservation::push(reservation newReservation)
{
    heap.push_back(newReservation);
    int index = heap.size() - 1;
    int parent = (index - 1) / 2;

    while (index > 0 && heap[parent].PriorityNumber > heap[index].PriorityNumber)
    {
        if (heap[parent].PriorityNumber == heap[index].PriorityNumber)
        {
            if (heap[parent].TimeOfReservation > heap[index].TimeOfReservation)
            {
                swap(heap[parent], heap[index]);
                index = parent;
                parent = (index - 1) / 2;
            }
            else
            {
                break;
            }
        }
        else
        {
            swap(heap[parent], heap[index]);
            index = parent;
            parent = (index - 1) / 2;
        }
    }
}

void pq_reservation::pop()
{
    if (heap.size() == 0)
    {
        return;
    }
    else if (heap.size() == 1)
    {
        heap.pop_back();
        return;
    }
    else
    {
        heap[0] = heap[heap.size() - 1];
        heap.pop_back();
        heapify(0);
    }
}

reservation pq_reservation::top()
{
    return heap[0];
}

bool pq_reservation::empty()
{
    return heap.size() == 0;
}

int pq_reservation::size()
{
    return heap.size();
}

pq_reservation::pq_reservation()
{
   heap = {};
}

pq_reservation::~pq_reservation()
{
}