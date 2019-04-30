#pragma once

#include "core/foundations/ACL.hh"
#include "core/foundations/Identifiers.hh"

namespace rx::space::core::foundations{

    /**
     * Identifier of a set of reactive
     * objects whoose access is restricted
     * by the given ACL
     */
    struct ProtectedSetIdentifier{
        SetIdentifier setId;
        ACL permissions;
    };

    namespace protected_set{
        ProtectedSetIdentifier dropACLs(const ProtectedSetIdentifier&);
        int64_t getScopedIndex(const ProtectedSetIdentifier&);
        bool inGroundScope(const ProtectedSetIdentifier&);
        bool isMember(const ProtectedSetIdentifier&, const PowerSetIdentifier&);
        ProtectedSetIdentifier nextScope(const ProtectedSetIdentifier& set);
    }
}