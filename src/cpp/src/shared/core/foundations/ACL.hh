#pragma once

#include <unordered_map>
#include <variant>

namespace rx::space::core::foundations{
    enum PermissionBase{
        Any,
        Exact
    };

    using Permission = std::variant<PermissionBase>;

    using ACL = std::unordered_map<size_t, Permission>;

    namespace acl{
        /**
         * Check if the values larger than the
         * given index have any access control
         * rules attached to them or not.
         */
        bool isProtectedAt(const size_t, const ACL&);

        /**
         * Drop the uppermost scope of this
         * ACL and return the scope for the
         * remaining elements.
         */
        ACL nextScope(const ACL&);
    }
}