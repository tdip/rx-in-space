#pragma once

#include <optional>

#include "core/space/IReactiveSpace.hh"

#include "util/SimpleSubject.hh"

namespace rx::space::structures{

    typedef util::SimpleSubject<core::ReactiveValueContextPtr> ReactiveMemberSubject;

    /**
     * Helper class that serves as a storage cell for reactive
     * spaces inside another reactive space.
     */
    class ReactiveMember{
    public:
        ReactiveMember();
        ReactiveMember(const core::ReactiveMemberValueStream&);
        const core::ReactiveMemberValueStream& reactiveMember() const;
        void update(const core::ReactiveMemberValueStream&);

    private:
        const ReactiveMemberSubject _reactiveMember;
        rx::composite_subscription _reactiveMemberSubscription;
    };
}