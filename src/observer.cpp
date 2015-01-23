#include "observer.hpp"

//////////
// Code //

// Ordering EventTypes.
bool operator<(const Event::EventType et1, const Event::EventType et2) {
    return static_cast<int>(et1) < static_cast<int>(et2);
}

// Attatching this listener to an OM.
void Listener::attach(Event::EventType et) { OM::instance().addListener(et, this); }

std::unique_ptr<OM> OM::_om(nullptr);

// Constructing a new OM.
OM::OM() { }

// Getting the instance for the OM.
OM& OM::instance() {
    if (OM::_om == nullptr)
        OM::_om = std::unique_ptr<OM>(new OM());
    return *OM::_om;
}

// Adding a new listener to the class.
void OM::addListener(Event::EventType et, std::shared_ptr<Listener> l) {
    if (this->listeners[et].find(l) == this->listeners[et].end())
        this->listeners[et].insert(l);
}

void OM::addListener(Event::EventType et, Listener* l) {
    this->addListener(et, std::shared_ptr<Listener>(l));
}

// Alerting every Listener in this OM.
void OM::alert(Event e) const {
    if (this->listeners.find(e.getType()) != this->listeners.end())
        for (auto& l: this->listeners.at(e.getType()))
            l->alert(e);
}
