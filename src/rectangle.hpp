#ifndef _RECTANGLE_HPP_
#define _RECTANGLE_HPP_

//////////
// Code //

// A struct to represent a Rectangle.
struct Rectangle {
    float x, y, w, h;

    // Constructing a new rectangle.
    Rectangle(float, float, float, float);

    // Getting different sides of the rectangle.
    float left()   const;
    float right()  const;
    float top()    const;
    float bottom() const;

    // Checking if a rectangle collides with another one.
    bool collides(Rectangle) const;
};

#endif
