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

// EventType being just a string.
using EventType = std::string;

// The actual Event class.
struct Event {
    // Getting the type of the event.
    virtual EventType getType() const { return ""; }
};

// An abstract class to represent a class that'll listen for events.
struct Listener {
    // An action to perform when a given listener is tasked with an event.
    virtual void alert(Event) = 0;

    // Attatching this listener to an OM.
    void attach(EventType);
};

// Managing different actions and listeners.
class OM {
private:
    static std::unique_ptr<OM> _om;

    std::map<EventType, std::set<std::shared_ptr<Listener>>> listeners;

    // Constructing a new OM.
    OM();

public:
    // Getting the instance for the OM.
    static OM& instance();

    // Adding a new listener to the class.
    void addListener(EventType, std::shared_ptr<Listener>);
    void addListener(EventType, Listener*);

    // Alerting every Listener in this OM.
    void alert(Event) const;
};

#endif
