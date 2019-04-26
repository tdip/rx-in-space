#pragma once

#include <memory>
#include <variant>
#include <vector>

#include "core/IScalar.hh"
#include "core/ValueAst.hh"

namespace rx::space::core{

    /**
     * Holder for reactive values
     */
    using Value = ValueAst<IScalarPtr>;

    using ValuePtr = std::shared_ptr<Value>;

    template<typename ...Args>
    ValuePtr createValue(Args&& ...args){
        return std::make_shared<Value>(
            std::forward<Args>(args)...);
    }
}