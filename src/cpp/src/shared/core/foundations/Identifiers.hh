#pragma once

#include <stdint.h>
#include <variant>
#include <vector>

namespace rx::space::core{
    using SetIdentifier = std::vector<int64_t>;
    using PowerSetIdentifier = std::variant<SetIdentifier>;

    namespace set_identifier{
        SetIdentifier nextScope(const SetIdentifier&);
    }

    namespace power_set_identifier{
        bool inScope(const int64_t, const PowerSetIdentifier&);
    }
}