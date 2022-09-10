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

        template<class PreEvent>
        void AddPreHandler(PreEventHandler<PreEvent> &handler);

        template<class Event>
        void RemoveHandler(EventHandler<Event> &handler);

        template<class PreEvent>
        void RemovePreHandler(PreEventHandler<PreEvent> &handler);

        template<class Event>
        void PublishEvent(const Event &event);

        template<class PreEvent>
        void PublishPreEvent(PreEvent &event);
    };
}
