#include "store/infrastructure/ReactiveMemberInstance.hh"

namespace rx::space::store::infrastructure{

    ActiveMemberContext::ActiveMemberContext(
        const ReactiveQueryContextBasePtr& queryContext,
        const types::IReactiveSpaceMemberPtr _activeMember,
        const std::function<void(core::ReactiveValueContextPtr)> action) : activeMember(_activeMember){

        types::MemberValue result = activeMember->query(
            *queryContext->space,
            queryContext->query);

        if(std::holds_alternative<types::ReactiveMemberValueStream>(result)){
            const_cast<rx::composite_subscription&>(activeMemberSubscription) = std::get<types::ReactiveMemberValueStream>(result)
                .subscribe(action);
        }else if(std::holds_alternative<types::IReactiveSpaceMemberPtr>(result)){
            const_cast<std::unique_ptr<ReactiveMemberInstance>&>(activeMemberInstance) = std::make_unique<ReactiveMemberInstance>(
                queryContext,
                std::get<types::IReactiveSpaceMemberPtr>(result));
            const_cast<rx::composite_subscription&>(activeMemberSubscription) = activeMemberInstance
                ->stream()
                .subscribe(action);
        }
    }

    ActiveMemberContext::~ActiveMemberContext(){
        activeMemberSubscription.unsubscribe();
    }

    ReactiveMemberInstance::ReactiveMemberInstance(
        const ReactiveQueryContextBasePtr& queryContext,
        types::IReactiveSpaceMemberPtr member) :
        ReactiveMemberInstance(
            queryContext,
            types::ReactiveContextTransform::identity(),
            member) {}

    ReactiveMemberInstance::ReactiveMemberInstance(
        const ReactiveQueryContextBasePtr& queryContext,
        const types::ReactiveContextTransformPtr contextMapper,
        types::IReactiveSpaceMemberPtr member) :
            context(new ReactiveMemberInstanceContext{
                queryContext,
                util::SimpleSubject<core::ReactiveValueContextPtr>(),
                contextMapper,
                nullptr
            }),
            wContext(context),
            onActiveMemberValue(
                [wContext = this->wContext](core::ReactiveValueContextPtr value){
                    ReactiveMemberInstance::onMemberInstanceValue(wContext, value);
                }){
            
            context->activeMemberContext = std::make_unique<ActiveMemberContext>(
                queryContext,
                member,
                onActiveMemberValue);
        }

    const types::ReactiveMemberValueStream& ReactiveMemberInstance::stream() const{
        return context->subject.observable();
    }

    void ReactiveMemberInstance::setActiveMember(
        types::IReactiveSpaceMemberPtr member){

        context->activeMemberContext = std::make_unique<ActiveMemberContext>(
            context->queryContext->query,
            context->queryContext->space,
            member,
            onActiveMemberValue);
    }

    void ReactiveMemberInstance::onMemberInstanceValue(
        const ContextWPtr wContext,
        core::ReactiveValueContextPtr value){

        ContextPtr context = wContext.lock();

        if(context){
            // Todo: add context of current member
            context->subject.onNext(value);
        }
    }
}