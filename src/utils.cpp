#include "utils.hpp"

//////////////
// Includes //
#include <cstdlib>

//////////
// Code //

// Creates a pseudo-random float from 0 to 1.
float randomFloat() { return rand() / static_cast<float>(RAND_MAX); }

// Creates a pseudo-random float from min to max.
float randomFloat(float min, float max) {
    if (max < min)
        return 0.f;
    else if (max == min)
        return min;
    return randomFloat() * (max - min) + min;
}

// Performing a bit of linear interpolation on a value.
float lerp(float f1, float f2, float steps, float dt) {
    return f1 + (f2 - f1) * (dt / steps);
}
