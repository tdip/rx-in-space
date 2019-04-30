#pragma once

#include <optional>

#include "core/foundations/Identifiers.hh"
#include "core/foundations/ProtectedSetIdentifier.hh"
#include "core/space/IReactiveSpace.hh"

namespace rx::space::structures{

    using ReactiveMemberValue = std::variant<core::ReactiveMemberValueStream, core::IReactiveQuerySpacePtr>;

    /**
     * Helper class that serves as a storage cell for reactive
     * spaces inside another reactive space.
     */
    class ReactiveMember{
    public:
        ReactiveMember(const core::ProtectedSetIdentifier&);
        const core::ProtectedSetIdentifier& protectedSet() const;
        const ReactiveMemberValue& reactiveMember() const;
        void update(const ReactiveUpdates&, ReactiveUpdates&);

    private:
        core::ProtectedSetIdentifier _protectedSet;
        ReactiveMemberValue _reactiveMember;

        void updateGroundState(const Update&);
    };
}