#pragma once

#include <variant>

#include "rx.hh"

#include "core/Context.hh"

namespace rx::space::store{

    class IReactiveNodeStream{
        public:
        virtual const rx::observable<core::ContextPtr>& observable() const = 0;
    };

    using IReactiveNodeStreamPtr = std::shared_ptr<IReactiveNodeStream>;
}