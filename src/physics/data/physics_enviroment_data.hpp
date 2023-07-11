#pragma once
#include <physics/data/component_flags.hpp>
#include <bitset>

namespace rythe::physics
{
    class PhysicsEnviromentData
    {
    public:

        void instantiateInfinitePlane(const rsl::math::float3& planeNormal, float distFromOrigin)
        {
            if (m_objectType == physics_enviroment_object_type::not_set)
            {
                m_modificationFlags.set(physics_enviroment_flag::pe_add_plane);
                m_planeNormal = planeNormal;
                m_distFromOrigin = distFromOrigin;
            }
            else
            {
                log::warn("Infinite Plane Instantiation Failed! PhysicsEnviromentData is already set");
            }
        }

        R_ALWAYS_INLINE void resetModificationFlags() { m_modificationFlags.reset(); }

        R_ALWAYS_INLINE const std::bitset<physics_enviroment_flag::pe_max>& getGeneratedModifyEvents() const noexcept
        {
            return m_modificationFlags;
        };

        R_ALWAYS_INLINE const rsl::math::float3& getInfinitePlaneNormal() const noexcept { return m_planeNormal; }

        R_ALWAYS_INLINE float getInfinitePlaneDistanceToOrigin() const noexcept { return m_distFromOrigin; }
    private:

        rsl::math::float3 m_planeNormal;
        float m_distFromOrigin;

        std::bitset<physics_enviroment_flag::pe_max> m_modificationFlags;
        physics_enviroment_object_type m_objectType = physics_enviroment_object_type::not_set;
    };
}
