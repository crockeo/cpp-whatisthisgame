#ifndef _DELTA_HPP_
#define _DELTA_HPP_

//////////
// Code //

// A class to encapsulate modeling the delta time between updates.
class Delta {
private:
    int curr, last;

public:
    // Starting a delta timer.
    Delta();

    // Getting the time since it was last ticked (in seconds).
    float since();
};

#endif
