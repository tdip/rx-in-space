#pragma once

#include <functional>
#include <unordered_map>
#include <memory>

#include "rx.hh"

#include "core/Context.hh"
#include "core/QueryArgs.hh"

#include "store/INodeReactiveQuerySpace.hh"
#include "store/IReactiveNode.hh"
#include "store/ReactiveNodeInstance.hh"

#include "util/ObservableSubjectBase.hh"

namespace rx::space::store{

    struct ReactiveNodeEntryContext : public ReactiveNodeContextBase{
        /**
         * The query-space instance that used by this
         * node entry to subscribe to other values
         * in the query space.
         */
        const INodeReactiveQuerySpacePtr space;
        /**
         * Holds the active (if any) subscription with the reactive node
         */
        rx::composite_subscription activeNodeSubscription;

        /**
         * The current node that provides values to the set
         * corresponding to this node entry.
         */
        IReactiveNodePtr activeNode;
    };

    /**
     * Wrapper class to store reactive nodes
     * in the reactive space. This class is also
     * in charge of activating the node when
     * requested and de-activate it when no
     * query is using it.
     */
    class ReactiveNodeEntry{

    typedef std::shared_ptr<ReactiveNodeEntryContext> ContextPtr;
    typedef std::weak_ptr<ReactiveNodeEntryContext> ContextWPtr;

    public:
        ReactiveNodeEntry(INodeReactiveQuerySpacePtr&&);

        ~ReactiveNodeEntry();

        /**
         * Activate the node in order to subscribe to
         * it's output sets. When all instances of
         * the node are discarded, the node will
         * be deactivated to save resources.
         */
        ReactiveNodeInstancePtr activate(bool isWeak) const;

        /**
         * Check whether this node belongs to
         * the set specified by the given
         * Query and if all required properties
         * are in the query.
         */
        bool matches(const core::QueryArgs&) const;

        /**
         * Change the reactive node that produces the
         * values for the set identified by this
         * node entry.
         */
        void setNode(IReactiveNodePtr&&) const;

    private:
        const ContextPtr context;

        /**
         * Called to make the node active, meaning
         * that it will start participating in
         * producing values of sets.
         */
        static void activateSubscriptionToNode(ContextWPtr);

        /**
         * Called whenever the underlying node produces a value. This
         * simply takes the value from the node, constructs the node
         * Context and passes the resulting value to the observable
         * of the node entry.
         */
        static void onNodeValue(ContextWPtr, core::ValuePtr);

        /**
         * Called to make the node inactive. It
         * is used to indicate that no subscriber
         * is interested in the node's set.
         */
        static bool unsubscribeNode(ContextWPtr);
    };

    using ReactiveNodeEntryPtr = std::unique_ptr<ReactiveNodeEntry>;
}