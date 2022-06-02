cmake_minimum_required(VERSION 3.22)

project(Combat)

set(CMAKE_CXX_STANDARD 14)

add_library(Combat
        Attribute.h Attribute.cpp
        Event.h Event.cpp
        Modifier.h Modifier.cpp
        Source.h Source.cpp
        Value.h Value.cpp)
