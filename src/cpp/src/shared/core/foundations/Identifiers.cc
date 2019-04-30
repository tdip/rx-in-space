#include "core/foundations/Identifiers.hh"

namespace rx::space::core{
    namespace set_identifier{
        SetIdentifier nextScope(const SetIdentifier& id){
            SetIdentifier result;

            if(id.size() == 0){
                return result;
            }

            result.reserve(id.size() - 1);

            for(auto&& item = ++id.begin(); item != id.end(); item++){
                result.push_back(*item);
            }

            return result;
        }
    }

    namespace power_set_identifier{
        bool inScope(const int64_t scope, const PowerSetIdentifier& id){

            if(std::holds_alternative<SetIdentifier>(id)){
                const SetIdentifier& set = std::get<SetIdentifier>(id);
                return set.size() > 0 && set[0] == scope; 
            }
        }
    }
}