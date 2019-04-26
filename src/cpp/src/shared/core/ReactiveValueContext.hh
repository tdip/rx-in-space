#pragma once

#include <memory>

#include "core/Value.hh"
#include "core/ValueAst.hh"

namespace rx::space::core{

    class IValuePropsEntry{};

    using IValuePropsEntryPtr = std::shared_ptr<IValuePropsEntry>;

    using ValueProps = ValueAst<IValuePropsEntryPtr>;

    using ValuePropsPtr = std::shared_ptr<ValueProps>;

    class ReactiveValueContext;

    using ReactiveValueContextPtr = std::shared_ptr<ReactiveValueContext>;

    /**
     * Type referring to value container that
     * warps reactive values so different types
     * can be used within the same reactive
     * space.
     */
    class ReactiveValueContext{
        public:
        ReactiveValueContext(ValuePropsPtr __properties, ValuePtr __value);

        ReactiveValueContext(core::IScalarPtr&);

        template<typename ...Args>
        static ReactiveValueContextPtr create(Args&& ...args){
            return std::make_shared<ReactiveValueContext>(
                std::forward<Args>(args)...);
        }

        static ReactiveValueContextPtr merge(std::vector<ReactiveValueContextPtr>);

        const ValuePropsPtr properties() const { return _properties; }
        const ValuePtr value() const { return _value; }

        private:
        const ValuePropsPtr _properties;
        const ValuePtr _value;
    };
}