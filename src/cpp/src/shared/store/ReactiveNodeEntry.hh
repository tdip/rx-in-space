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

    using ReactiveNodeEntrySubject = util::ObservableSubject<core::ContextPtr, std::function<void()>, std::function<void()>>;

    /**
     * Wrapper class to store reactive nodes
     * in the reactive space. This class is also
     * in charge of activating the node when
     * requested and de-activate it when no
     * query is using it.
     */
    class ReactiveNodeEntry{
    public:
        ReactiveNodeEntry(INodeReactiveQuerySpacePtr&&);

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
        void setNode(IReactiveNodePtr&&);

    private:
        /**
         * The subject used to manage the subscriptions to this entry.
         * It will activate the node when subscribers appear and
         * dispose it when all subscribers are gone.
         */
        const ReactiveNodeEntrySubject subject;

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

        /**
         * Called whenever the underlying node produces a value. This
         * simply takes the value from the node, constructs the node
         * Context and passes the resulting value to the observable
         * of the node entry.
         */
        void onNodeValue(core::ValuePtr);

        bool unsubscribeNode();

        void activateSubscriptionToNode();
    };

    using ReactiveNodeEntryPtr = std::unique_ptr<ReactiveNodeEntry>;
}