#include "EventBus.h"

using namespace Combat;

template<class Event>
void EventBus::AddHandler(EventHandler<Event> &handler)
{
    auto it = static_cast<void *>(handler);
    handlers[typeid(Event)].push_back(it);
}

template<class Event>
void EventBus::AddPreHandler(PreEventHandler<Event> &handler)
{
    auto it = static_cast<void *>(handler);
    preHandlers[typeid(Event)].push_back(it);
}

template<class Event>
void EventBus::RemoveHandler(EventHandler<Event> &handler)
{
    auto from = handlers[typeid(Event)];
    auto predicate = [handler](auto it) { return it == handler; };
    auto index = std::find_if(from.begin(), from.end(), predicate);
    from.erase(index);
}

template<class Event>
void EventBus::RemovePreHandler(PreEventHandler<Event> &handler)
{
    auto from = preHandlers[typeid(Event)];
    auto predicate = [handler](auto it) { return it == handler; };
    auto index = std::find_if(from.begin(), from.end(), predicate);
    from.erase(index);
}

template<class Event>
void EventBus::PublishEvent(const Event &event)
{
    static_assert(std::is_base_of<Event, Event>::value,
                  "Published event must derive from Event");

    for (void *handler : handlers[typeid(Event)])
    {
        auto it = static_cast<EventHandler<Event> *>(handler);
        it->ApplyEvent(event);
    }
}

template<class Event>
void EventBus::PublishPreEvent(Event &event)
{
    static_assert(std::is_base_of<PreEvent, Event>::value,
                  "Published event must derive from PreEvent");

    for (void *handler : preHandlers[typeid(Event)])
    {
        auto it = static_cast<PreEventHandler<Event> *>(handler);
        it->ApplyPreEvent(event);
    }
}
