#pragma once

#include <algorithm>
#include <map>
#include <typeindex>
#include <vector>

namespace Combat
{
    namespace Ability
    {
        class Snapshot;
    }

    namespace Event
    {
        struct Base
        {

        };

        struct PreBase
        {
            bool cancelled = false;
            bool explicitlyAllowed = false;

            inline bool IsAllowed() const { return !cancelled || explicitlyAllowed; }
        };

        template<class Event>
        class Handler
        {
        public:
            virtual void ApplyEvent(const Event &event) { }
        };

        template<class Event>
        class PreHandler
        {
        public:
            virtual void ApplyPreEvent(Event &event) { }
        };

        class Bus
        {
        private:
            std::map<std::type_index, std::vector<void *>> handlers { };
            std::map<std::type_index, std::vector<void *>> preHandlers { };

        public:
            template<class Event>
            void AddHandler(Handler<Event> *handler)
            {
                auto it = static_cast<void *>(handler);
                handlers[typeid(Event)].push_back(it);
            }

            template<class Event>
            void AddPreHandler(PreHandler<Event> *handler)
            {
                auto it = static_cast<void *>(handler);
                preHandlers[typeid(Event)].push_back(it);
            }

            template<class Event>
            void RemoveHandler(Handler<Event> *handler)
            {
                auto from = handlers[typeid(Event)];
                auto predicate = [handler](auto it) { return it == handler; };
                auto index = std::find_if(from.begin(), from.end(), predicate);
                from.erase(index);
            }

            template<class Event>
            void RemovePreHandler(PreHandler<Event> *handler)
            {
                auto from = preHandlers[typeid(Event)];
                auto predicate = [handler](auto it) { return it == handler; };
                auto index = std::find_if(from.begin(), from.end(), predicate);
                from.erase(index);
            }

            template<class Event>
            void PublishEvent(const Event &event)
            {
                auto _ = static_cast<Base>(event); // template type constraint hack

                for (void *handler : handlers[typeid(Event)])
                {
                    auto it = static_cast<Handler<Event> *>(handler);
                    it->ApplyEvent(event);
                }
            }

            template<class Event>
            void PublishPreEvent(Event &event)
            {
                auto _ = static_cast<PreBase>(event); // template type constraint hack

                for (void *handler : preHandlers[typeid(Event)])
                {
                    auto it = static_cast<PreHandler<Event> *>(handler);
                    it->ApplyPreEvent(event);
                }
            }
        };
    }
}
