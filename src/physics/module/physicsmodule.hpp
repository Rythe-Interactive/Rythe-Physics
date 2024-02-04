#pragma once
#include <core/core.hpp>

#include <physics/components/capsule_controller.hpp>
#include <physics/components/physics_component.hpp>
#include <physics/components/physics_enviroment.hpp>
#include <physics/components/rigidbody.hpp>
#include <physics/diviner/components/physics_component.hpp>
#include <physics/diviner/components/rigidbody.hpp>
#include <physics/diviner/systems/physicssystem.hpp>
#include <physics/physx/systems/physx_physics_system.hpp>

namespace rythe::physics
{
	class PhysicsModule : public Module
	{
	public:
		virtual void setup() override
		{
			createProcessChain("Physics");
			reportSystem<PhysicsSystem>();
			registerComponentType<diviner::physics_component>();
			registerComponentType<diviner::rigidbody>();
			registerComponentType<identifier>();

			reportSystem<PhysXPhysicsSystem>();
			registerComponentType<physics_component>();
			registerComponentType<rigidbody>();
			registerComponentType<physics_enviroment>();
			registerComponentType<capsule_controller>();
		}

		virtual rsl::priority_type priority() override
		{
			return 20;
		}
	};
} // namespace rythe::physics
