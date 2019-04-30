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

        std::unordered_map<int64_t, ReactiveUpdates> updates;

        for(
            auto&& delta = deltas.begin();
            delta != deltas.end();
            delta++){

            const int64_t index = reactive_update::getScopedIndex(*delta);
            updates[index].emplace_back(*delta);
        }
    }
}