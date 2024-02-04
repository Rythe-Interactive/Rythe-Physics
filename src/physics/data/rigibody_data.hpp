#pragma once
#include <bitset>
#include <core/core.hpp>
#include <core/events/event.hpp>
#include <physics/data/component_flags.hpp>

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

		rythe_always_inline void setInertiaTensor(const math::float3x3& inertiaTensor)
		{
			m_inertiaTensor = inertiaTensor;
			m_modificationFlags.set(rigidbody_flag::rb_inertia_tensor);
		}

		rythe_always_inline void setVelocity(const rsl::math::float3& velocity)
		{
			m_velocity = velocity;
			m_modificationFlags.set(rigidbody_flag::rb_velocity);
		}

		rythe_always_inline void setAngularVelocity(const rsl::math::float3& velocity)
		{
			m_angularVelocity = velocity;
			m_modificationFlags.set(rigidbody_flag::rb_angular_velocity);
		}

		rythe_always_inline void setLinearDrag(float linearDrag)
		{
			m_linearDrag = linearDrag;
			m_modificationFlags.set(rigidbody_flag::rb_linear_drag);
		}

		rythe_always_inline void setAngularDrag(float angularDrag)
		{
			m_angularDrag = angularDrag;
			m_modificationFlags.set(rigidbody_flag::rb_angular_drag);
		}

		rythe_always_inline float getMass() const noexcept { return m_mass; }

		rythe_always_inline math::float3x3 getInertiaTensor() const noexcept { return m_inertiaTensor; }

		rythe_always_inline rsl::math::float3 getVelocity() const noexcept { return m_velocity; }

		rythe_always_inline rsl::math::float3 getAngularVelocity() const noexcept { return m_angularVelocity; }

		rythe_always_inline float getLinearDrag() const noexcept { return m_linearDrag; }

		rythe_always_inline float getAngularDrag() const noexcept { return m_angularDrag; }

		rythe_always_inline float getDensity() const noexcept { return m_density; }

		rythe_always_inline const std::bitset<rigidbody_flag::rb_max>& getGeneratedModifyEvents() const
		{
			return m_modificationFlags;
		}

		rythe_always_inline void resetModificationFlags() { m_modificationFlags.reset(); }

		//-------------------------------------------- internal use functions ------------------------------------------------//

		/** @brief Internal use only. Sets the mass of the rigidbody without updating its bitset*/
		rythe_always_inline void setMassDirect(float newMass) noexcept { m_mass = newMass; }

		/** @brief Internal use only. Sets the density of the rigidbody without updating its bitset.
		 * The currently active active physics engine should be responsible for setting this value */
		rythe_always_inline void setDensityDirect(float newDensity) noexcept { m_density = newDensity; }

		/** @brief Internal use only. Sets the density of the rigidbody without updating its bitset.
		 * The currently active active physics engine should be responsible for setting this value */
		rythe_always_inline void setLinearVelocityDirect(const rsl::math::float3& linearVelocity) noexcept { m_velocity = linearVelocity; }

		/** @brief Internal use only. Sets the density of the rigidbody without updating its bitset.
		 * The currently active active physics engine should be responsible for setting this value */
		rythe_always_inline void setAngularVelocityDirect(const rsl::math::float3& angularVelocity) noexcept { m_velocity = angularVelocity; }

	private:
		rsl::math::float3 m_velocity = rsl::math::float3(0.0);
		rsl::math::float3 m_angularVelocity = rsl::math::float3(0.0);

		math::float3x3 m_inertiaTensor = math::float3x3(6.0f);

		float m_mass = 1.0f;
		float m_linearDrag;
		float m_angularDrag = 0.01f;

		float m_density = 1.0f;

		std::bitset<rigidbody_flag::rb_max> m_modificationFlags;
	};
} // namespace rythe::physics
