#pragma once

#include <memory>

namespace rx::space::core{

    /**
     * Holder for reactive values
     */
    class IValue{};

    using IValuePtr = std::shared_ptr<IValue>;
}