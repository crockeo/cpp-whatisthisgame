#ifndef _DELTA_HPP_
#define _DELTA_HPP_

//////////
// Code //

// Getting the current system time as a float.
unsigned long long currentSystemTime();

// A class to encapsulate modeling the delta time between updates.
class Delta {
private:
    int curr, last;

public:
    // Starting a delta timer.
    Delta();

    // Getting the time since it was last ticked (in seconds).
    float since();

    // Sleeping for a number of milliseconds.
    void sleep(int);
};

#endif
