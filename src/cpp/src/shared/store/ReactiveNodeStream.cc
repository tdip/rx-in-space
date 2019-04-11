#include "store/ReactiveNodeStream.hh"

#include "core/QueryArgs.hh"
#include "core/MergeStrategy.hh"

#include "store/IReactiveNodeStream.hh"

#include "util/operators.hh"

namespace rx::space::store{

    core::ContextPtr aggregateContext(
        const core::QueryArgs& query,
        const util::CombineLatestValues<core::ContextPtr> input){
    }

    ReactiveNodeStream::ReactiveNodeStream(
        const core::QueryArgs& _query,
        QueryContextPtr _queryInstance): 
        queryInstance(std::move(_queryInstance)),
        query(_query),
        sourcesSubscription(
            queryInstance->sources.subscribe(
                [this](QuerySources sources){

                })){}

    const rx::observable<core::ContextPtr>& ReactiveNodeStream::observable() const{
        return subject.observable();
    }

    void ReactiveNodeStream::onQuerySources(QuerySources sources){
        auto& queryArgs = query;
        rx::observable<core::ContextPtr> observable;
        
        if(std::holds_alternative<core::Aggregate>(queryArgs.mergeStrategy)){
            observable = util::combineLatest<core::ContextPtr>(*sources)
                | rx::operators::map([&queryArgs](util::CombineLatestValues<core::ContextPtr> value){ return aggregateContext(queryArgs, value); });
        }else{
            observable = util::merge<core::ContextPtr>(*sources);
        }

        valuesSubscription.unsubscribe();
        valuesSubscription = observable.subscribe(subject.onNext);
    }
}