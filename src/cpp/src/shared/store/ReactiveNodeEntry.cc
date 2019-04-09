#include "store/ReactiveNodeEntry.hh"

namespace rx::space::store{

    ReactiveNodeEntry::ReactiveNodeEntry(IReactiveQuerySpacePtr&& _space) :
        subject(
            [this]() mutable { activateSubscriptionToNode(); },
            [this]() mutable { unsubscribeNode(); }),
        space(std::move(_space)) {}

    void ReactiveNodeEntry::onNodeValue(core::IValuePtr){
        core::ContextPtr context = core::Context::create();
        subject.onNext(context);
    }

    void ReactiveNodeEntry::activateSubscriptionToNode(){
        if(!activeNode){
            return;
        }

        activeNodeSubscription = activeNode->subscribe(
            *space,
            [this](core::IValuePtr ctx){
                onNodeValue(ctx);
            });
    }

    void ReactiveNodeEntry::setNode(IReactiveNodePtr&& node){
        activeNode = std::move(node);
        if(unsubscribeNode()){
            activateSubscriptionToNode();
        }
    }

    bool ReactiveNodeEntry::unsubscribeNode(){
        activeNodeSubscription.unsubscribe();
        return subject.isActive();
    }

    ReactiveNodeInstancePtr ReactiveNodeEntry::activate(bool isWeak){

        return std::make_unique<ReactiveNodeInstance>(
            isWeak ? subject.observableWeak() : subject.observable());
    }
}