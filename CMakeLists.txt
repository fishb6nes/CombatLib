cmake_minimum_required(VERSION 3.22)

project(CombatLib)

set(CMAKE_CXX_STANDARD 17)

add_library(CombatLib
        Entity.h Hitbox.h Modifier.h Source.h
        Ability.h AbilityService.h AbilityService.cpp
        Attribute.h Attribute.cpp
        Event.h EventBus.h EventBus.cpp events.h
        math.h
        Movement.h Movement.cpp
        Projectile.h Projectile.cpp ProjectileManager.h ProjectileManager.cpp
        Value.h Value.cpp)
