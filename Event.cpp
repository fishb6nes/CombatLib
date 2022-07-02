#include <algorithm>

#include "Event.h"

using namespace Combat::Event;

template<class Entity, class Config>
bool PreBase<Entity, Config>::IsAllowed()
{
    return isExplicitlyAllowed || !isCancelled;
}

template<class Entity, class Config>
void PreBase<Entity, Config>::AddModifier(Config config, Modifier<Entity> modifier)
{
    auto it = modifiers.find(config);
    if (it == modifiers.end())
    {
        std::vector<Modifier<Entity>> configModifiers { };
        configModifiers.push_back(modifier);
        modifiers[config] = configModifiers;
    }
    else
    {
        it->second.push_back(modifier);
    }
}

template<class Entity, class Config>
void Bus<Entity, Config>::AddHandler(const Handler<Entity, Config> &handler)
{
    handlers.push_back(&handler);
}

template<class Entity, class Config>
void Bus<Entity, Config>::RemoveHandler(const Handler<Entity, Config> &handler)
{
    auto predicate = [handler](auto it) { return it == &handler; };
    auto index = std::find_if(handlers.begin(), handlers.end(), predicate);
    handlers.erase(index);
}

template<class Entity, class Config>
template<class T>
T Bus<Entity, Config>::PublishEvent(T &event) const
{
    for (auto &handler : handlers)
    {
        event = handler->ApplyEvent(event);
    }
    return event;
}
