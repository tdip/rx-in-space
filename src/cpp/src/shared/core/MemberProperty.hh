#pragma once

#include <map>
#include <string>
#include <variant>
#include <vector>

namespace rx::space::core{

    /**
     * The value of a property that identifies a member
     * of the space's power set.
     */
    using MemberPropertyValue = std::variant<std::string>;

    /**
     * A set of properites that identify members
     * of the space's power set.
     */
    using MemberProperties = std::map<std::string, MemberPropertyValue>;
}