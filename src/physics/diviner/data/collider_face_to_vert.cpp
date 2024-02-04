#include <physics/diviner/data/collider_face_to_vert.hpp>
#include <physics/diviner/physics_statics.hpp>

namespace rythe::physics
{
	std::pair<rsl::math::float3, float> rythe::physics::ColliderFaceToVert::getFurthestOutsideVert() const
	{
		const rsl::math::float3& faceCentroid = face->centroid;
		const rsl::math::float3& faceNormal = face->normal;

		float largestDist = std::numeric_limits<float>::lowest();
		const rsl::math::float3* mostDistantVert = nullptr;

		for (const rsl::math::float3& vert : outsideVerts)
		{
			float distance = PhysicsStatics::PointDistanceToPlane(faceNormal, faceCentroid, vert);

			if (distance > largestDist)
			{
				largestDist = distance;
				mostDistantVert = &vert;
			}
		}

		return std::make_pair(*mostDistantVert, largestDist);
	}

	void ColliderFaceToVert::populateVectorWithVerts(std::vector<rsl::math::float3>& vertVector)
	{
		for (size_t i = 0; i < outsideVerts.size(); i++)
		{
			vertVector.push_back(outsideVerts.at(i));
		}
	}
} // namespace rythe::physics
