#include "store/infrastructure/ReactiveMemberInstance.hh"

namespace rx::space::store::infrastructure{

    ActiveMemberContext::ActiveMemberContext(
        const core::Query& query,
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
        const core::Query& query,
        types::IReactiveSpaceMemberPtr member,
        const types::IReactiveQuerySpacePtr space) :
        ReactiveMemberInstance(
            types::ReactiveContextTransform::identity(),
            query,
            member,
            space) {}

    ReactiveMemberInstance::ReactiveMemberInstance(
        const types::ReactiveContextTransformPtr contextMapper,
        const core::Query& query,
        types::IReactiveSpaceMemberPtr member,
        const types::IReactiveQuerySpacePtr space) :
            context(new ReactiveMemberInstanceContext{
                util::SimpleSubject<core::ReactiveValueContextPtr>(),
                space,
                contextMapper,
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

    void ReactiveMemberInstance::setActiveMember(
        const core::Query& query,
        types::IReactiveSpaceMemberPtr member){

        context->activeMemberContext = std::make_unique<ActiveMemberContext>(
            query,
            context->space,
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