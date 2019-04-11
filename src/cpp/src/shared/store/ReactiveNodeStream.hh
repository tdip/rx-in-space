#pragma once

#include <vector>

#include "core/QueryArgs.hh"

#include "store/IReactiveNodeStream.hh"
#include "store/QueryContext.hh"
#include "store/ReactiveNodeStream.hh"

#include "util/SimpleSubject.hh"

namespace rx::space::store{

    /**
     * Class responsible for providing access to values emitted by
     * reactive nodes. Instance of this class are constructed
     * based on a query provided to the node store and provides
     * a single observable that emits values from all the nodes
     * matching that query. It will pick up new reactive nodes
     * as they appear and when discarded, it will remove
     * all links asociated to the reactive node.
     */
    class ReactiveNodeStream: public IReactiveNodeStream{

    public:
        ReactiveNodeStream(
            const core::QueryArgs& _query,
            QueryContextPtr _queryInstance): 
            queryInstance(std::move(_queryInstance)),
            query(_query){}

        virtual const rx::observable<core::ContextPtr>& observable() const override;

        static IReactiveNodeStreamPtr create(
            const core::QueryArgs& _query,
            QueryContextPtr&& _queryInstance){

            return std::make_shared<ReactiveNodeStream>(_query, std::move(_queryInstance));
        }

    private:
        const QueryContextPtr queryInstance;
        const core::QueryArgs query;
        const util::SimpleSubject<core::ContextPtr> subject;
        const rx::composite_subscription sourcesSubscription;

        rx::composite_subscription valuesSubscription;

        /**
         * Called whenever the sources for the query change.
         */
        void onQuerySources(QuerySources sources);
    };
}