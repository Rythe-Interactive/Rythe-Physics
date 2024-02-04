#pragma once

#include <core/core.hpp>

namespace rythe::physics::constants
{
	static rsl::math::float3 gravity = rsl::math::float3(0, -9.81, 0);

	static constexpr rsl::size_type contactSolverIterationCount = 9;

	static constexpr rsl::size_type frictionSolverIterationCount = 4;

	static constexpr float faceToFacePenetrationBias = 0.005f;

	static constexpr float faceToEdgePenetrationBias = 0.05f;

	static constexpr float baumgarteCoefficient = 0.1f;

	static constexpr float baumgarteSlop = 0.01f;

	static constexpr float restitutionSlop = 0.5f;

	static constexpr float contactOffset = 0.01f;

	static constexpr float sutherlandHodgmanClippingThreshold = 0.01f;

	static constexpr float gaussMapEdgeCheckAngleThres = 0.99862953475f;

	static constexpr bool applyWarmStarting = true;
} // namespace rythe::physics::constants
