#include "Movement.h"

using namespace Combat;

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

float3 ProjectileMovement::Next()
{
    velocity.y -= gravity; // TODO adjust for physics update
    return LinearMovement::Next();
}

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

float AcceleratedMovement::AccelerateSpeed(float speed) const
{
    float acceleratedSpeed = speed + acceleration;
    if ((acceleration > 0 && acceleratedSpeed >= maxSpeed) ||
        (acceleration < 0 && acceleratedSpeed <= maxSpeed))
    {
        return maxSpeed;
    }
    else return acceleratedSpeed;
}

float3 AcceleratedMovement::AccelerateVelocity(float3 velocity) const
{
    if (acceleration != 0)
    {
        float velocityLength = velocity.length();
        float acceleratedLength = AccelerateSpeed(velocityLength);
        float accelerationScalar = acceleratedLength / velocityLength;
        return velocity * accelerationScalar;
    }
    else return velocity;
}

float3 AcceleratedLinearMovement::Next()
{
    velocity = AccelerateVelocity(velocity);
    return LinearMovement::Next();
}

float3 AcceleratedProjectileMovement::Next()
{
    velocity = AccelerateVelocity(velocity);
    return ProjectileMovement::Next();
}

float3 AcceleratedHomingMovement::Next()
{
    velocity = AccelerateSpeed(velocity);
    return HomingMovement::Next();
}
