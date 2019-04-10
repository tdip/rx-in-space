#pragma once

#include <memory>

#include "store/IReactiveNodeStream.hh"

namespace rx::space::store{
    class IReactiveQuerySpace{
        public:
        virtual IReactiveNodeStreamPtr query(const core::QueryArgs&) = 0;
    };

    using IReactiveQuerySpacePtr = std::unique_ptr<IReactiveQuerySpace>;
}
