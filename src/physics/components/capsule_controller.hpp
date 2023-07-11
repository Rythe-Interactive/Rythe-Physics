#pragma once
#include <physics/data/capsule_controller_data.hpp>

namespace rythe::physics
{
    constexpr size_t invalid_capsule_controller = std::numeric_limits<rsl::size_type>::max();

    struct capsule_controller
    {
        CapsuleControllerData data;
        size_t id = invalid_capsule_controller;
    };
}
