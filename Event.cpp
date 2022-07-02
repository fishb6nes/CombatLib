#include <algorithm>

#include "Event.h"

using namespace Combat::Event;

template<class AbilityAttribute, class Entity>
void PreBase<AbilityAttribute, Entity>::AddModifier(AbilityAttribute attribute, Modifier<Entity> modifier)
{
    auto it = modifiers.find(attribute);
    if (it == modifiers.end())
    {
        std::vector<Modifier<Entity>> configModifiers { };
        configModifiers.push_back(modifier);
        modifiers[attribute] = configModifiers;
    }
    else
    {
        it->second.push_back(modifier);
    }
}

template<class AbilityAttribute, class Entity>
void Bus<AbilityAttribute, Entity>::AddHandler(const Handler<AbilityAttribute, Entity> &handler)
{
    handlers.push_back(&handler);
}

template<class AbilityAttribute, class Entity>
void Bus<AbilityAttribute, Entity>::RemoveHandler(const Handler<AbilityAttribute, Entity> &handler)
{
    auto predicate = [handler](auto it) { return it == &handler; };
    auto index = std::find_if(handlers.begin(), handlers.end(), predicate);
    handlers.erase(index);
}

template<class AbilityAttribute, class Entity>
template<class T>
T Bus<AbilityAttribute, Entity>::PublishEvent(T &event) const
{
    for (auto &handler : handlers)
    {
        event = handler->ApplyEvent(event);
    }
    return event;
}
