#pragma once

#include "PxPhysicsAPI.h"

using namespace physx;
using namespace std;

namespace Combat
{
    struct Movement
    {
        enum class Type : uint8_t
        {
            ENTITY,
            LINEAR,
            ONESHOT,
            STATIC,
        } type;

        bool hasNext;
        PxVec3 location;
        union { class Entity *entity; PxVec3 velocity; } data;

        inline PxVec3
        SetNext()
        {
            switch (type)
            {
                case Type::ENTITY:
                {
                    location = data.entity->GetLocation();
                    break;
                }
                case Type::LINEAR:
                {
                    location = location + data.velocity;
                    break;
                }
                default: break;
            }
            return location;
        }

        inline static Movement
        Entity(Entity *entity)
        {
            return { Type::ENTITY, true, entity->GetLocation(), entity };
        }

        inline static Movement
        Linear(PxVec3 origin, PxVec3 velocity)
        {
            return { Type::LINEAR, true, origin, { .velocity=velocity }};
        }

        inline static Movement
        Oneshot(PxVec3 location)
        {
            return { Type::ONESHOT, false, location, nullptr };
        }

        inline static Movement
        Static(PxVec3 location)
        {
            return { Type::STATIC, true, location, nullptr };
        }
    };
}
