#include "events.hpp"

//////////
// Code //

// Constructing a new BulletShotEvent.
BulletShootEvent::BulletShootEvent(float x, float y, float dy) {
    this->x = x;
    this->y = y;
    this->dy = dy;
}

// Getting the type of this event.
Event::EventType BulletShootEvent::getType() const {
    return BULLET_SHOOT_EVENT;
}
