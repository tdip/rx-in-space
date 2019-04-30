#include "structures/space/ReactiveMember.hh"

#include "structures/space/ReactiveSpace.hh"

namespace rx::space::structures{

    IReactiveSpacePtr tryGetSpace(const ReactiveMemberValue& value){
        if(!std::holds_alternative<IReactiveQuerySpacePtr>(value)){
            return nullptr;
        }

        return std::dynamic_pointer_cast<IReactiveSpace>(std::get<IReactiveQuerySpacePtr>(value));
    }

    ReactiveMember::ReactiveMember(
        const foundations::ProtectedSetIdentifier& __protectedSet,
        ReactiveMemberValue& __reactiveMember) :
        _protectedSet(__protectedSet),
        _reactiveMember(__reactiveMember){}

    const foundations::ProtectedSetIdentifier& ReactiveMember::protectedSet() const{
        return _protectedSet;
    }

    const ReactiveMemberValue& ReactiveMember::reactiveMember() const{
        return _reactiveMember;
    }

    ReactiveUpdates ReactiveMember::update(const ReactiveUpdates& updates){

        ReactiveUpdates nextUpdates;
        std::optional<Update> groundUpdate;

        // First apply updates to the ground scope if necessary
        for(
            auto&& update = updates.begin();
            update != updates.end();
            update++){

            const foundations::ProtectedSetIdentifier& set = std::get<0>(*update);
            const Operation& op = std::get<1>(*update);

            // If the scope of the set is the 'ground scope', this
            // member will be directly replaced.
            if(foundations::protected_set::inGroundScope(set)){
                updateGroundState(*update);
                groundUpdate = *update;
            }else{
                nextUpdates.emplace_back(*update);
            }
        }

        /**
         * Forward updates to child nodes if necessary
         */
        if(nextUpdates.size() > 0){
            IReactiveSpacePtr member = tryGetSpace(_reactiveMember);

            if(!member){
                member = ReactiveSpace::create();
                _protectedSet = foundations::protected_set::dropACLs(_protectedSet);
                groundUpdate = {
                    _protectedSet,
                    core::SetReactiveSpace{ member }
                };
            }

            member->update(nextUpdates);
        }

        if(groundUpdate.has_value()){
            return { groundUpdate.value() };
        }else{
            return {};
        }
    }

    void ReactiveMember::updateGroundState(const Update& update){

        const foundations::ProtectedSetIdentifier& set = std::get<0>(update);
        const Operation& op = std::get<1>(update);
        _protectedSet = set;

        if(std::holds_alternative<SetReactiveSpace>(op)){
            _reactiveMember = std::get<SetReactiveSpace>(op).space;
        }else if(std::holds_alternative<DeleteValue>(op)){
            _reactiveMember = rx::empty<core::ReactiveValueContextPtr>();
        }
    }
}