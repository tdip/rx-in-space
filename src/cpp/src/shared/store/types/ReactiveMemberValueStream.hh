#pragma once

#include "rx.hh"

#include "core/ReactiveValueContext.hh"

namespace rx::space::store::types{

    using ReactiveMemberValueStream = rx::observable<core::ReactiveValueContext>;
}