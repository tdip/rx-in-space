#pragma once

#include <memory>
#include <variant>

#include "core/Query.hh"

#include "store/types/ReactiveMemberValueStream.hh"

namespace rx::space::store::types{

    class IReactiveQuerySpace{
        public:
        virtual const ReactiveMemberValueStream query(const core::Query&) = 0;
    };

    using IReactiveQuerySpacePtr = std::shared_ptr<IReactiveQuerySpace>;
}
