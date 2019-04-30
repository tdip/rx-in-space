#include "store/infrastructure/Key.hh"

namespace rx::space::store::infrastructure{

    Key fromMemberProperties(const core::MemberProperties& properties){
        Key key;

        for(
            auto&& item = properties.begin();
            item != properties.end();
            item++){

            if(std::holds_alternative<std::string>(item->second)){
                key.emplace(item->first, std::get<std::string>(item->second));
            }
        }

        return std::move(key);
    }


    Key fromQuery(core::Query& args){
        return fromMemberProperties(args.query);
    }

    Key fromOutputSet(const core::OutputSet& outputSet){
        return fromMemberProperties(outputSet.properties);
    }
}