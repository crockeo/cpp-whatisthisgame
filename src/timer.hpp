#ifndef _TIMER_HPP_
#define _TIMER_HPP_

//////////
// Code //

// A class to represent a timer.
class Timer {
private:
    float maxTime, time;

public:
    // Constructing a timer with a given maximum time, after which it will loop.
    Timer(float);

    // Constructing a timer without a maximum time.
    Timer();

    // Resetting the timer.
    void reset();

    // Updating this timer with a delta time.
    void update(float dt);

    // Getting the maximum time.
    float getMaxTime() const;

    // Getting the current time.
    float getTime() const;
    
    // Checking if this thing will loop.
    bool willLoop() const;
};

#endif
