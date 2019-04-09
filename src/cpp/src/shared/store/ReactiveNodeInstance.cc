#include "store/ReactiveNodeInstance.hh"

namespace rx::space::store{
    ReactiveNodeInstance::ReactiveNodeInstance(const rx::observable<core::ContextPtr>& nodeSource) :
        nodeSubscription(
            nodeSource.subscribe([this](core::ContextPtr& value){ onValue(value); })),
        subject([](){}, [](){}) {}

    ReactiveNodeInstance::~ReactiveNodeInstance(){
        nodeSubscription.unsubscribe();
    }

    void ReactiveNodeInstance::onValue(core::ContextPtr& value){
        subject.onNext(value);
    }
}