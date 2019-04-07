#include "store/ReactiveNodeCollection.hh"

#include "store/ReactiveNodeStream.hh"

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

    IReactiveNodeStreamPtr ReactiveNodeCollection::query(core::QueryArgs&& query){

        std::vector<std::shared_ptr<ReactiveNode>> queryNodes;

        for(auto&& node = reactiveNodes.begin(); node != reactiveNodes.end(); node++){

            std::shared_ptr<ReactiveNode> entry = node->second.lock();
            if(entry && entry->matches(query.query)){
                queryNodes.push_back(entry);
            }
        }

        const QueryInstancePtr instance = std::make_shared<QueryInstance>(query, std::move(queryNodes));
        const Key key = fromQuery(query);
        reactiveQueries[key] = instance;
        return std::make_shared<ReactiveNodeStream>(instance);
    }
}