#include <iostream>
#include <vector>

using namespace std;


const int WINDOW_SIZE = 400;  // Working Set Window (arbitrary threshold for replacement)

// Structure for each page frame node in the WSClock
class PageFrameNode {

public:

    int lastUseTime;
    int referenceBit;

    PageFrameNode(int time, int refBit) : lastUseTime(time), referenceBit(refBit) {}

};


// Display the current state of the working set with a pointer or an index
void displayWSClock(vector<PageFrameNode> clock, int vTime, int pointer) {
    
    cout << "Virtual Time: " << vTime << endl;
    cout << "Working Set Clock: ";
    int n = clock.size();
    for (int i = 0; i < n; i++)
    {
        if (i == pointer)
        {
            cout << "[" << clock[i].lastUseTime << ":" << clock[i].referenceBit << "] ";
        }
        else cout << clock[i].lastUseTime << ":" << clock[i].referenceBit << " ";
    }
    cout << endl;
}


// WSClock Page Replacement Algorithm
void wsClockPageReplacement(vector<PageFrameNode> clock, int vTime) {

    int pointer = 3; // Initial pointer to node with last use time 2014
    int end = pointer;
    while (true) {

        if (clock[pointer].referenceBit == 1) // If reference bit is 1, set it to 0 and move to the next node
        {
            displayWSClock(clock, vTime, pointer);
            cout << endl;
            clock[pointer].referenceBit = 0;
        }
        else if (clock[pointer].referenceBit == 0 && vTime - clock[pointer].lastUseTime > WINDOW_SIZE) // If reference bit is 0 and last use time is outside window, replace page
        {
            displayWSClock(clock, vTime, pointer);
            cout << "Replacing page at index " << pointer << endl << endl;
            clock[pointer].referenceBit = 1;
            clock[pointer].lastUseTime = vTime;
            vTime++;
        }
        else
        {
            displayWSClock(clock, vTime, pointer);
            cout << endl;
        }

        pointer++; // Move the pointer to the next node in the circular list
        pointer = pointer % clock.size();
        if (pointer == end)
        {
            cout << "Done!" << endl;
            break; // Stop if we have cycled back to the original starting point
        }
    }
}

int main() {

    // Initialize the WSClock with given values (time of last use: reference R bit)
    vector<PageFrameNode> clock = { {1620, 0}, {2032, 1}, {2020, 1}, {2014, 1}, {1213, 0}, {1980, 1}, {2003, 1}, {2084, 1} };

    int virtualTime = 2204; // Starting virtual time
    wsClockPageReplacement(clock, virtualTime);
    return 0;
}