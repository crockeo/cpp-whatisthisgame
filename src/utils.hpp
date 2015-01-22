#ifndef _UTILS_HPP_
#define _UTILS_HPP_

//////////
// Code //

// Creates a pseudo-random float from 0 to 1.
float randomFloat();

// Creates a pseudo-random float from min to max.
float randomFloat(float, float);

// Performing a bit of linear interpolation on a value.
float lerp(float, float, float, float);

#endif
