#pragma once

#include <memory>
#include <vector>

#include "core/Context.hh"

#include "store/ReactiveNodeInstance.hh"

namespace rx::space::store{

    class QueryContext;

    using QueryContextPtr = std::unique_ptr<QueryContext>;

    using QuerySources = std::shared_ptr<std::vector<rx::observable<core::ContextPtr>>>;

    /**
     * Class repsponsible for storing all the resources
     * that are required to perform a query and later
     * provide the reactive values of that query.
     */
    class QueryContext{
    public:
        QueryContext(std::vector<ReactiveNodeInstancePtr>&& _nodeInstances)
            : nodeInstances(std::move(_nodeInstances)) {}

        const rx::observable<QuerySources>& sources() const;

        static QueryContextPtr create(
            std::vector<ReactiveNodeInstancePtr>&& _nodeInstances){
            
            return std::make_unique<QueryContext>(std::move(_nodeInstances));
        }

    private:
        const std::vector<ReactiveNodeInstancePtr> nodeInstances;
    };
}