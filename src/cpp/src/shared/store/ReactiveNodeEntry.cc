#include "store/ReactiveNodeEntry.hh"

namespace rx::space::store{

    ReactiveNodeEntry::ReactiveNodeEntry(IReactiveQuerySpacePtr&& _space) :
        space(std::move(_space)),
        subscribe([this](const rx::subscriber<core::ContextPtr> &ss){ return this->onSubscribe(ss); }),
        observable(rx::create<core::ContextPtr>(subscribe)){}

    void ReactiveNodeEntry::onSubscribe(const rx::subscriber<core::ContextPtr>& ss){
        const long id = idCount++;
        auto disposeRef = subscribeToNode();

        ss.add([id, disposeRef, this]() mutable {
            subscriptions.erase(id);
            disposeRef.reset();
        });

        subscriptions.emplace(id, std::move(ss));
    }

    std::shared_ptr<ReactiveNodeEntryDispose> ReactiveNodeEntry::subscribeToNode(){
        // Try get a copy of the dispose handler of the node
        std::shared_ptr<ReactiveNodeEntryDispose> disposeRef = dispose.lock();

        // If the dispose handler returns null, it means the node is not
        // active. This will activate the node and create a dispose
        // handler.
        if(!disposeRef){
            activateSubscriptionToNode();
            disposeRef = std::make_shared<ReactiveNodeEntryDispose>(
                [this](){
                    unsubscribeNode();
                });

            // Store the dispose handler as a weak-ref, that way
            // it gets discarded when all subscribers get discarded.
            dispose = disposeRef;
        }

        return disposeRef;
    }

    void ReactiveNodeEntry::setNode(IReactiveNodePtr&& node){
        activeNode = std::move(node);
        if(unsubscribeNode()){
            activateSubscriptionToNode();
        }
    }

    bool ReactiveNodeEntry::unsubscribeNode(){
        activeNodeSubscription.unsubscribe();
        return !dispose.expired();
    }

    ReactiveNodeInstance ReactiveNodeEntry::activate(){

        return ReactiveNodeInstance(observable);
    }
}