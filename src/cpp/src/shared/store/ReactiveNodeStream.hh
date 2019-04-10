#pragma once

#include <vector>

#include "core/QueryArgs.hh"

#include "store/IReactiveNodeStream.hh"
#include "store/ReactiveNodeStream.hh"

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
            core::QueryArgs&& _query,
            QueryContext&& _queryInstance): 
            query(_query),
            queryInstance(std::move(_queryInstance)){}

        virtual const rx::observable<core::Context>& observable() const override;

    private:
        const QueryContext queryInstance;
        const core::QueryArgs query;
    };
}