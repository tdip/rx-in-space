#pragma once

#include <memory>

#include "core/ValueAst.hh"

namespace rx::space::core{

    class IValuePropsEntry{};

    using IValuePropsEntryPtr = std::shared_ptr<IValuePropsEntry>;

    using ValueProps = ValueAst<IValuePropsEntryPtr>;

    class Context;

    using ContextPtr = std::shared_ptr<Context>;

    /**
     * Type referring to value container that
     * warps reactive values so different types
     * can be used within the same reactive
     * space.
     */
    class Context{
        public:
        static ContextPtr create();

        const ValueProps& properties() const;
    };
}