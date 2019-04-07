#pragma once

#include <vector>

#include "store/IReactiveNodeStream.hh"
#include "store/QueryInstance.hh"

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
        ReactiveNodeStream(const QueryInstancePtr& _queryInstance): queryInstance(_queryInstance){}

        virtual rx::observable<core::Context>& observable() override;

    private:
        const QueryInstancePtr queryInstance;
    };
}