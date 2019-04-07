#pragma once

#include <memory>
#include <vector>

#include "core/QueryArgs.hh"
#include "store/IReactiveNode.hh"

namespace rx::space::store{

    /**
     * Data structure that stores all the context
     * asociated to a particular query. It will be used
     * to ensure that a query is delivered the latest
     * values when new subscribers are created and removed.
     */
    class QueryInstance{

    public:
        QueryInstance(
            const core::QueryArgs&& _queryArgs,
            const std::vector<IReactiveNodePtr>&&  _reactiveNodes)
            : queryArgs(_queryArgs), reactiveNodes(_reactiveNodes) {}

    private:
        core::QueryArgs queryArgs;
        std::vector<IReactiveNodePtr> reactiveNodes;
    };

    using QueryInstancePtr = std::shared_ptr<QueryInstance>;
    using QueryInstanceWPtr = std::weak_ptr<QueryInstance>;
}