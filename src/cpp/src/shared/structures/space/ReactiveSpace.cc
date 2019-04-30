#include "structures/space/ReactiveSpace.hh"

namespace rx::space::structures{

    ReactiveSpace::ReactiveSpace() : ReactiveSpace(ReactiveSpaceCollection()) {}

    ReactiveSpace::ReactiveSpace(ReactiveSpaceCollection&& initialMembers) :
        scope(std::nullopt),
        context(new ReactiveSpaceContext{
            initialMembers,
            ReactiveUpdates()
        }) {}

    ReactiveSpace::ReactiveSpace(const core::SetIdentifier& _scope, const ContextPtr& _context) :
        scope(_scope),
        context(_context) {}

    ReactiveMemberValueStream ReactiveSpace::query(const core::PowerSetIdentifier& setId){

    }

    std::optional<exceptions::UpdateException> ReactiveSpace::update(const ReactiveUpdates& deltas){

    }
}