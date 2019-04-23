#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include "core/Query.hh"

#include "store/infrastructure/ReactiveMemberEntry.hh"
#include "store/infrastructure/ReactiveMemberInstance.hh"

namespace rx::space::store::infrastructure{


    struct ReactiveQueryInstanceContext{
        const core::Query query;
        const IReactiveQuerySpacePtr space,
        std::vector<ReactiveMemberInstancePtr> members;
    };

    /**
     * Class repsponsible for storing all the resources
     * that are required to perform a query and later
     * provide the reactive values of that query.
     */
    class ReactiveQueryInstance{

    typedef std::shared_ptr<ReactiveQueryInstanceContext> ContextPtr;

    public:
        ReactiveQueryInstance(
            const core::Query&,
            const IReactiveQuerySpacePtr,
            std::vector<ReactiveMemberEntry*>&);

        const rx::observable<QuerySources>& sources() const;

        static QueryContextPtr create(
            std::vector<ReactiveNodeInstancePtr>&& _nodeInstances){
            
            return std::make_unique<QueryContext>(std::move(_nodeInstances));
        }

    private:
        const ContextPtr context;
    };
}