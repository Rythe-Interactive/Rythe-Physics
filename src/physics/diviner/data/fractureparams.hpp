#pragma once
#include <core/core.hpp>

namespace rythe::physics
{
	/** @struct FractureParams
	 * @brief contains the parameters that will be used for a given fracture event.
	 */
	struct FractureParams
	{

		rsl::math::float3 explosionCentroid;
		float strength;

		FractureParams(rsl::math::float3 pWorldExplostionCent, float pStrength = 5.0f)
			: explosionCentroid(pWorldExplostionCent),
			  strength(pStrength)
		{
		}
	};
} // namespace rythe::physics
