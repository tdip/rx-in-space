#include "store/ReactiveNodeInstance.hh"

namespace rx::space::store{

    void onNext(
        const std::shared_ptr<ReactiveNodeInstanceContext> context,
        core::ContextPtr& value){

        context->subject.onNext(value);
    }

    ReactiveNodeInstance::ReactiveNodeInstance(
        const bool isWeak,
        const std::shared_ptr<ReactiveNodeContextBase> baseContext):
        context(new ReactiveNodeInstanceContext{
            baseContext,
            ReactiveNodeEntrySubject([](){}, [](){})}) {

            auto ctx = context;
            context->nodeSubscription = (isWeak ?
                baseContext->subject.observableWeak() :
                baseContext->subject.observable())
                .subscribe([ctx](core::ContextPtr value){ onNext(ctx, value); });
        }

    ReactiveNodeInstance::~ReactiveNodeInstance(){
        // Unsubscribe from the source since this node instance is
        // no longer needed
        context->nodeSubscription.unsubscribe();
    }

    const rx::observable<core::ContextPtr> ReactiveNodeInstance::observable() const{
        return context->subject.observable();
    }
}