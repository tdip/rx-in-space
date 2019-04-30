#include "core/foundations/ProtectedSetIdentifier.hh"

namespace rx::space::core::protected_set{

    ProtectedSetIdentifier create(const int64_t address){
        return ProtectedSetIdentifier{
            std::vector<int64_t>{ address },
            std::unordered_map<size_t, Permission>()
        };
    }

    ProtectedSetIdentifier dropACLs(const ProtectedSetIdentifier& acls){
        return {
            acls.setId,
            std::unordered_map<size_t, Permission>()  
        };
    }

    int64_t getScopedIndex(const ProtectedSetIdentifier& set){
        return set.setId[0];
    }

    bool inGroundScope(const ProtectedSetIdentifier& set){
        return set.setId.size() == 1;
    }

    bool isMember(
        const ProtectedSetIdentifier& set,
        const SetIdentifier& pSet){

        if(set.setId.size() < pSet.size()){
            return false;
        }

        const SetIdentifier& sSet = set.setId;

        for(int i = 0; i < pSet.size(); i++){
            if(pSet[i] != sSet[i]){
                return false;
            }
        }

        return !acl::isProtectedAt(pSet.size(), set.permissions);
    }

    bool isMember(
        const ProtectedSetIdentifier& set,
        const PowerSetIdentifier& pSet){

        if(std::holds_alternative<SetIdentifier>(pSet)){
            return isMember(set, std::get<SetIdentifier>(pSet));
        }

        return false;
    }

    ProtectedSetIdentifier nextScope(const ProtectedSetIdentifier& set){
        return ProtectedSetIdentifier{
            set_identifier::nextScope(set.setId),
            acl::nextScope(set.permissions)
        };
    }


}