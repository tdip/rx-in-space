#include "store/ReactiveNodeStream.hh"

#include <optional>
#include <set>

#include "core/QueryArgs.hh"
#include "core/MergeStrategy.hh"

#include "store/IReactiveNodeStream.hh"

#include "util/operators.hh"

namespace rx::space::store{

    using PropertyGroup = std::set<std::tuple<std::string, core::OutputSetPredicate>>;

    std::optional<PropertyGroup> getProperties(
        std::vector<std::string>& keys,
        core::OutputSet& output){

        PropertyGroup result;
        auto& predicates = output.predicates;

        for(
            auto&& key = keys.begin();
            key != keys.end();
            key++){
            
            auto value = predicates.find(*key);
            if(value == predicates.end()){
                return std::nullopt;
            }

            result.emplace(*key, *value);
        }

        return result;
    }

    rx::observable<core::ContextPtr> aggregateQuery(
        core::Aggregate& agregate,
        QuerySources& sources){
        
        std::unordered_map<PropertyGroup, rx::observable<core::ContextPtr>&> groups();
        std::vector<rx::observable<core::ContextPtr>> sourceObservables;

        for(

        )
    }

    core::ContextPtr aggregateContext(
        const core::QueryArgs& query,
        const util::CombineLatestValues<core::ContextPtr> input){
    }

    ReactiveNodeStream::ReactiveNodeStream(
        const core::QueryArgs& _inputQuery,
        QueryContextPtr&& _queryInstance): 
        inputQuery(_inputQuery),
        queryInstance(std::move(_queryInstance)),
        sourcesSubscription(
            queryInstance->sources.subscribe(
                [this](QuerySources sources){

                })){}

    ReactiveNodeStream::~ReactiveNodeStream(){
        sourcesSubscription.unsubscribe();
        valuesSubscription.unsubscribe();
    }

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