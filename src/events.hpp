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

    // Getting the type of this event.
    Event::EventType getType() const;
};

// An event to represent an enemy getting behind our lines and winning!
struct EnemyWinEvent : public Event {
    // Constructing this thing.
    EnemyWinEvent();

    // Getting the event type.
    Event::EventType getType() const;
};

// An event to represent an entity being shot.
struct EnemyShotEvent : public Event {
    float x, y;
    void* ptr;

    // Creating a new EnemyShotEvent.
    EnemyShotEvent(float, float, void*);

    // Getting the type of this event.
    Event::EventType getType() const;
};

#endif
