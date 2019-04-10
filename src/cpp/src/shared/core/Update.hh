#pragma once

#include <variant>
#include <vector>

#include "rx.hh"

#include "core/Value.hh"
#include "core/OutputSet.hh"

namespace rx::space::core{

    struct SetValue{
        OutputSet output;
        rx::observable<ValuePtr> values;
    };

    using Update = std::variant<SetValue>;

    struct UpdateArgs{
        std::vector<Update> updates;
    };
}