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

    std::optional<Update> ReactiveMember::update(const Update& update){
        const foundations::ProtectedSetIdentifier& set = std::get<0>(update);
        const Operation& op = std::get<1>(update);
        std::optional<Update> result = std::nullopt;

        // If the scope of the set is the 'ground scope', this
        // member will be directly replaced.
        if(foundations::protected_set::inGroundScope(set)){
            if(std::holds_alternative<SetReactiveSpace>(op)){
                _reactiveMember = std::get<SetReactiveSpace>(op).space;
            }else if(std::holds_alternative<DeleteValue>(op)){
                _reactiveMember = rx::empty<core::ReactiveValueContextPtr>();
            }

            result = update;
        }else{
            IReactiveSpacePtr member = tryGetSpace(_reactiveMember);

            if(!member){
                member = ReactiveSpace::create();
                result = update;
            }

            const ReactiveUpdates nextUpdates = { reactive_update::nextScope(update) };
            member->update(nextUpdates);
        }

        return std::move(result);
    }
}