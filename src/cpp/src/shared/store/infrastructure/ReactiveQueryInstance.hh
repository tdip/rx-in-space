#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include "core/Query.hh"

#include "store/infrastructure/Context.hh"
#include "store/infrastructure/Key.hh"
#include "store/infrastructure/ReactiveMemberEntry.hh"
#include "store/infrastructure/ReactiveMemberInstance.hh"

namespace rx::space::store::infrastructure{

    class ReactiveQueryInstance;

    using ReactiveQueryInstancePtr = std::shared_ptr<ReactiveQueryInstance>;

    struct ReactiveQueryInstanceContext{
        const ReactiveQueryContextBasePtr queryContext;
        std::unordered_map<Key, ReactiveMemberInstancePtr> members;
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
            const ReactiveQueryContextBasePtr&,
            std::vector<ReactiveMemberEntry*>&);

        const types::ReactiveMemberValueStream& stream() const;

        static ReactiveQueryInstancePtr create(
            const ReactiveQueryContextBasePtr& queryContext,
            std::vector<ReactiveMemberEntry*>& members){

        return std::make_unique<ReactiveQueryInstance>(
            queryContext,
            members);
        }

    private:
        const ContextPtr context;
    };
}