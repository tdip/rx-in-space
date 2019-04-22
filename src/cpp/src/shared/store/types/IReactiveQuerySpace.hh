#pragma once

#include <memory>
#include <variant>

#include "store/types/ReactiveMemberValueStream.hh"

namespace rx::space::store::types{

    class IReactiveQuerySpace{
        public:
        virtual const ReactiveMemberValueStream query(const core::QueryArgs&) = 0;
    };

    using IReactiveQuerySpacePtr = std::shared_ptr<IReactiveQuerySpace>;
}
