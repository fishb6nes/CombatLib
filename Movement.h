#pragma once

#include <functional>
#include <utility>

#include "./math.h"

namespace Combat
{
    class Movement
    {
    public:
        virtual float3 Get() const = 0;

        virtual bool HasNext() const = 0;

        virtual float3 Next() = 0;
    };

    class StationaryMovement : public Movement
    {
    protected:
        float3 location;

    public:
        explicit StationaryMovement(float3 location)
                : location { location } { }

        inline float3 Get() const override { return location; }

        inline bool HasNext() const override { return true; }

        inline float3 Next() override { return location; }
    };

    class OneOffMovement : public Movement
    {
    protected:
        float3 location;
        bool hasNext;

    public:
        explicit OneOffMovement(float3 location)
                : location { location }, hasNext { true } { }

        inline float3 Get() const override { return location; }

        inline bool HasNext() const override { return hasNext; }

        //@formatter:off
        inline float3 Next() override { hasNext = false; return location; }
        //@formatter:on
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

        inline float3 Get() const override { return location; }

        inline bool HasNext() const override { return hasNext(); }

        inline float3 Next() override { return location = next(); }
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

        inline float3 Get() const override { return location; }

        inline bool HasNext() const override { return !outOfRange; }

    public:
        float3 Next() override;
    };

    class ProjectileMovement : public LinearMovement
    {
    protected:
        float gravity;

    public:
        ProjectileMovement(float3 origin, float3 velocity, float maxRange, float gravity)
                : LinearMovement(origin, velocity, maxRange), gravity { gravity } { }

    public:
        float3 Next() override;
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

        inline float3 Get() const override { return location; }

        inline bool HasNext() const override { return !targetReached; }

    public:
        float3 Next() override;
    };

    class AcceleratedMovement
    {
    private:
        float acceleration;
        float maxSpeed;

    public:
        AcceleratedMovement(float acceleration, float maxSpeed)
                : acceleration { acceleration }, maxSpeed { maxSpeed } { }

    public:
        float AccelerateSpeed(float speed) const;

        float3 AccelerateVelocity(float3 velocity) const;
    };

    class AcceleratedLinearMovement : public LinearMovement, private AcceleratedMovement
    {
    public:
        AcceleratedLinearMovement(float3 origin, float3 velocity, float maxRange,
                                  float acceleration, float maxSpeed)
                : LinearMovement(origin, velocity, maxRange),
                  AcceleratedMovement(acceleration, maxSpeed) { }

    public:
        float3 Next() override;
    };

    class AcceleratedProjectileMovement : public ProjectileMovement, private AcceleratedMovement
    {
    public:
        AcceleratedProjectileMovement(float3 origin, float3 velocity, float maxRange, float gravity,
                                      float acceleration, float maxSpeed)
                : ProjectileMovement(origin, velocity, maxRange, gravity),
                  AcceleratedMovement(acceleration, maxSpeed) { }

    public:
        float3 Next() override;
    };

    class AcceleratedHomingMovement : public HomingMovement, private AcceleratedMovement
    {
    public:
        AcceleratedHomingMovement(float3 origin, float velocity, std::function<float3()> target,
                                  float acceleration, float maxSpeed)
                : HomingMovement(origin, velocity, std::move(target)),
                  AcceleratedMovement(acceleration, maxSpeed) { }

    public:
        float3 Next() override;
    };
}
