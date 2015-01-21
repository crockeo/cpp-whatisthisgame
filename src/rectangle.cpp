#include "rectangle.hpp"

//////////
// Code //

// Constructing a new rectangle.
Rectangle::Rectangle(float x, float y, float w, float h) {
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

// Getting different sides of the rectangle.
float Rectangle::left()   const { return this->x; }
float Rectangle::right()  const { return this->x + this->w; }
float Rectangle::top()    const { return this->y; }
float Rectangle::bottom() const { return this->y + this->h; }

// Checking if a rectangle collides with another one.
bool Rectangle::collides(Rectangle rect) const {
    Rectangle sw = this->w <= rect.w ? *this : rect;
    Rectangle bw = this->w >  rect.w ? *this : rect;

    Rectangle sh = this->h <= rect.h ? *this : rect;
    Rectangle bh = this->h >  rect.h ? *this : rect;

    bool cLeft   = sw.left()   < bw.right()  && sw.left()   > bw.left();
    bool cRight  = sw.right()  > bw.left()   && sw.right()  < bw.right();

    bool cTop    = sh.top()    < bh.bottom() && sh.top()    > bh.top();
    bool cBottom = sh.bottom() > bh.top()    && sh.bottom() < bh.bottom();

    return (cLeft || cRight) && (cTop || cBottom);
}
