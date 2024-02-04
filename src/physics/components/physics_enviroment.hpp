#pragma once
#include <core/core.hpp>
#include <physics/data/physics_enviroment_data.hpp>

namespace rythe::physics
{
	constexpr rsl::size_type invalid_physics_enviroment = std::numeric_limits<rsl::size_type>::max();

	struct physics_enviroment
	{
		PhysicsEnviromentData data;
		size_t physicsEnviromentID = invalid_physics_enviroment;
	};
} // namespace rythe::physics
