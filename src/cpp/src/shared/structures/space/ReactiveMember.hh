#pragma once

#include <optional>

#include "core/foundations/ProtectedSetIdentifier.hh"
#include "core/space/IReactiveSpace.hh"

namespace rx::space::structures{
    using namespace core;

    using ReactiveMemberValue = std::variant<ReactiveMemberValueStream, IReactiveQuerySpacePtr>;

    /**
     * Helper class that serves as a storage cell for reactive
     * spaces inside another reactive space.
     */
    class ReactiveMember{
    public:
        ReactiveMember(const foundations::ProtectedSetIdentifier&, ReactiveMemberValue&);
        const foundations::ProtectedSetIdentifier& protectedSet() const;
        const ReactiveMemberValue& reactiveMember() const;
        std::optional<Update> update(const Update&);

    private:
        foundations::ProtectedSetIdentifier _protectedSet;
        ReactiveMemberValue& _reactiveMember;
    };
}