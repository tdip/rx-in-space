#pragma once

#include <string>
#include <variant>
#include <vector>

namespace rx::space::merge{

    enum MergeStrategyBase{
        Sequence,
        Concat
    };

    struct Aggregate{
        std::vector<std::string> groupKeys;
    };

    using MergeStrategy = std::variant<MergeStrategyBase, Aggregate>; 
}