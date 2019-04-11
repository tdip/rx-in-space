#pragma once

#include <memory>
#include <variant>
#include <vector>

#include "core/ValueAst.hh"

namespace rx::space::core{

    class IScalar{

    };

    using IScalarPtr = std::shared_ptr<IScalar>;

    /**
     * Holder for reactive values
     */
    using Value = ValueAst<IScalarPtr>;

    using ValuePtr = std::shared_ptr<Value>;
}