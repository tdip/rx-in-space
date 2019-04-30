#include "structures/space/ReactiveMember.hh"

#include "structures/space/ReactiveSpace.hh"

namespace rx::space::structures{

    using namespace core;

    const IReactiveSpacePtr tryGetSpace(const ReactiveMemberValue& value){
        if(!std::holds_alternative<IReactiveQuerySpacePtr>(value)){
            return nullptr;
        }

        const IReactiveQuerySpacePtr& ptr = std::get<IReactiveQuerySpacePtr>(value);
        return std::dynamic_pointer_cast<IReactiveSpace>(ptr);
    }

    ReactiveMember::ReactiveMember(
        const ProtectedSetIdentifier& __protectedSet) :
        _protectedSet(__protectedSet),
        _reactiveMember(rx::empty<ReactiveValueContextPtr>()){}

    const ProtectedSetIdentifier& ReactiveMember::protectedSet() const{
        return _protectedSet;
    }

    const ReactiveMemberValue& ReactiveMember::reactiveMember() const{
        return _reactiveMember;
    }

    void ReactiveMember::update(
        const ReactiveUpdates& updates,
        ReactiveUpdates& notifyUpdates){

        ReactiveUpdates nextUpdates;
        std::optional<Update> groundUpdate;

        // First apply updates to the ground scope if necessary
        for(
            auto&& update = updates.begin();
            update != updates.end();
            update++){

            const ProtectedSetIdentifier& set = update->setId;
            const Operation& op = update->operation;

            // If the scope of the set is the 'ground scope', this
            // member will be directly replaced.
            if(protected_set::inGroundScope(set)){
                updateGroundState(*update);
                groundUpdate.emplace(*update);
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
                _protectedSet = protected_set::dropACLs(_protectedSet);
                groundUpdate.emplace(Update{
                    _protectedSet,
                    SetReactiveSpace{ member }
                });
            }

            member->update(nextUpdates);
        }

        if(groundUpdate.has_value()){
            notifyUpdates.emplace_back(
                groundUpdate.value());
        }
    }

    void ReactiveMember::updateGroundState(const Update& update){

        const ProtectedSetIdentifier& set = update.setId;
        const Operation& op = update.operation;
        _protectedSet = set;

        if(std::holds_alternative<SetReactiveSpace>(op)){
            _reactiveMember = std::get<SetReactiveSpace>(op).space;
        }else if(std::holds_alternative<DeleteValue>(op)){
            _reactiveMember = rx::empty<core::ReactiveValueContextPtr>();
        }
    }
}