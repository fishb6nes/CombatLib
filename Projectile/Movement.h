#pragma once

#include "Movement/EntityMovement.h"
#include "Movement/LinearMovement.h"
#include "Movement/OneOffMovement.h"
#include "Movement/StaticMovement.h"

namespace Combat
{
    struct Movement
    {
        enum Type
        {
            STATIC,
            ONEOFF,
            LINEAR,
            ENTITY,
        } type;

        union
        {
            float3 location;

            StaticMovement _static;
            OneOffMovement _oneoff;
            LinearMovement _linear;
            EntityMovement _entity;
        };

        Movement(const StaticMovement &it)
                : type { STATIC }, _static { it } { }

        Movement(const OneOffMovement &it)
                : type { ONEOFF }, _oneoff { it } { }

        Movement(const LinearMovement &it)
                : type { LINEAR }, _linear { it } { }

        Movement(const EntityMovement &it)
                : type { ENTITY }, _entity { it } { }

        operator StaticMovement() const { return _static; }
        operator OneOffMovement() const { return _oneoff; }
        operator LinearMovement() const { return _linear; }
        operator EntityMovement() const { return _entity; }

        static bool
        HasNext(const Movement &it)
        {
            switch (it.type)
            {
                case STATIC: return StaticMovement::HasNext(it);
                case ONEOFF: return OneOffMovement::HasNext(it);
                case LINEAR: return LinearMovement::HasNext(it);
                case ENTITY: return EntityMovement::HasNext(it);
            }
        }

        static Movement
        SetNext(const Movement &it)
        {
            switch (it.type)
            {
                case STATIC: return StaticMovement::SetNext(it);
                case ONEOFF: return OneOffMovement::SetNext(it);
                case LINEAR: return LinearMovement::SetNext(it);
                case ENTITY: return EntityMovement::SetNext(it);
            }
        }
    };
}
