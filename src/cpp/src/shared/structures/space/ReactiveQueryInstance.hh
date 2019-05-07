#pragma once

#include "rx.hh"

#include "core/foundations/Key.hh"
#include "core/space/IReactiveSpace.hh"

namespace rx::space::structures{

    class ReactiveQueryInstance{
    public:
        const core::KeyPowerSet& query() const;

        rx::composite_subscription addMember(const core::ReactiveMemberValueStream&) const;

        rx::composite_subscription addSpace(const core::IReactiveQuerySpacePtr&) const;

    private:
        const core::KeyPowerSet _query;
    };
}