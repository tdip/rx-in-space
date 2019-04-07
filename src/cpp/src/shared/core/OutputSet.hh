#pragma once

#include <string>
#include <variant>
#include <vector>

namespace rx::space::core{
    enum FieldPredicateType{
        Required,
        Optional
    };

    struct FieldPredicate{
        const FieldPredicateType type;
        const std::string field;
    };

    using OutputSetPredicate = std::variant<FieldPredicate>;

    using OutputSet = std::vector<std::pair<std::string, OutputSetPredicate>>;
}