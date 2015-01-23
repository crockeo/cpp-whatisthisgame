#ifndef _OBSERVER_HPP_
#define _OBSERVER_HPP_

//////////////
// Includes //
#include <memory>
#include <string>
#include <map>
#include <set>

//////////
// Code //

// The actual Event class.
struct Event {
    enum EventType {
        GENERIC_EVENT
    };

    // Getting the type of the event.
    virtual Event::EventType getType() const { return GENERIC_EVENT; }
};

// Ordering EventTypes.
bool operator<(const Event::EventType, const Event::EventType);

// An abstract class to represent a class that'll listen for events.
struct Listener {
    // An action to perform when a given listener is tasked with an event.
    virtual void alert(Event) = 0;

    // Attatching this listener to an OM.
    void attach(Event::EventType);
};

// Managing different actions and listeners.
class OM {
private:
    static std::unique_ptr<OM> _om;

    std::map<Event::EventType, std::set<std::shared_ptr<Listener>>> listeners;

    // Constructing a new OM.
    OM();

public:
    // Getting the instance for the OM.
    static OM& instance();

    // Adding a new listener to the class.
    void addListener(Event::EventType, std::shared_ptr<Listener>);
    void addListener(Event::EventType, Listener*);

    // Alerting every Listener in this OM.
    void alert(Event) const;
};

#endif
