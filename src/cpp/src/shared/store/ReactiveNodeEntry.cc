#include "store/ReactiveNodeEntry.hh"

#include <cassert>

namespace rx::space::store{

    void ReactiveNodeEntry::activateSubscriptionToNode(const ContextWPtr wContext){

        auto context = wContext.lock();
        assert(context);

        auto& activeNode = context->activeNode;
        if(!context->activeNode){
            return;
        }

        context->space->activate();
        context->activeNodeSubscription = activeNode->subscribe(
            *context->space,
            [wContext](core::ValuePtr value){
                onNodeValue(wContext, value);
            });
    }

    ReactiveNodeEntry::~ReactiveNodeEntry(){
        unsubscribeNode(context);
    }

    ReactiveNodeEntry::ReactiveNodeEntry(INodeReactiveQuerySpacePtr&& _space) :
        context(new ReactiveNodeEntryContext{
            ReactiveNodeContextBase{ core::OutputSet(), ReactiveNodeEntrySubject(nullptr) },
            std::move(_space),
            rx::composite_subscription(),
            nullptr
        }) {
            ContextWPtr wContext = context;
            const_cast<ReactiveNodeEntrySubject&>(context->subject) = ReactiveNodeEntrySubject(
                [wContext]() mutable { activateSubscriptionToNode(wContext); },
                [wContext]() mutable { unsubscribeNode(wContext); });
        }

    void ReactiveNodeEntry::onNodeValue(ContextWPtr wContext, core::ValuePtr value){
        auto context = wContext.lock();
        assert(context);

        core::ContextPtr result = core::Context::create(
            nullptr,
            value);
        context->subject.onNext(result);
    }

    void ReactiveNodeEntry::setNode(IReactiveNodePtr&& node) const{
        context->activeNode = std::move(node);
        if(unsubscribeNode(context)){
            activateSubscriptionToNode(context);
        }
    }

    bool ReactiveNodeEntry::unsubscribeNode(ContextWPtr wContext){
        auto context = wContext.lock();
        assert(context);

        context->activeNodeSubscription.unsubscribe();
        context->space->deactivate();
        return context->subject.isActive();
    }

    ReactiveNodeInstancePtr ReactiveNodeEntry::activate(bool isWeak) const{
        return std::make_unique<ReactiveNodeInstance>(isWeak, context);
    }
}