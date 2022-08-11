cmake_minimum_required(VERSION 3.22)

project(CombatLib)

set(CMAKE_CXX_STANDARD 17)

add_library(CombatLib
        Attribute.h Entity.h Event.h Hitbox.h Modifier.h Movement.h Projectile.h Source.h Value.h
        Ability.h AbilityService.h AbilityService.cpp
        events.h math.h)
