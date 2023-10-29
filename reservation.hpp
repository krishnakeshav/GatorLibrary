#include <string>
#include <queue>

using namespace std;

// reservation stores the priority number, patron id and the time of reservation
class reservation
{
private:
    /* data */
public:
    int PatronId;
    int PriorityNumber;
    string TimeOfReservation;
    reservation(int patronId, int priorityNumber, string timeOfReservation);
};

class Compare
{
private:
    /* data */
public:
    bool operator () (reservation a, reservation b)
    {
        if (a.PriorityNumber > b.PriorityNumber)
        {
            return true;
        }
        else if (a.PriorityNumber == b.PriorityNumber)
        {
            if (a.TimeOfReservation > b.TimeOfReservation)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
};
