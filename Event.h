#pragma once

#include <algorithm>
#include <map>
#include <typeindex>
#include <vector>

namespace Combat
{
    struct Event
    {

    };

    struct PreEvent
    {
        bool cancelled = false;
        bool explicitlyAllowed = false;

        inline bool IsAllowed() const { return !cancelled || explicitlyAllowed; }
    };

    template<class Event>
    struct EventHandler
    {
        virtual void ApplyEvent(const Event &event) { }
    };

    template<class Event>
    struct PreEventHandler
    {
        virtual void ApplyPreEvent(Event &event) { }
    };

    class EventBus
    {
    private:
        std::map<std::type_index, std::vector<void *>> handlers { };
        std::map<std::type_index, std::vector<void *>> preHandlers { };

    public:
        template<class Event>
        void AddHandler(EventHandler<Event> &handler)
        {
            auto it = static_cast<void *>(handler);
            handlers[typeid(Event)].push_back(it);
        }

        template<class Event>
        void AddPreHandler(PreEventHandler<Event> &handler)
        {
            auto it = static_cast<void *>(handler);
            preHandlers[typeid(Event)].push_back(it);
        }

        template<class Event>
        void RemoveHandler(EventHandler<Event> &handler)
        {
            auto from = handlers[typeid(Event)];
            auto predicate = [handler](auto it) { return it == handler; };
            auto index = std::find_if(from.begin(), from.end(), predicate);
            from.erase(index);
        }

        template<class Event>
        void RemovePreHandler(PreEventHandler<Event> &handler)
        {
            auto from = preHandlers[typeid(Event)];
            auto predicate = [handler](auto it) { return it == handler; };
            auto index = std::find_if(from.begin(), from.end(), predicate);
            from.erase(index);
        }

        template<class Event>
        void PublishEvent(const Event &event)
        {
            static_assert(std::is_base_of<Event, Event>::value,
                          "Published event must derive from Ability");

            for (void *handler : handlers[typeid(Event)])
            {
                auto it = static_cast<EventHandler<Event> *>(handler);
                it->ApplyEvent(event);
            }
        }

        template<class Event>
        void PublishPreEvent(Event &event)
        {
            static_assert(std::is_base_of<PreEvent, Event>::value,
                          "Published event must derive from PreEvent");

            for (void *handler : preHandlers[typeid(Event)])
            {
                auto it = static_cast<PreEventHandler<Event> *>(handler);
                it->ApplyPreEvent(event);
            }
        }
    };
}
