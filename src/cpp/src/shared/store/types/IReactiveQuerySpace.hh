#pragma once

#include <memory>
#include <variant>

#include "store/types/IReactiveMemberStream.hh"

namespace rx::space::store::types{

    class IReactiveQuerySpace{
        public:
        virtual IReactiveMemberStreamPtr query(const core::QueryArgs&) = 0;
    };

    using IReactiveQuerySpacePtr = std::unique_ptr<IReactiveQuerySpace>;
}
