#pragma once

#include <memory>

#include "core/Value.hh"
#include "core/ValueAst.hh"

namespace rx::space::core{

    class IValuePropsEntry{};

    using IValuePropsEntryPtr = std::shared_ptr<IValuePropsEntry>;

    using ValueProps = ValueAst<IValuePropsEntryPtr>;

    using ValuePropsPtr = std::shared_ptr<ValueProps>;

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
        Context(ValuePropsPtr __properties, ValuePtr __value):
            _properties(__properties),
            _value(__value) {}

        static ContextPtr create(ValuePropsPtr, ValuePtr);

        static ContextPtr merge(std::vector<ContextPtr>);

        const ValuePropsPtr properties() const { return _properties; }
        const ValuePtr value() const { return _value; }

        private:
        const ValuePropsPtr _properties;
        const ValuePtr _value;
    };
}