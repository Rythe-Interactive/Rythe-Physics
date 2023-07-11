#pragma once
#include <core/core.hpp>

namespace rythe::physics
{
    struct physics_component;
    struct physics_enviroment;
    struct capsule_controller;

    template <class PhysxObject>
    class PhysxWrapperContainer
    {
    public:

        PhysxObject& createPhysxWrapper(physics_component& unregisteredPhysXWrapper);

        PhysxObject& createPhysxWrapper(physics_enviroment& unregisteredPhysXWrapper);

        PhysxObject& createPhysxWrapper(capsule_controller& unregisteredPhysXWrapper);

        void PopAndSwapRemoveWrapper(rsl::size_type id);

        pointer<PhysxObject> findWrapperWithID(rsl::size_type id);

        inline void ReleasePhysicsWrappers() { m_physxWrappers.clear(); }

        std::vector<PhysxObject>& getWrappers() { return m_physxWrappers; }

    private:

        PhysxObject& registerWrapperID(rsl::size_type& outID);

        sparse_set<rsl::size_type> m_wrapperIDSet;
        std::vector<PhysxObject> m_physxWrappers;

        rsl::size_type nextID = 0;
    };

}

