#pragma once

#include <algorithm>
#include <map>
#include <typeindex>
#include <vector>

#include "Event.h"

namespace Combat
{
    class EventBus
    {
    private:
        std::map<std::type_index, std::vector<void *>> handlers;
        std::map<std::type_index, std::vector<void *>> preHandlers;

    public:
        template<class Event>
        void AddHandler(EventHandler<Event> &handler);

        template<class Event>
        void AddPreHandler(PreEventHandler<Event> &handler);

        template<class Event>
        void RemoveHandler(EventHandler<Event> &handler);

        template<class Event>
        void RemovePreHandler(PreEventHandler<Event> &handler);

        template<class Event>
        void PublishEvent(const Event &event);

        template<class Event>
        void PublishPreEvent(Event &event);
    };
}
