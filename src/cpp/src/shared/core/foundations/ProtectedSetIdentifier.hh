#pragma once

#include "core/foundations/ACL.hh"
#include "core/foundations/Identifiers.hh"

namespace rx::space::core::foundations{

    struct ProtectedSetIdentifier{
        SetIdentifier setId;
        ACL permissions;

        
    };

    namespace protected_set{
        bool inGroundScope(const ProtectedSetIdentifier&);

        ProtectedSetIdentifier nextScope(const ProtectedSetIdentifier& set);

        ProtectedSetIdentifier dropACLs(const ProtectedSetIdentifier&);
    }
}