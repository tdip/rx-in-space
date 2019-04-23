#pragma once

#include <memory>

#include "core/Query.hh"

#include "store/types/IReactiveQuerySpace.hh"

namespace rx::space::store::infrastructure{
    struct ReactiveQueryContextBase{
        const core::Query query;
        const types::IReactiveQuerySpacePtr space;
    };

    using ReactiveQueryContextBasePtr = std::shared_ptr<ReactiveQueryContextBase>;
}