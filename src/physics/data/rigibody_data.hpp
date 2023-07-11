#pragma once
#include <core/core.hpp>
#include <core/events/event.hpp>
#include <physics/data/component_flags.hpp>
#include <bitset>

namespace rythe::physics
{
    class RigidbodyData
    {
    public:

        void setMass(float mass)
        {
            m_mass = mass;
            m_modificationFlags.set(rigidbody_flag::rb_mass);
        }

        R_ALWAYS_INLINE void setInertiaTensor(const math::mat3& inertiaTensor)
        {
            m_inertiaTensor = inertiaTensor;
            m_modificationFlags.set(rigidbody_flag::rb_inertia_tensor);
        }
        
        R_ALWAYS_INLINE void setVelocity(const rsl::math::float3& velocity)
        {
            m_velocity = velocity;
            m_modificationFlags.set(rigidbody_flag::rb_velocity);
        }

        R_ALWAYS_INLINE void setAngularVelocity(const rsl::math::float3& velocity)
        {
            m_angularVelocity = velocity;
            m_modificationFlags.set(rigidbody_flag::rb_angular_velocity);
        }
        
        R_ALWAYS_INLINE void setLinearDrag(float linearDrag)
        {
            m_linearDrag = linearDrag;
            m_modificationFlags.set(rigidbody_flag::rb_linear_drag);
        }

        R_ALWAYS_INLINE void setAngularDrag(float angularDrag)
        {
            m_angularDrag = angularDrag;
            m_modificationFlags.set(rigidbody_flag::rb_angular_drag);
        }
        
        R_ALWAYS_INLINE float getMass() const noexcept { return m_mass; }

        R_ALWAYS_INLINE math::mat3 getInertiaTensor() const noexcept { return m_inertiaTensor; }

        R_ALWAYS_INLINE rsl::math::float3 getVelocity() const noexcept { return m_velocity; }

        R_ALWAYS_INLINE rsl::math::float3 getAngularVelocity() const noexcept { return m_angularVelocity; }

        R_ALWAYS_INLINE float getLinearDrag() const noexcept { return m_linearDrag; }

        R_ALWAYS_INLINE float getAngularDrag() const noexcept { return m_angularDrag; }

        R_ALWAYS_INLINE float getDensity() const noexcept { return m_density; }

        R_ALWAYS_INLINE const std::bitset<rigidbody_flag::rb_max>& getGeneratedModifyEvents() const
        {
            return m_modificationFlags;
        }

        R_ALWAYS_INLINE void resetModificationFlags() { m_modificationFlags.reset(); }

        //-------------------------------------------- internal use functions ------------------------------------------------//

        /** @brief Internal use only. Sets the mass of the rigidbody without updating its bitset*/
        R_ALWAYS_INLINE void setMassDirect(float newMass) noexcept { m_mass = newMass; }

        /** @brief Internal use only. Sets the density of the rigidbody without updating its bitset.
         * The currently active active physics engine should be responsible for setting this value */
        R_ALWAYS_INLINE void setDensityDirect(float newDensity) noexcept { m_density = newDensity; }

        /** @brief Internal use only. Sets the density of the rigidbody without updating its bitset.
         * The currently active active physics engine should be responsible for setting this value */
        R_ALWAYS_INLINE void setLinearVelocityDirect(const rsl::math::float3& linearVelocity) noexcept { m_velocity = linearVelocity; }

        /** @brief Internal use only. Sets the density of the rigidbody without updating its bitset.
         * The currently active active physics engine should be responsible for setting this value */
        R_ALWAYS_INLINE void setAngularVelocityDirect(const rsl::math::float3& angularVelocity) noexcept { m_velocity = angularVelocity; }

    private:

        rsl::math::float3 m_velocity = rsl::math::float3(0.0);
        rsl::math::float3 m_angularVelocity = rsl::math::float3(0.0);

        math::mat3 m_inertiaTensor = math::mat3(6.0f);

        float m_mass = 1.0f;
        float m_linearDrag;
        float m_angularDrag = 0.01f;

        float m_density = 1.0f;

        std::bitset<rigidbody_flag::rb_max> m_modificationFlags;
    };
}
