#include "adapters/ReactiveSpaceMember.hh"

#include "rxjs/NodeObservableWrap.hh"

#include "adapters/ValueScalar.hh"

namespace rx::space::platform::adapters{
    
    ReactiveSpaceMemberAdapter::ReactiveSpaceMemberAdapter(v8::Local<v8::Object> os) :
        observable(
            rx::platform::node::NodeObservableWrap::toCppObservable(os)
            | rx::map(ValueScalar::fromPlatform)
        ) {}

    store::types::MemberValue ReactiveSpaceMemberAdapter::query(
        const store::types::IReactiveQuerySpace&,
        const core::Query&){

        return store::types::ReactiveMemberValueStream(observable);
    }
}