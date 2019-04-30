#include "core/foundations/ProtectedSetIdentifier.hh"

namespace rx::space::core::foundations::protected_set{

    bool inGroundScope(const ProtectedSetIdentifier& set){
        return set.setId.size() == 1;
    }

    ProtectedSetIdentifier nextScope(const ProtectedSetIdentifier& set){
        return ProtectedSetIdentifier{
            set_identifier::nextScope(set.setId),
            acl::nextScope(set.permissions)
        };
    }

    ProtectedSetIdentifier dropACLs(const ProtectedSetIdentifier& acls){
        return {
            acls.setId,
            std::unordered_map<size_t, Permission>()  
        };
    }
}