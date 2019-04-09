#include "store/ReactiveNodeInstance.hh"

namespace rx::space::store{
    ReactiveNodeInstance::ReactiveNodeInstance(
        rx::observable<core::ContextPtr>&& nodeSource):
        subject([](){}, [](){}),
        nodeSubscription(
            nodeSource.subscribe(
                [this](core::ContextPtr& p){ onNext(p); })){}

    ReactiveNodeInstance::~ReactiveNodeInstance(){
        // Unsubscribe from the source since this node instance is
        // no longer needed
        nodeSubscription.unsubscribe();
    }

    void ReactiveNodeInstance::onNext(core::ContextPtr& value){
        subject.onNext(value);
    }

    rx::observable<core::ContextPtr> ReactiveNodeInstance::observable(){
        return subject.observable();
    }
}