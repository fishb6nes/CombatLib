cmake_minimum_required(VERSION 3.22)

project(CombatLib)

set(CMAKE_CXX_STANDARD 17)

add_library(CombatLib
        Ability.h Attribute.h Event.h Modifier.h Source.h Value.h
        AbilityService.h AbilityService.cpp
        events.h)
