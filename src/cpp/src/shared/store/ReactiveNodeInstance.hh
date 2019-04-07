#pragma once

#include "rx.hh"

#include "core/Context.hh"

namespace rx::space::store{
    class ReactiveNodeInstance{
    public:
        ReactiveNodeInstance(const rx::observable<core::Context>&) {}
    };
}