#include "store/ReactiveNodeCollection.hh"

#include "store/NodeEntryQuerySpace.hh"

namespace rx::space::store{

    Key fromQuery(core::QueryArgs& args){
        Key key;
        const core::QuerySet& query = args.query;

        for(
            auto&& item = query.begin();
            item != query.end();
            item++){

            if(std::holds_alternative<std::string>(item->second)){
                key.emplace(item->first, std::get<std::string>(item->second));
            }
        }

        return std::move(key);
    }

    QueryContextPtr ReactiveNodeCollection::queryContext(
        bool isWeak,
        const core::QueryArgs& query) const{

        std::vector<ReactiveNodeInstancePtr> nodes;
        for(auto&& node = reactiveNodes.begin(); node != reactiveNodes.end(); node++){

            const ReactiveNodeEntry& entry = node->second;

            if(entry.matches(query)){
                nodes.push_back(entry.activate(isWeak));
            }
        }

        return QueryContext::create(std::move(nodes));
    }

    IReactiveNodeStreamPtr ReactiveNodeCollection::query(const core::QueryArgs& query){
        auto result = std::make_shared<ReactiveNodeStream>(query, queryContext(false, query));
        activeQueries.emplace_back(result);
        return result;
    }
}