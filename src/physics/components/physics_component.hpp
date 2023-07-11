#pragma once
#include <physics/data/physics_component_data.hpp>

namespace rythe::physics
{
    constexpr size_t invalid_physics_component = std::numeric_limits<rsl::size_type>::max();

    struct physics_component
    {
        PhysicsComponentData physicsCompData;
        size_t physicsComponentID = invalid_physics_component;
    };
}
