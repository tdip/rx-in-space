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

    QueryContext ReactiveNodeCollection::queryContext(core::QueryArgs& query){

        QueryContext context;
        for(auto&& node = reactiveNodes.begin(); node != reactiveNodes.end(); node++){

            ReactiveNodeEntry& entry = node->second;

            if(entry.matches(query)){
                context.addNodeInstance(entry.activate());
            }
        }

        return context;
    }
}