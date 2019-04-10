#pragma once

#include <functional>
#include <memory>
#include <vector>

#include "rx.hh"

#include "core/OutputSet.hh"
#include "core/QueryArgs.hh"
#include "core/QuerySet.hh"
#include "core/Value.hh"

#include "store/IReactiveQuerySpace.hh"

namespace rx::space::store{

    using OnValueNext = std::function<void(core::ValuePtr)>;

    class IReactiveNode{
    public:
        /**
         * Property that declares the output set of this node. The
         * values written to the observers of the subscribe function
         * will be palced in the output set defined by this property.
         */
        virtual const core::OutputSet& output() const = 0;

        /**
         * This method is called whenever a query matches the output
         * sets of this node. It should trigger the node to emit
         * values into the output sets through the observers given
         * to it.
         * 
         * The return type is an indicator so that the node can known
         * when there are no more queries that match it's output set.
         * This value will get destroyed when such event happens.
         */
        virtual rx::composite_subscription subscribe(
            IReactiveQuerySpace&,
            OnValueNext&&) = 0;
    };

    using IReactiveNodePtr = std::unique_ptr<IReactiveNode>;
}