#include "Movement.h"

using namespace Combat;

/// LinearMovement

float3 LinearMovement::Next()
{
    float distance = (location - origin).length();
    float distanceDelta = velocity.length();
    float nextDistance = distance + distanceDelta;
    if (nextDistance < maxRange)
    {
        location = location + velocity;
    }
    else
    {
        float deltaCorrection = (nextDistance - maxRange) / distanceDelta;
        location = location + (velocity * deltaCorrection);
        outOfRange = true;
    }
    return location;
}

/// ProjectileMovement

float3 ProjectileMovement::Next()
{
    velocity.y -= gravity; // TODO adjust for physics update
    return LinearMovement::Next();
}

/// HomingMovement

float3 HomingMovement::Next()
{
    float3 nextTarget = target();
    float distance = (nextTarget - location).length();
    if (distance > velocity)
    {
        float3 direction = (nextTarget - location).normalized();
        float3 directionalVelocity = direction * velocity;
        location = location + directionalVelocity;
    }
    else
    {
        location = nextTarget;
        targetReached = true;
    }
    return location;
}

/// AcceleratedMovement

template<class T>
float3 AcceleratedMovement<T>::Next()
{
    movement.velocity = AccelerateVelocity(movement.velocity);
    return movement.Next();
}

template<class T>
float AcceleratedMovement<T>::AccelerateVelocity(float velocity) const
{
    float acceleratedVelocity = velocity + acceleration;
    if ((acceleration > 0 && acceleratedVelocity >= maxVelocity) ||
        (acceleration < 0 && acceleratedVelocity <= maxVelocity))
    {
        return maxVelocity;
    }
    else return acceleratedVelocity;
}

template<class T>
float3 AcceleratedMovement<T>::AccelerateVelocity(float3 velocity) const
{
    if (acceleration != 0)
    {
        float velocityLength = velocity.length();
        float acceleratedLength = AccelerateVelocity(velocityLength);
        float accelerationScalar = acceleratedLength / velocityLength;
        return velocity * accelerationScalar;
    }
    else return velocity;
}
