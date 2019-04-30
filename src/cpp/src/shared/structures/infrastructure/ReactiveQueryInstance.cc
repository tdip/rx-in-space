#include "store/infrastructure/ReactiveQueryInstance.hh"

namespace rx::space::store::infrastructure{

    std::unordered_map<Key, ReactiveMemberInstancePtr> queryMembers(
        const ReactiveQueryContextBasePtr& queryContext,
        std::vector<std::reference_wrapper<ReactiveMemberEntry>>& entries){

        std::unordered_map<Key, ReactiveMemberInstancePtr> result;
        result.reserve(entries.size());

        for(
            auto&& entry = entries.begin();
            entry != entries.end();
            entry++){

            auto&& value = entry->get();
            result.emplace(
                std::make_pair(
                    fromOutputSet(value.outputSet()),
                    ReactiveMemberInstance::create(queryContext, value.getMember())));
        }

        return result;
    }

    types::ReactiveMemberValueStream getAggregator(
        const ReactiveQueryContextBasePtr& queryContext,
        std::unordered_map<Key, ReactiveMemberInstancePtr>& queryMembers){

        std::vector<std::reference_wrapper<const types::ReactiveMemberValueStream>> values;

        for(
            auto&& entry = queryMembers.begin();
            entry != queryMembers.end();
            entry++){

            values.push_back(entry->second->stream());
        }

        return ReactiveQueryAggregator::aggregator(
            queryContext->query,
            values);
    }

    ReactiveQueryInstance::ReactiveQueryInstance(
        const ReactiveQueryContextBasePtr queryContext,
        std::vector<std::reference_wrapper<ReactiveMemberEntry>>& entries) :
            context(new ReactiveQueryInstanceContext{
                queryContext,
                types::ReactiveMemberValueSimpleSubject(),
                queryMembers(queryContext, entries),
                rx::composite_subscription{} }) {

        context->aggregatorSubscription = getAggregator(queryContext, context->members)
            .subscribe(
                [context = this->context](core::ReactiveValueContextPtr value){
                    context->subject.onNext(value);
                });
    }

    ReactiveQueryInstance::ReactiveQueryInstance(
        const core::Query& query,
        const types::IReactiveQuerySpacePtr& space,
        std::vector<std::reference_wrapper<ReactiveMemberEntry>>& entries) :
        ReactiveQueryInstance(
            std::shared_ptr<ReactiveQueryContextBase>(new ReactiveQueryContextBase{query, space}),
            entries) {}

    const types::ReactiveMemberValueStream& ReactiveQueryInstance::stream() const{
        return context->subject.observable();
    }

    ReactiveQueryInstance::~ReactiveQueryInstance(){
        context->aggregatorSubscription.unsubscribe();
    }
}