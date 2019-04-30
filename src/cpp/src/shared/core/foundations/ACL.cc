#include "core/foundations/ACL.hh"

namespace rx::space::core::foundations::acl{
    ACL nextScope(const ACL& other){
        ACL result;

        for(auto&& permission = other.begin(); permission != other.end(); permission++){
            const size_t key = permission->first - 1;

            if(key >= 0){
                result[key] = permission->second;
            }
        }

        return result;
    }
}