#pragma once

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
}
