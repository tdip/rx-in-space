#include "structures/space/ReactiveSpace.hh"

namespace rx::space::structures{

    ReactiveSpace::ReactiveSpace() : ReactiveSpace(ReactiveSpaceCollection()) {}

    ReactiveSpace::ReactiveSpace(ReactiveSpaceCollection&& initialMembers) :
        scope(std::nullopt),
        context(new ReactiveSpaceContext{
            initialMembers,
            ReactiveUpdateSubject()
        }) {}

    ReactiveSpace::ReactiveSpace(const core::SetIdentifier& _scope, const ContextPtr& _context) :
        scope(_scope),
        context(_context) {}

    void ReactiveSpace::notify(const ReactiveUpdates&) const{
    }

    ReactiveMemberValueStream ReactiveSpace::query(const core::PowerSetIdentifier& setId){

        ReactiveSpaceCollection& spaces = context->spaces;

        for(
            auto&& member = spaces.begin();
            member != spaces.end();
            member++){

            if(
                (!scope.has_value() || protected_set::isMember(scope.value(), setId))
                && 
            )
        }
    }

    std::optional<exceptions::UpdateException> ReactiveSpace::update(const ReactiveUpdates& deltas){

        std::unordered_map<int64_t, ReactiveUpdates> updates;

        /**
         * Determine the reactive member to which each of
         * the updates belongs to.
         */
        for(
            auto&& delta = deltas.begin();
            delta != deltas.end();
            delta++){

            const int64_t index = reactive_update::getScopedIndex(*delta);
            updates[index].emplace_back(*delta);
        }

        /**
         * Update the values of the reactive members.
         */
        ReactiveUpdates updateNotifications;
        for(
            auto&& kv = updates.begin();
            kv != updates.end();
            kv++){

            ReactiveSpaceCollection& spaces = context->spaces;

            if(spaces.find(kv->first) == spaces.end()){
                auto setId = foundations::protected_set::create(kv->first);
                spaces.emplace(
                    std::piecewise_construct,
                    std::forward_as_tuple(kv->first),
                    std::forward_as_tuple(setId));
            }

            ReactiveMember& member = spaces[kv->first];
            member.update(kv->second, updateNotifications);
        }

        return std::nullopt;
    }
}