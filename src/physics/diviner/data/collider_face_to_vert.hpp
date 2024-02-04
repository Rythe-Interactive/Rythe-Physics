#pragma once
#include <core/core.hpp>
#include <physics/diviner/halfedgeface.hpp>

namespace rythe::physics
{
	class ColliderFaceToVert
	{
	public:
		std::vector<rsl::math::float3> outsideVerts;
		core::pointer<HalfEdgeFace> face{nullptr};

		ColliderFaceToVert(HalfEdgeFace* pFace)
			: face{pFace}
		{
			pFace->faceToVert = this;
		}

		/** @brief Given the positions in 'outsideVerts', gets the vertex furthest from the HalfEdgeFace 'face'
		 */
		std::pair<rsl::math::float3, float> getFurthestOutsideVert() const;

		/** @brief Given the vertices in 'vertVector', adds them to 'outsideVerts'
		 */
		void populateVectorWithVerts(std::vector<rsl::math::float3>& vertVector);
	};
} // namespace rythe::physics
