#include "adapters/ReactiveSpaceMember.hh"

#include "rxjs/rxjs.hh"

#include "adapters/core.hh"

namespace rx::space::platform::adapters{
    
    ReactiveSpaceMemberAdapter::ReactiveSpaceMemberAdapter(
        rx::observable<v8::Local<v8::Value>> os) :
        observable(
            os
            | rx::map(ReactiveValueContext::fromPlatform)) {}

    store::types::MemberValue ReactiveSpaceMemberAdapter::query(
        const store::types::IReactiveQuerySpace&,
        const core::Query&){

        store::types::ReactiveMemberValueStream res = store::types::ReactiveMemberValueStream(observable);
        return std::move(res);
    }

    static std::optional<store::types::IReactiveSpaceMemberPtr> create(
        v8::Local<v8::Value> observable){

        auto os = rx::platform::node::NodeObservableWrap::toCppObservable(observable);

        if(os.has_value()){
            return std::make_shared<ReactiveSpaceMemberAdapter>(
                os.value());
        }

        return std::nullopt;
    }
}