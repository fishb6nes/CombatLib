#include "AABBHitbox.h"
#include "SphereHitbox.h"

using namespace Combat;

AABBHitbox
AABBHitbox::Translate(const AABBHitbox &it, float3 translation)
{
    return { it.min + translation, it.max + translation };
}

bool
AABBHitbox::TestAABB(const AABBHitbox &it, const AABBHitbox &other)
{
    return it.max.x >= other.min.x
           && it.min.x <= other.max.x
           && it.max.y >= other.min.y
           && it.min.y <= other.max.y
           && it.max.z >= other.min.z
           && it.min.z <= other.max.z;
}

bool
AABBHitbox::TestSphere(const AABBHitbox &it, const SphereHitbox &other)
{
    float3 min = {
            other.center.x - other.radius,
            other.center.y - other.radius,
            other.center.z - other.radius };
    float3 max = {
            other.center.x + other.radius,
            other.center.y + other.radius,
            other.center.z + other.radius };
    return TestAABB(it, { min, max });
}
