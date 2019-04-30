#include "core/foundations/ACL.hh"

namespace rx::space::core::foundations::acl{

    bool isProtectedAt(const size_t i, const ACL& acl){

        for(
            auto&& kv = acl.begin();
            kv != acl.end();
            kv++){

            auto&& permission = kv->second;
            if(
                kv->first >= i
                && std::holds_alternative<PermissionBase>(permission)
                && std::get<PermissionBase>(permission) != PermissionBase::Any){

                return true;
            }
        }

        return false;
    }

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