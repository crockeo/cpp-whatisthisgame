#include "delta.hpp"

//////////////
// Includes //
#include <chrono>

//////////
// Code //

// Getting the current system time as a float.
int currentSystemTime() {
    auto now = std::chrono::system_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
}

// Starting a delta timer.
Delta::Delta() {
    this->curr = 0;
    this->last = 0;
}

// Getting the time since it was last ticked (in seconds).
float Delta::since() {
    this->curr = currentSystemTime();

    float dt = (curr - last) / 1000.f;
    if (this->last == 0)
        dt = 0;

    this->last = curr;

    return dt;
}
