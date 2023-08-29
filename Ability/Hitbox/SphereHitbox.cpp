#include "AABBHitbox.h"
#include "SphereHitbox.h"

using namespace Combat;

SphereHitbox
SphereHitbox::Translate(const SphereHitbox &it, float3 translation)
{
    return { it.center + translation, it.radius };
}

bool
SphereHitbox::TestAABB(const SphereHitbox &it, const AABBHitbox &other)
{
    float3 center = { other.min.x + other.dx / 2.0f,
                      other.min.y + other.dy / 2.0f,
                      other.min.z + other.dz / 2.0f };
    float radius = (other.dx + other.dy + other.dz) / 3.0f;
    return TestSphere(it, { center, radius });
}


bool
SphereHitbox::TestSphere(const SphereHitbox &it, const SphereHitbox &other)
{
    float3 distance = it.center - other.center;
    return distance.length() < it.radius + other.radius;
}
