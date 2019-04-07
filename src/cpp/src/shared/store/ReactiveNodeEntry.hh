#pragma once

#include <memory>

#include "rx.hh"

#include "core/Context.hh"
#include "core/QueryArgs.hh"

#include "store/IReactiveNode.hh"
#include "store/ReactiveNodeInstance.hh"

namespace rx::space::store{

    /**
     * Wrapper class to store reactive nodes
     * in the reactive space. This class is also
     * in charge of activating the node when
     * requested and de-activate it when no
     * query is using it.
     */
    class ReactiveNodeEntry{
    public:
        ReactiveNodeEntry();

        /**
         * Activate the node in order to subscribe to
         * it's output sets. When all instances of
         * the node are discarded, the node will
         * be deactivated to save resources.
         */
        ReactiveNodeInstance activate();

        /**
         * Check whether a Query exactly matches
         * this node.
         */
        bool matches(const core::QueryArgs&) const;

        void setNode(IReactiveNodePtr&&);

    private:
        IReactiveNodePtr activeNode;
        rx::observable<core::Context> observable;
    };

    using ReactiveNodeEntryPtr = std::unique_ptr<ReactiveNodeEntry>;
}