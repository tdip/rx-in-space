#pragma once

#include <map>
#include <string>
#include <variant>
#include <vector>

#include "core/MemberProperty.hh"

namespace rx::space::core{

    /**
     * Indicates that all items of the set are accessible
     * as long as one of the keys is valid.
     */
    enum BaseSelector{
        All
    };

    using OutputSetSelector = std::variant<BaseSelector, std::vector<std::string>>;

    /**
     * Describes the set on which values of the reactive space
     * will be located. Additionally it specifies the
     * conditions under which the items of said set are
     * accesible.
     */
    struct OutputSet{
        MemberProperties properties;
        std::vector<OutputSetSelector> selectors;

        // bool matches(const QuerySet&) const;
    };
}