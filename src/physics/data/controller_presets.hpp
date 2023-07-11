#pragma once
#include <core/core.hpp>

namespace rythe::physics
{
    struct gravity_preset
    {
        rsl::math::float3 gravityValue = rsl::math::float3(0.0f);
        rsl::math::float3 gravityAcc = rsl::math::float3(0.0f);
    };

    //preset must be added within the same physics time step that the target capsule is created
    struct rigidbody_force_feedback
    {
        float forceAmount = 0.0f;
        float massMaximum = 0.0f;//if massMaximum is <= 0, all rigidbodies will be pushed regardless of mass
    }; //TODO: make it so that this preset can be set at any point of the appplication
}
