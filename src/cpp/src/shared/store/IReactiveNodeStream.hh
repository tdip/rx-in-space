#pragma once

#include "rx.hh"

#include "core/Context.hh"

namespace rx::space::store{
    using ReactiveNodeValue = std::shared_ptr<std::vector<core::ContextPtr>>;

    class IReactiveNodeStream{
        public:
        virtual const rx::observable<ReactiveNodeValue>& observable() const = 0;
    };

    using IReactiveNodeStreamPtr = std::shared_ptr<IReactiveNodeStream>;
}