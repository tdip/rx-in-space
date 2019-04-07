#pragma once

#include <memory>
#include <vector>

#include "rx.hh"

#include "core/QueryArgs.hh"
#include "core/QuerySet.hh"
#include "core/IValue.hh"

#include "store/IReactiveQuerySpace.hh"

namespace rx::space::store{

    class IReactiveNodeSubscription{
        public:
        virtual ~IReactiveNodeSubscription() = 0;
    };

    using IReactiveNodeSubscriptionPtr = std::unique_ptr<IReactiveNodeSubscription>;

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
        virtual IReactiveNodeSubscriptionPtr subscribe(IReactiveQuerySpace&, std::vector<rx::observer<core::IValue>>) = 0;
    };

    using IReactiveNodePtr = std::unique_ptr<IReactiveNode>;
}