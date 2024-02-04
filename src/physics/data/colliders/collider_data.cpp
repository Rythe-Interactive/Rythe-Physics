#include "collider_data.hpp"

namespace rythe::physics
{
	ColliderData::ColliderData(rsl::size_type colliderIndex, pointer<std::vector<collider_modification_data>> modificationsRequests, collider_type colliderType, const rsl::math::float3& offset, const rsl::math::quat& rotation) noexcept
		: m_rotationOffset(rotation),
		  m_positionOffset(offset),
		  m_colliderIndex(colliderIndex),
		  m_colliderType(colliderType),
		  m_modificationsRequests(modificationsRequests),
		  m_isRegistered(false)
	{
	}

	void ColliderData::setMaterialHash(rsl::size_type materialHash) noexcept
	{
		m_materialHash = materialHash;

		collider_modification_data modData;
		modData.colliderIndex = m_colliderIndex;
		modData.modificationType = collider_modification_flag::cm_set_new_material;
		modData.data.newMaterial = materialHash;

		m_modificationsRequests->push_back(modData);
	}

	void ColliderData::setBoxExtents(const rsl::math::float3& newExtents) noexcept
	{
		collider_modification_data modData;
		modData.colliderIndex = m_colliderIndex;
		modData.modificationType = collider_modification_flag::cm_set_new_box_extents;
		modData.data.newBoxExtents = newExtents;

		m_modificationsRequests->push_back(modData);
	}

	void ColliderData::setSphereRadius(float newRadius) noexcept
	{
		collider_modification_data modData;
		modData.colliderIndex = m_colliderIndex;
		modData.modificationType = collider_modification_flag::cm_set_new_sphere_radius;
		modData.data.newRadius = newRadius;

		m_modificationsRequests->push_back(modData);
	}
} // namespace rythe::physics
