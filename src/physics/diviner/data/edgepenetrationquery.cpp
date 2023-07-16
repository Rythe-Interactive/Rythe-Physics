
#include <physics/diviner/data/edgepenetrationquery.hpp>
#include <physics/diviner/physics_statics.hpp>
#include <rendering/debugrendering.hpp>


namespace rythe::physics
{
    EdgePenetrationQuery::EdgePenetrationQuery(HalfEdgeEdge* pRefEdge, HalfEdgeEdge* pIncEdge,
        rsl::math::float3& pFaceCentroid, rsl::math::float3& pNormal, float& pPenetration, bool pIsARef) :
        PenetrationQuery(pFaceCentroid,pNormal,pPenetration,pIsARef),refEdge(pRefEdge),incEdge(pIncEdge)
    {
        debugID = "EdgePenetrationQuery";
    }


    void EdgePenetrationQuery::populateContactList(physics_manifold& manifold,
        math::float4x4& refTransform, math::float4x4 incTransform, PhysicsCollider* refCollider)
    {
        //------------------- The contact points between 2 edges are the closest points between the 2 edges --------------------//
        //log::debug("EdgePenetrationQuery::populateContactList");

        rsl::math::float3 p1 = refTransform * math::float4(refEdge->edgePosition, 1);
        rsl::math::float3 p2 = refTransform * math::float4(refEdge->nextEdge->edgePosition, 1);

        rsl::math::float3 p3 = incTransform * math::float4(incEdge->edgePosition, 1);
        rsl::math::float3 p4 = incTransform * math::float4(incEdge->nextEdge->edgePosition, 1);

        rsl::math::float3 refContactPoint;
        rsl::math::float3 incContactPoint;

        PhysicsStatics::FindClosestPointsBetweenLineSegments(p1, p2, p3, p4, refContactPoint, incContactPoint);

        /*debug::user_projectdrawLine(p1, p2, math::colors::black, 5.0f, 20.0f);
        debug::user_projectdrawLine(p3, p4, math::colors::grey, 5.0f, 20.0f);
        debug::user_projectdrawLine(refContactPoint, incContactPoint, math::colors::darkgrey, 5.0f, 20.0f);*/

        physics_contact contact;

        auto refLabel = refEdge->label;
        auto incLabel = incEdge->label;

        contact.label = EdgeLabel(std::make_pair(refLabel.firstEdge.first, refLabel.firstEdge.second),
            std::make_pair(incLabel.nextEdge.first, incLabel.nextEdge.second));

        contact.refCollider = refCollider;
        contact.IncWorldContact = incContactPoint;
        contact.RefWorldContact = refContactPoint;

        refCollider->AttemptFindAndCopyConvergenceID(contact);

        manifold.contacts.push_back(contact);

    }

}
