#pragma once
#include <physics/diviner/data/penetrationquery.hpp>
#include <physics/diviner/halfedgeedge.hpp>

namespace rythe::physics
{
    class ConvexConvexPenetrationQuery : public PenetrationQuery
    {
    public:

        HalfEdgeFace* refFace = nullptr;
        HalfEdgeFace* incFace = nullptr;

        ConvexConvexPenetrationQuery(HalfEdgeFace* pRefFace, HalfEdgeFace* pIncFace, rsl::math::float3& pFaceCentroid,
            rsl::math::float3& pNormal, float pPenetration, bool pIsARef);

        virtual void populateContactList(physics_manifold& manifold,  math::float4x4& refTransform,
            math::float4x4 incTransform , PhysicsCollider* refCollider) override;

    };
}


