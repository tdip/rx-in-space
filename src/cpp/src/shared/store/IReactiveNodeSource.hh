#pragma once

#include <memory>

#include "rx.hh"

#include "core/IValue.hh"

namespace rx::space::store{

    /**
     * Class that represents a source of
     * values from which a node draws new
     * values.
     * 
     * A source can also include custom
     * tear-down logic to release resources
     * once it is no longer needed.
     */
    class IReactiveNodeSource{
    public:
        virtual const rx::observable<core::IValuePtr>& observable() const = 0;
    };
}