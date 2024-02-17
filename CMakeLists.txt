cmake_minimum_required(VERSION 3.26.4)
set(CMAKE_CXX_STANDARD 20)

project(CombatLib VERSION 0.0.1)
option(PHYSX_BUILD_TYPE "one of {debug, checked, profile, release}" "checked")

include_directories(../PhysX/physx/include)

if(CMAKE_BUILD_TYPE AND CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("Building in debug configuration")
    add_compile_definitions(_DEBUG)
    link_directories("../PhysX/physx/bin/win.x86_64.vc143.mt/debug")
else()
    message("Building in release configuration with PhysX ${PHYSX_BUILD_TYPE} configuration")
    add_compile_definitions(NDEBUG)
    link_directories("PhysX/bin/win.x86_64.vc143.mt/${PHYSX_BUILD_TYPE}")
endif()

add_library(CombatLib
        Ability/Ability.h
        Ability/AbilityService.h Ability/AbilityService.cpp

        Ability/Hitbox.h
        Ability/Hitbox/BasicHitbox.h
        Ability/Hitbox/CachedHitbox.h
        Ability/Hitbox/TargetedHitbox.h

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
        math.h
        concepts.h
        Entity/Hittable.h
        Projectile/ProjectileSystem.cpp
        Projectile/ProjectileSystem.h)

target_link_libraries(CombatLib
        PhysXExtensions_static_64
        PhysX_static_64
        PhysXPvdSDK_static_64
        PhysXCommon_static_64
        PhysXFoundation_static_64

        pthread
        dl
)
