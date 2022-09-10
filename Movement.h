#pragma once

#include <functional>
#include <utility>

#include "./math.h"

namespace Combat
{
    /**
     * An interface representing a certain movement in 3D space.
     *
     * Once `HasNext` returns false this movement reached its destination and `Next` should no longer be used.
     */
    class Movement
    {
    public:
        virtual float3 Get() const = 0;

        virtual bool HasNext() const = 0;

        virtual float3 Next() = 0;
    };

    /**
     * A stationary movement that will always have a next location and always return the same location.
     */
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

    /**
     * A one-off movement that will only supply the provided location once.
     */
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

    /**
     * A movement that follows the location supplied by `next` for as long as `hasNext` supplies true.
     */
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

    /**
     * A linear movement starting at `origin` henceforth travelling linearly following its `velocity` until
     * reaching its `maxRange`.
     */
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
                : origin { origin }, location { origin }, velocity { velocity },
                  maxRange { maxRange }, outOfRange { false } { }

        inline float3 Get() const override { return location; }

        inline bool HasNext() const override { return !outOfRange; }

    public:
        float3 Next() override;
    };

    /**
     *
     */
    class ProjectileMovement : public LinearMovement
    {
    protected:
        float gravity;

    public:
        ProjectileMovement(float3 origin, float3 velocity, float maxRange,
                           float gravity)
                : LinearMovement(origin, velocity, maxRange),
                  gravity { gravity } { }

    public:
        float3 Next() override;
    };

    /**
     *
     */
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

    /**
     *
     */
    template<class T>
    class AcceleratedMovement : public Movement
    {
    private:
        T &movement;

        float acceleration;
        float maxVelocity;

    public:
        AcceleratedMovement(T &movement, float acceleration, float maxVelocity)
                : movement { movement }, acceleration { acceleration }, maxVelocity { maxVelocity } { }

    public:
        float3 Next() override;

    private:
        float AccelerateVelocity(float velocity) const;

        float3 AccelerateVelocity(float3 velocity) const;
    };
}
