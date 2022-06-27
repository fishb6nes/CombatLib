#include <algorithm>

#include "Event.h"

using namespace Combat::Event;

template<class Entity, class Attribute>
void Bus<Entity, Attribute>::AddHandler(const Handler<Entity, Attribute> &handler)
{
    handlers.push_back(&handler);
}

template<class Entity, class Attribute>
void Bus<Entity, Attribute>::RemoveHandler(const Handler<Entity, Attribute> &handler)
{
    auto predicate = [handler](auto it) { return it == &handler; };
    auto index = std::find_if(handlers.begin(), handlers.end(), predicate);
    handlers.erase(index);
}

template<class Entity, class Attribute>
template<class T>
T Bus<Entity, Attribute>::PublishEvent(T &event) const
{
    for (auto &handler : handlers)
    {
        event = handler->ApplyEvent(event);
    }
    return event;
}
