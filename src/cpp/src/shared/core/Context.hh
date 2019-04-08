#pragma once

#include <memory>

namespace rx::space::core{

    /**
     * Type referring to value container that
     * warps reactive values so different types
     * can be used within the same reactive
     * space.
     */
    class Context{};

    using ContextPtr = std::shared_ptr<Context>;
}