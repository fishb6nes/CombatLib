#pragma once

#include <algorithm>
#include <map>
#include <typeindex>
#include <vector>

namespace Combat::Event
{
    class Cancellable
    {
    public:
        bool isCancelled = false;
        bool isExplicitlyAllowed = false;
        std::map<int, std::vector<Modifier>> modifiers { };

        inline bool IsAllowed() const { return !isCancelled || isExplicitlyAllowed; }
    };

    template<class Event>
    class PreHandler
    {
    public:
        virtual void ApplyPreEvent(Event &event) { }
    };

    template<class Event>
    class Handler
    {
    public:
        virtual void ApplyEvent(const Event &event) { }
    };

    class Bus
    {
    private:
        std::map<std::type_index, std::vector<void *>> preHandlers { };
        std::map<std::type_index, std::vector<void *>> handlers { };

    public:
        template<class Event>
        void AddPreHandler(PreHandler<Event> *handler)
        {
            auto it = static_cast<void *>(handler);
            preHandlers[typeid(Event)].push_back(it);
        }

        template<class Event>
        void AddHandler(Handler<Event> *handler)
        {
            auto it = static_cast<void *>(handler);
            handlers[typeid(Event)].push_back(it);
        }

        template<class Event>
        void RemovePreHandler(PreHandler<Event> *handler)
        {
            auto from = preHandlers[typeid(Event)];
            Remove(from, handler);
        }

        template<class Event>
        void RemoveHandler(Handler<Event> *handler)
        {
            auto from = handlers[typeid(Event)];
            Remove(from, handler);
        }

        template<class Event>
        void PublishPreEvent(Event &event)
        {
            for (void *handler : preHandlers[typeid(Event)])
            {
                auto it = static_cast<PreHandler<Event> *>(handler);
                it->ApplyPreEvent(event);
            }
        }

        template<class Event>
        void PublishEvent(const Event &event)
        {
            for (void *handler : handlers[typeid(Event)])
            {
                auto it = static_cast<Handler<Event> *>(handler);
                it->ApplyEvent(event);
            }
        }

    private:
        static void Remove(std::vector<void *> &from, void *handler)
        {
            auto predicate = [handler](auto it) { return it == handler; };
            auto index = std::find_if(from.begin(), from.end(), predicate);
            from.erase(index);
        }
    };
}
