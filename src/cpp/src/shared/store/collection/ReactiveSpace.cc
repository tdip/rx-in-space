#include "store/collection/ReactiveSpace.hh"

namespace rx::space::store::collection{

    ReactiveMemberValueStream ReactiveSpace::query(const core::Query& query){
        std::vector<std::reference_wrapper<ReactiveMemberEntry>> entries;
        auto&& activeQueries = context->activeQueries;
        auto&& members = context->members;

        for(
            auto&& member = members.begin();
            member != members.end();
            member++){

            if(member->second.matches(query)){
                entries.push_back(member->second);
            }
        }

        std::shared_ptr<ReactiveQueryInstance> queryInstance = ReactiveQueryInstance::create(
            query,
            getQuerySubspace(query),
            entries);
        activeQueries.push_back(queryInstance);

        return rx::create<core::ReactiveValueContextPtr>(
            [queryInstance]
            (rx::subscriber<core::ReactiveValueContextPtr> subject){
                subject.add([queryInstance](){});
                subject.add(queryInstance->stream().subscribe(subject));
            });
    }

    void ReactiveSpace::update(const core::OutputSet& output, const types::IReactiveSpaceMemberPtr& member){
        Key key = fromOutputSet(output);
        auto&& elements = context->members;
        
        if(elements.find(key) != elements.end()){
            elements.erase(key);
        }

        elements.emplace(
            std::piecewise_construct,
            std::forward_as_tuple(key),
            std::forward_as_tuple(output, member));
    }
}