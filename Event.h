#pragma once

#include <algorithm>
#include <vector>

namespace Combat::Event
{
    struct PreBase
    {
        std::multimap<int, Modifier> modifiers { };
        bool isCancelled = false;
        bool isExplicitlyAllowed = false;

        void AddModifier(int type, Modifier modifier)
        {
            modifiers.insert(std::pair(type, modifier));
        }

        inline bool IsAllowed() const
        {
            return isExplicitlyAllowed || !isCancelled;
        }
    };

    class Handler
    {
    public:
        virtual void ApplyEvent(struct AbilityPreCast &event) { }

        virtual void ApplyEvent(const struct AbilityCast &event) { }

        virtual void ApplyEvent(struct AbilityPreHit &event) { }

        virtual void ApplyEvent(const struct AbilityHit &event) { }

        virtual void ApplyEvent(const struct AbilityMiss &event) { }
    };

    class Bus
    {
    private:
        std::vector<Handler *> handlers { };

    public:
        void AddHandler(Handler *handler)
        {
            handlers.push_back(handler);
        }

        void RemoveHandler(Handler *handler)
        {
            auto predicate = [handler](auto it) { return it == handler; };
            auto index = std::find_if(handlers.begin(), handlers.end(), predicate);
            handlers.erase(index);
        }

        template<class T>
        void PublishEvent(T &event) const
        {
            for (auto &handler : handlers)
            {
                handler->ApplyEvent(event);
            }
        }
    };
}
