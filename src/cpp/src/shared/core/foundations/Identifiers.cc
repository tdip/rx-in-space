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

        SetIdentifier intersect(const SetIdentifier& s1, const SetIdentifier& s2){

        }
    }

    namespace power_set_identifier{
        bool inScope(const int64_t scope, const PowerSetIdentifier& id){
            return id.members.find(scope) != id.members.end();
        }

        PowerSetIdentifier intersect(
            const PowerSetIdentifier& s1,
            const PowerSetIdentifier& s2){
        }
    }
}