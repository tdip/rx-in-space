#pragma once

#include <memory>

#include "store/IReactiveQuerySpace.hh"

namespace rx::space::store{
    class INodeReactiveQuerySpace: public IReactiveQuerySpace{
        public:
        virtual void activate() = 0;
        virtual void deactivate() = 0;
    };

    using INodeReactiveQuerySpacePtr = std::unique_ptr<INodeReactiveQuerySpace>;
}