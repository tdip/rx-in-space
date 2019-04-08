#pragma once

#include <functional>
#include <unordered_map>
#include <memory>

#include "rx.hh"

#include "core/Context.hh"
#include "core/QueryArgs.hh"

#include "store/IReactiveNode.hh"
#include "store/ReactiveNodeInstance.hh"

#include "util/Disposable.hh"

namespace rx::space::store{

    using ReactiveNodeEntryDispose = util::Disposable<std::function<void()>>;

    /**
     * Wrapper class to store reactive nodes
     * in the reactive space. This class is also
     * in charge of activating the node when
     * requested and de-activate it when no
     * query is using it.
     */
    class ReactiveNodeEntry{
    public:
        ReactiveNodeEntry(IReactiveQuerySpacePtr&&);

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

        /**
         * Change the reactive node that produces the
         * values for the set identified by this
         * node entry.
         */
        void setNode(IReactiveNodePtr&&);

    private:
        /**
         * Counter to generate unique identifiers to all
         * subscribers to this node entry.
         */
        long idCount;

        /**
         * The query-space instance that used by this
         * node entry to subscribe to other values
         * in the query space.
         */
        IReactiveQuerySpacePtr space;

        /**
         * The subscriptions in this query space.
         */
        std::unordered_map<long, rx::subscriber<core::ContextPtr>> subscriptions;

        /**
         * Lambda function that wraps around the 'onSubscribe' method to make
         * it easier to construct an observable with it.
         */
        const std::function<void(const rx::subscriber<core::ContextPtr>&)> subscribe;

        /**
         * Permanent observable for a particualr output set. Regardles of nodes
         * being changed. This observable will always yield the latest value
         * of the node.
         */
        const rx::observable<core::ContextPtr> observable;

        rx::composite_subscription activeNodeSubscription;
        std::weak_ptr<ReactiveNodeEntryDispose> dispose;
        IReactiveNodePtr activeNode;

        void onSubscribe(const rx::subscriber<core::ContextPtr>&);

        bool unsubscribeNode();

        std::shared_ptr<ReactiveNodeEntryDispose> subscribeToNode();

        void activateSubscriptionToNode();
    };

    using ReactiveNodeEntryPtr = std::unique_ptr<ReactiveNodeEntry>;
}