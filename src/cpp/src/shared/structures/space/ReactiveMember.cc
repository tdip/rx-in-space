#include "structures/space/ReactiveMember.hh"

#include "structures/space/ReactiveSpace.hh"

namespace rx::space::structures{

    using namespace core;

    ReactiveMember::ReactiveMember(): ReactiveMember(rx::empty<ReactiveValueContextPtr>()) {}

    ReactiveMember::ReactiveMember(const core::ReactiveMemberValueStream& __reactiveMember) :
        _reactiveMember(ReactiveMemberSubject()),
        _reactiveMemberSubscription(
            _reactiveMember.subscribeTo(__reactiveMember)) {}

    const core::ReactiveMemberValueStream& ReactiveMember::reactiveMember() const{
        return _reactiveMember.observable();
    }

    void ReactiveMember::update(const core::ReactiveMemberValueStream& os){
        _reactiveMemberSubscription.unsubscribe();
        _reactiveMemberSubscription = _reactiveMember.subscribeTo(os);
    }
}