#ifndef _EVENTS_HPP_
#define _EVENTS_HPP_

//////////////
// Includes //
#include "observer.hpp"

//////////
// Code //

// An event to represent a bullet shot.
struct BulletShootEvent : public Event {
    float x, y, dy;

    // Constructing a new BulletShotEvent.
    BulletShootEvent(float, float, float);

    // Copy constructor.
    BulletShootEvent(const BulletShootEvent&);

    // Getting the type of this event.
    Event::EventType getType() const;
};

// An event to represent an enemy getting behind our lines and winning!
struct EnemyWinEvent : public Event { };

// An event to represent an entity being shot.
struct EnemyShotEvent : public Event { };

#endif
