cmake_minimum_required(VERSION 3.22)

project(CombatLib)

set(CMAKE_CXX_STANDARD 17)

add_library(CombatLib
        Ability.h Ability.cpp
        AbilityService.cpp AbilityService.h
        Attribute.h Attribute.cpp
        Event.h Event.cpp
        Modifier.h Modifier.cpp
        Source.h Source.cpp
        Value.h Value.cpp)
