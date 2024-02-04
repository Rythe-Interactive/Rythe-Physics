#pragma once
#include <core/core.hpp>
#include <physics/diviner/data/penetrationquery.hpp>
#include <physics/diviner/halfedgeedge.hpp>

namespace rythe::physics
{
	class EdgePenetrationQuery : public PenetrationQuery
	{
	public:
		HalfEdgeEdge* refEdge = nullptr;
		HalfEdgeEdge* incEdge = nullptr;

		EdgePenetrationQuery(HalfEdgeEdge* pRefEdge, HalfEdgeEdge* pIncEdge, rsl::math::float3& pFaceCentroid, rsl::math::float3& pNormal, float& pPenetration, bool pIsARef);

		virtual void populateContactList(physics_manifold& manifold, math::float4x4& refTransform, math::float4x4 incTransform, PhysicsCollider* refCollider);
	};
} // namespace rythe::physics
