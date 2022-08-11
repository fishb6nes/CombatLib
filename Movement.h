#pragma once

#include <functional>
#include <utility>

#include "./math.h"

namespace Combat
{
    class Movement
    {
    public:
        virtual float3 Get() = 0;

        virtual bool HasNext() = 0;

        virtual float3 Next() = 0;
    };

    class StationaryMovement : public Movement
    {
    protected:
        float3 location;

    public:
        explicit StationaryMovement(float3 location)
                : location { location } { }

        float3 Get() override { return location; };

        bool HasNext() override { return true; };

        float3 Next() override { return location; };
    };

    class OneOffMovement : public Movement
    {
    protected:
        float3 location;
        bool hasNext;

    public:
        explicit OneOffMovement(float3 location)
                : location { location }, hasNext { true } { }

        float3 Get() override { return location; };

        bool HasNext() override { return hasNext; };

        float3 Next() override
        {
            hasNext = false;
            return location;
        };
    };

    class SuppliedMovement : public Movement
    {
    protected:
        float3 location;
        std::function<bool()> hasNext;
        std::function<float3()> next;

    public:
        SuppliedMovement(std::function<bool()> hasNext, std::function<float3()> next)
                : location { next() }, hasNext { std::move(hasNext) }, next { std::move(next) } { }

        float3 Get() override { return location; };

        bool HasNext() override { return hasNext(); };

        float3 Next() override { return location = next(); };
    };

    class LinearMovement : public Movement
    {
    protected:
        float3 origin;
        float3 location;
        float3 velocity;
        float maxRange;
        bool outOfRange;

    public:
        LinearMovement(float3 origin, float3 velocity, float maxRange)
                : origin { origin }, location { origin }, velocity { velocity }, maxRange { maxRange },
                  outOfRange { false } { }

        float3 Get() override { return location; };

        bool HasNext() override { return !outOfRange; };

        float3 Next() override
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
        };
    };

    class ProjectileMovement : public LinearMovement
    {
    protected:
        float gravity;

    public:
        ProjectileMovement(float3 origin, float3 velocity, float maxRange, float gravity)
                : LinearMovement(origin, velocity, maxRange), gravity { gravity } { }

        float3 Next() override
        {
            velocity.y -= gravity; // TODO adjust for physics update
            return LinearMovement::Next();
        }
    };

    class HomingMovement : public Movement
    {
    protected:
        float3 location;
        float velocity;
        std::function<float3()> target;
        bool targetReached;

    public:
        HomingMovement(float3 origin, float velocity, std::function<float3()> target)
                : location { origin }, velocity { velocity }, target { std::move(target) },
                  targetReached { false } { }

        float3 Get() override { return location; };

        bool HasNext() override { return !targetReached; };

        float3 Next() override
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
        };
    };

    class AcceleratedMovement
    {
    private:
        float acceleration;
        float maxSpeed;

    public:
        AcceleratedMovement(float acceleration, float maxSpeed)
                : acceleration { acceleration }, maxSpeed { maxSpeed } { }

        float AccelerateSpeed(float speed) const
        {
            float acceleratedSpeed = speed + acceleration;
            if ((acceleration > 0 && acceleratedSpeed >= maxSpeed) ||
                (acceleration < 0 && acceleratedSpeed <= maxSpeed))
            {
                return maxSpeed;
            }
            else return acceleratedSpeed;
        }

        float3 AccelerateVelocity(float3 velocity) const
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
    };

    class AcceleratedLinearMovement : public LinearMovement, private AcceleratedMovement
    {
    public:
        AcceleratedLinearMovement(float3 origin, float3 velocity, float maxRange,
                                  float acceleration, float maxSpeed)
                : LinearMovement(origin, velocity, maxRange),
                  AcceleratedMovement(acceleration, maxSpeed) { }

        float3 Next() override
        {
            velocity = AccelerateVelocity(velocity);
            return LinearMovement::Next();
        }
    };

    class AcceleratedProjectileMovement : public ProjectileMovement, private AcceleratedMovement
    {
    public:
        AcceleratedProjectileMovement(float3 origin, float3 velocity, float maxRange, float gravity,
                                      float acceleration, float maxSpeed)
                : ProjectileMovement(origin, velocity, maxRange, gravity),
                  AcceleratedMovement(acceleration, maxSpeed) { }

        float3 Next() override
        {
            velocity = AccelerateVelocity(velocity);
            return ProjectileMovement::Next();
        }
    };

    class AcceleratedHomingMovement : public HomingMovement, private AcceleratedMovement
    {
    public:
        AcceleratedHomingMovement(float3 origin, float velocity, std::function<float3()> target,
                                  float acceleration, float maxSpeed)
                : HomingMovement(origin, velocity, std::move(target)),
                  AcceleratedMovement(acceleration, maxSpeed) { }

        float3 Next() override
        {
            velocity = AccelerateSpeed(velocity);
            return HomingMovement::Next();
        }
    };
}
