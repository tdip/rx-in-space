#include "rx.hh"

#include "rx.hh"

#include "core/Context.hh"

namespace rx::space::store{
    class IReactiveNodeStream{
        virtual rx::observable<core::Context>& observable() = 0;
    };

    using IReactiveNodeStreamPtr = std::shared_ptr<IReactiveNodeStream>;
}