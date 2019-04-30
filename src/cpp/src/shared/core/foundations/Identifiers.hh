#pragma once

#include <stdint.h>
#include <variant>
#include <vector>

namespace rx::space::core{
    using SetIdentifier = std::vector<int64_t>;

    struct AllSets{};
    struct PowerSetIdentifier{
        std::unordered_map<int64_t, std::variant<AllSets, PowerSetIdentifier>> members;
    };



    namespace set_identifier{
        SetIdentifier nextScope(const SetIdentifier&);
        SetIdentifier intersect(const SetIdentifier&, const SetIdentifier&);
    }

    namespace power_set_identifier{
        bool inScope(const int64_t, const PowerSetIdentifier&);
        PowerSetIdentifier intersect(const PowerSetIdentifier&, const PowerSetIdentifier&);
    }
}