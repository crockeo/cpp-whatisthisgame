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

// Constructing this thing.
EnemyWinEvent::EnemyWinEvent() { }

// Getting the event type.
Event::EventType EnemyWinEvent::getType() const {
    return ENEMY_WIN_EVENT;
}

// Creating a new EnemyShotEvent.
EnemyShotEvent::EnemyShotEvent(float x, float y, float size, void* ptr) {
    this->x = x;
    this->y = y;
    this->size = size;
    this->ptr = ptr;
}

// Getting the type of this event.
Event::EventType EnemyShotEvent::getType() const {
    return ENEMY_SHOT_EVENT;
}
