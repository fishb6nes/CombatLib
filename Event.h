#pragma once

#include <algorithm>
#include <vector>

namespace Combat
{
    namespace Event
    {
        struct AbilityPreCast { };

        struct AbilityCast { };

        struct AbilityPreHit { };

        struct AbilityHit { };

        struct AbilityMiss { };

        class Handler
        {
        public:
            virtual void ApplyEvent(AbilityPreCast &event) { }

            virtual void ApplyEvent(AbilityCast &event) { }

            virtual void ApplyEvent(AbilityPreHit &event) { }

            virtual void ApplyEvent(AbilityHit &event) { }

            virtual void ApplyEvent(AbilityMiss &event) { }
        };

        class Bus
        {
        private:
            std::vector<const Handler *> handlers { };

        public:
            void AddHandler(const Handler &handler);

            void RemoveHandler(const Handler &handler);

            template<class T> T PublishEvent(T &event);
        };
    }
}
