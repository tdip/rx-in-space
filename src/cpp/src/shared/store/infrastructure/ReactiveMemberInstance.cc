#include "store/infrastructure/ReactiveMemberInstance.hh"

namespace rx::space::store::infrastructure{

    ActiveMemberContext::ActiveMemberContext(
        const core::QueryArgs& query,
        const types::IReactiveQuerySpace& space,
        const types::IReactiveSpaceMemberPtr _activeMember,
        const std::function<void(core::ReactiveValueContextPtr)> action) : activeMember(_activeMember){

        types::MemberValue result = activeMember->query(space, query);

        if(std::holds_alternative<types::ReactiveMemberValueStream>(result)){
            const_cast<rx::composite_subscription&>(activeMemberSubscription) = std::get<types::ReactiveMemberValueStream>(result)
                .subscribe(action);
        }else if(std::holds_alternative<types::IReactiveSpaceMemberPtr>(result)){
            const_cast<std::unique_ptr<ReactiveMemberInstance>&>(activeMemberInstance) = std::make_unique<ReactiveMemberInstance>(
                query,
                std::get<types::IReactiveSpaceMemberPtr>(result),
                space);
            const_cast<rx::composite_subscription&>(activeMemberSubscription) = activeMemberInstance
                ->stream()
                .subscribe(action);
        }
    }

    ActiveMemberContext::~ActiveMemberContext(){
        activeMemberSubscription.unsubscribe();
    }

    ReactiveMemberInstance::ReactiveMemberInstance(
        const core::QueryArgs& query,
        types::IReactiveSpaceMemberPtr member,
        const types::IReactiveQuerySpacePtr space) :
            context(new ReactiveMemberInstanceContext{
                query,
                util::SimpleSubject<core::ReactiveValueContextPtr>(),
                space,
                nullptr
            }),
            wContext(context),
            onActiveMemberValue(
                [wContext = this->wContext](core::ReactiveValueContextPtr value){
                    ReactiveMemberInstance::onMemberInstanceValue(wContext, value);
                }){
            
            context->activeMemberContext = std::make_unique<ActiveMemberContext>(
                query,
                space,
                member,
                onActiveMemberValue);
        }

    const types::ReactiveMemberValueStream& ReactiveMemberInstance::stream() const{
        return context->subject.observable();
    }

    void ReactiveMemberInstance::setActiveMember(types::IReactiveSpaceMemberPtr member){
        context->activeMemberContext = std::make_unique<ActiveMemberContext>(
            context->query,
            context->space,
            member,
            onActiveMemberValue);
    }

    void ReactiveMemberInstance::onMemberInstanceValue(
        const ContextWPtr wContext,
        core::ReactiveValueContextPtr value){

        ContextPtr context = wContext.lock();

        if(context){
            context->subject.onNext(value);
        }
    }
}