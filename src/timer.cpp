#include "timer.hpp"

//////////
// Code //

// Constructing a timer with a given maximum time, after which it will loop.
Timer::Timer(float maxTime) {
    this->maxTime = maxTime;
    this->time = 0;
}

// Constructing a timer without a maximum time.
Timer::Timer() {
    this->maxTime = -1;
    this->time = 0;
}

// Resetting the timer.
void Timer::reset() {
    this->time = 0;
}

// Updating this timer with a delta time.
void Timer::update(float dt) {
    this->time += dt;
    if (this->maxTime > 0)
        while (this->time >= this->maxTime)
            this->time -= this->maxTime;
}

// Getting the maximum time.
float Timer::getMaxTime() const { return this->maxTime; }

// Getting the current time.
float Timer::getTime() const { return this->time; }

// Checking if this thing will loop.
bool Timer::willLoop() const { return this->maxTime < 0; }
