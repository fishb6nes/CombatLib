cmake_minimum_required(VERSION 3.26.4)

project(CombatLib VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)

add_library(CombatLib
        Ability/Ability.h
        Ability/AbilityService.h Ability/AbilityService.cpp
        Ability/Hitbox.h

        Core/Attribute.h
        Core/Modifier.h
        Core/Source.h
        Core/Value.h

        Entity/Entity.h
        Entity/EntityService.h

        Event/Event.h
        Event/EventBus.h Event/EventBus.cpp

        Projectile/Movement.h
        Projectile/Projectile.h
        Projectile/ProjectileManager.h Projectile/ProjectileManager.cpp

        events.h
        headers.cpp
        math.h)
