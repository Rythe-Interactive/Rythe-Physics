
#include <physics/diviner/data/convexconvexpenetrationquery.hpp>
#include <physics/diviner/physics_statics.hpp>
#include <physics/diviner/physics_contact.hpp>
#include <physics/diviner/data/contact_vertex.hpp>

namespace rythe::physics
{
    ConvexConvexPenetrationQuery::ConvexConvexPenetrationQuery(HalfEdgeFace* pRefFace, HalfEdgeFace* pIncFace,
        rsl::math::float3& pFaceCentroid, rsl::math::float3& pNormal, float pPenetration, bool pIsARef)
        :  PenetrationQuery(pFaceCentroid,pNormal,pPenetration,pIsARef),refFace(pRefFace), incFace(pIncFace)
    {
        debugID = "ConvexConvexPenetrationQuery";
    }

    void ConvexConvexPenetrationQuery::populateContactList(physics_manifold& manifold, math::mat4& refTransform
        , math::mat4 incTransform, PhysicsCollider* refCollider)
    {
        auto incCollider = isARef ? manifold.colliderB : manifold.colliderA;
        float largestDotResult = std::numeric_limits<float>::lowest();

        //------------------------------- find face that is touching refFace -------------------------------------------------//

        for (auto face : incCollider->GetHalfEdgeFaces())
        {
            rsl::math::float3 worldFaceNormal = incTransform * math::vec4(face->normal, 0);
            float currentDotResult = math::dot(-normal, worldFaceNormal);
            if (currentDotResult > largestDotResult)
            {
                largestDotResult = currentDotResult;
                incFace = face;
            }
        }
        
        //------------------------------- get all world vertex positions in incFace -------------------------------------------------//
        std::vector<ContactVertex> outputContactPoints;

        bool facePartiallyBelowPlane = false;

        auto sendToInitialOutput = [&outputContactPoints,&incTransform](HalfEdgeEdge* edge)
        {
            rsl::math::float3 localVertexPosition = edge->edgePosition;
            rsl::math::float3 worldVertex = incTransform * math::vec4(localVertexPosition, 1);

            outputContactPoints.push_back(ContactVertex(worldVertex,edge->label));
        };

        incFace->forEachEdge(sendToInitialOutput);

        //------------------------------- clip vertices with faces that are the neighbors of refFace  ---------------------------------//
        auto clipNeigboringFaceWithOutput = [&refTransform,&outputContactPoints](HalfEdgeEdge* edge)
        {
            HalfEdgeFace* neighborFace = edge->pairingEdge->face;
            rsl::math::float3 planePosition = refTransform * math::vec4(neighborFace->centroid, 1);
            rsl::math::float3 planeNormal = refTransform * math::vec4(neighborFace->normal, 0);

            auto inputContactList = outputContactPoints;
            outputContactPoints.clear();


            PhysicsStatics::SutherlandHodgmanFaceClip(planeNormal, planePosition, inputContactList, outputContactPoints,edge);

        };

        refFace->forEachEdge(clipNeigboringFaceWithOutput);

        for (const auto& incidentContact : outputContactPoints)
        {
            float distanceToCollisionPlane = PhysicsStatics::PointDistanceToPlane(normal, faceCentroid, incidentContact.position);

            if (distanceToCollisionPlane < constants::contactOffset)
            {
                rsl::math::float3 referenceContact = incidentContact.position - normal * distanceToCollisionPlane;

                physics_contact contact;
                contact.refCollider = refCollider;
                contact.IncWorldContact = incidentContact.position;
                contact.RefWorldContact = referenceContact;
                contact.label = incidentContact.label;

                refCollider->AttemptFindAndCopyConvergenceID(contact);

                manifold.contacts.push_back(contact);
            }
        }
    }
}
