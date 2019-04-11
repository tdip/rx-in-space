#include "store/ReactiveNodeEntry.hh"

namespace rx::space::store{

    ReactiveNodeEntry::ReactiveNodeEntry(INodeReactiveQuerySpacePtr&& _space) :
        subject(
            [this]() mutable { activateSubscriptionToNode(); },
            [this]() mutable { unsubscribeNode(); }),
        space(std::move(_space)) {}

    void ReactiveNodeEntry::onNodeValue(core::ValuePtr value){
        core::ContextPtr context = core::Context::create(
            nullptr,
            value);
        subject.onNext(context);
    }

    void ReactiveNodeEntry::activateSubscriptionToNode(){
        if(!activeNode){
            return;
        }

        space->activate();

        activeNodeSubscription = activeNode->subscribe(
            *space,
            [this](core::ValuePtr ctx){
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
        space->deactivate();
        return subject.isActive();
    }

    ReactiveNodeInstancePtr ReactiveNodeEntry::activate(bool isWeak) const{

        return std::make_unique<ReactiveNodeInstance>(isWeak, nullptr);
    }
}