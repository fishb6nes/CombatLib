#pragma once

#include <cassert>
#include <vector>

#include "Modifier.h"

namespace Combat
{

    class Value
    {
    private:
        enum class Type : uint8_t { ATTRIBUTE, VALUE } type;
        float baseValue;
        Source *source;

        std::vector<Modifier> modifiers;
        float flatModifier = 0;
        float percentModifier = 1;
        float modifiedValue = 0;

    public:
        Value(Value::Type type, float baseValue, Source *source)
                : type { type }, baseValue { baseValue }, source { source }, modifiers { } { }

        inline float
        GetBaseValue() const { return baseValue; }

        inline Source *
        GetSource() const { return source; }

        inline float
        GetModifiedValue() const { return modifiedValue; }

        inline const std::vector<Modifier> &
        ViewModifiers() const { return modifiers; }

    public:
        void
        AddModifier(Modifier modifier)
        {
            modifiers.push_back(modifier);

            SelectModifierValue(modifier, flatModifier, percentModifier) += modifier.value;
            modifiedValue = ComputeModifiedValue(type, baseValue, flatModifier, percentModifier);
        }

        void
        RemoveModifier(const Modifier &modifier)
        {
            auto index = std::find(modifiers.begin(), modifiers.end(), modifier);
            assert(index != modifiers.end());

            if (index != modifiers.end())
            {
                modifiers.erase(index);

                SelectModifierValue(modifier, flatModifier, percentModifier) -= modifier.value;
                modifiedValue = ComputeModifiedValue(type, baseValue, flatModifier, percentModifier);
            }
        }

    private:
        static inline float &
        SelectModifierValue(const Modifier &modifier, float &flatModifier, float &percentModifier)
        {
            switch (modifier.type)
            {
                case Modifier::Type::FLAT: return flatModifier;
                case Modifier::Type::PERCENT: return percentModifier;
            }
        }

        static inline float
        ComputeModifiedValue(Value::Type type, float baseValue, float flatModifier, flat percentModifier)
        {
            switch (type)
            {
                case Value::Type::ATTRIBUTE: return baseValue + flatModifier * percentModifier;
                case Value::Type::VALUE: return baseValue * percentModifier + flatModifier;
            }
        }
    };

//    class Value
//    {
//    private:
//        Source *source;
//        float baseValue;
//        std::vector<Modifier> modifiers;
//
//        float percentModifier = 1;
//        float flatModifier = 0;
//        float cachedValue = 0;
//
//    public:
//        Value(Source *source, float base, const std::vector<Modifier> &modifiers = { })
//                : source { source }, baseValue { base }, modifiers { modifiers }
//        {
//            for (auto modifier : modifiers) UpdateCache(modifier);
//        }
//
//        inline Source *
//        GetSource() const { return source; }
//
//        inline float
//        GetBaseValue() const { return baseValue; }
//
//        inline const std::vector<Modifier> &
//        GetModifiers() const { return modifiers; }
//
//        inline float
//        GetModifiedValue() const { return cachedValue; }
//
//    public:
//        void
//        AddModifier(Modifier modifier)
//        {
//            modifiers.push_back(modifier);
//            UpdateCache(modifier);
//        }
//
//    private:
//        inline void
//        UpdateCache(Modifier modifier)
//        {
//            percentModifier += modifier.percentModifier;
//            flatModifier += modifier.flatModifier;
//            cachedValue = baseValue * percentModifier + flatModifier;
//        }
//    };
}
