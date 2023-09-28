#pragma once
#include <core/core.hpp>
#include <physics/data/component_flags.hpp>
#include <bitset>

namespace rythe::physics
{
    constexpr rsl::size_type defaultPhysicsMaterial = 0;

    struct collider_modification_data
    {
        rsl::size_type colliderIndex = std::numeric_limits<rsl::size_type>::max();
        collider_modification_flag modificationType = collider_modification_flag::cm_max;

        union modification
        {
            rsl::math::float3 newBoxExtents;
            float newRadius;
            rsl::size_type newMaterial;
        };

        modification data;
    };

    using InternalConvexColliderPtr = void*;

    class ColliderData
    {
        friend class PhysicsComponentData;

    public:

        ColliderData(rsl::size_type colliderIndex,pointer<std::vector<collider_modification_data>> modificationsRequests, collider_type colliderType, const rsl::math::float3& offset, const rsl::math::quat& rotation) noexcept;

        rythe_always_inline void setRegistered(bool registeredState) noexcept { m_isRegistered = registeredState; }
        rythe_always_inline bool isRegistered() const noexcept   { return m_isRegistered; }

        rythe_always_inline const rsl::math::float3& getOffset() const noexcept   { return m_positionOffset; }
        rythe_always_inline const rsl::math::quat& getRotationOffset() const noexcept  { return m_rotationOffset; }

        rythe_always_inline collider_type getColliderType() const noexcept  { return m_colliderType; }

        rythe_always_inline bool isRegisteredOrNotOfType(collider_type colliderType) const noexcept
        {
            return m_isRegistered || colliderType != m_colliderType;
        }

        rythe_always_inline rsl::size_type getMaterialHash() const noexcept { return m_materialHash; }

        void setMaterialHash(rsl::size_type materialHash) noexcept;
        

        rythe_always_inline pointer<const rsl::math::float3> getBoxExtents() const
        {
            if (m_colliderType != collider_type::box)
            {
                log::warn("ColliderData::getBoxExtents called on a collider that is not of type collider_type::box");
                return { nullptr };
            }

            return { &m_colliderSpecifics.boxExtents };
        }

        void setBoxExtents(const rsl::math::float3& newExtents) noexcept;
        
        rythe_always_inline pointer<const float> getSphereRadius() const 
        {
            if (m_colliderType != collider_type::sphere)
            {
                log::warn("ColliderData::getSphereRadius called on a collider that is not of type collider_type::sphere");
                return { nullptr };
            }

            return { &m_colliderSpecifics.sphereRadius };
        }

        void setSphereRadius(float newRadius) noexcept;
        
        rythe_always_inline InternalConvexColliderPtr getConvexCollider() const 
        {
            if (m_colliderType != collider_type::quickhull_convex)
            {
                log::warn("ColliderData::getConvexCollider called on a collider that is not of type collider_type::quickhull_convex");
                return { nullptr };
            }

            return m_colliderSpecifics.internalConvexStructure;
        }

        rythe_always_inline rsl::size_type getColliderIndex() const noexcept { return m_colliderIndex; }

    private:

        rythe_always_inline void setModificationRequestVector(pointer<std::vector<collider_modification_data>> modificationsRequests) noexcept
        {
            m_modificationsRequests = modificationsRequests;
        }

        rythe_always_inline void setColliderToBoxCollider(const rsl::math::float3& boxExtents)
        {
            m_colliderSpecifics.boxExtents = { boxExtents };
        }

        rythe_always_inline void setColliderToConvexCollider(InternalConvexColliderPtr convexMesh)
        {
            m_colliderSpecifics.internalConvexStructure = { convexMesh };
        }

        rythe_always_inline void setColliderToSphereCollider(float radius)
        {
            m_colliderSpecifics.sphereRadius = { radius };
        }

        union ColliderSpecifics
        {
            ColliderSpecifics() : boxExtents{ 0.0f } {}

            rsl::math::float3 boxExtents;
            InternalConvexColliderPtr internalConvexStructure;
            float sphereRadius;
        };

        ColliderSpecifics m_colliderSpecifics;

        rsl::math::quat m_rotationOffset{ math::identity<rsl::math::quat>()};
        rsl::math::float3 m_positionOffset{0};

        rsl::size_type m_materialHash = defaultPhysicsMaterial;
        rsl::size_type m_colliderIndex = std::numeric_limits<rsl::size_type>::max();

        collider_type m_colliderType = collider_type::not_set;
        pointer<std::vector<collider_modification_data>> m_modificationsRequests{nullptr};

        bool m_isRegistered = false;
    };
}

