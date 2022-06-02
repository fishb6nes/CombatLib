#include "Event.h"

using namespace Combat::Event;

void Bus::AddHandler(const Handler &handler)
{
    handlers.push_back(&handler);
}

void Bus::RemoveHandler(const Handler &handler)
{
    auto predicate = [handler](auto it) { return it == &handler; };
    auto index = std::find_if(handlers.begin(), handlers.end(), predicate);
    handlers.erase(index);
}

template<class T> T Bus::PublishEvent(T &event)
{
    for (auto &handler : handlers)
    {
        event = handler->ApplyEvent(event);
    }
    return event;
}
