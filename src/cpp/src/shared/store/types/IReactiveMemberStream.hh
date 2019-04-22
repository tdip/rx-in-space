#pragma once

#include <variant>

#include "rx.hh"

#include "core/Context.hh"

namespace rx::space::store::types{

    class IReactiveMemberStream{
        public:
        virtual const rx::observable<core::ContextPtr>& observable() const = 0;
    };

    using IReactiveMemberStreamPtr = std::shared_ptr<IReactiveMemberStream>;
}