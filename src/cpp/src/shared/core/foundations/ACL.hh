#pragma once

#include <unordered_map>

namespace rx::space::core::foundations{
    enum PermissionBase{
        Any,
        Exact
    };

    using Permission = std::variant<PermissionBase>;

    using ACL = std::unordered_map<size_t, Permission>;

    namespace acl{
        ACL nextScope(const ACL&);
    }
}