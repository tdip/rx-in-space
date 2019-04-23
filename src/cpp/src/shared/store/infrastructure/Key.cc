#include "store/infrastructure/Key.hh"

namespace rx::space::store::infrastructure{

    Key fromQuery(core::Query& args){
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
}