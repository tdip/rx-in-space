#pragma once

#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>

#include "core/Query.hh"

#include "store/infrastructure/Context.hh"
#include "store/infrastructure/Key.hh"
#include "store/infrastructure/ReactiveMemberEntry.hh"
#include "store/infrastructure/ReactiveMemberInstance.hh"
#include "store/infrastructure/ReactiveQueryAggregator.hh"

namespace rx::space::store::infrastructure{

    class ReactiveQueryInstance;

    using ReactiveQueryInstancePtr = std::shared_ptr<ReactiveQueryInstance>;

    struct ReactiveQueryInstanceContext{
        const ReactiveQueryContextBasePtr queryContext;
        const types::ReactiveMemberValueSimpleSubject subject;
        std::unordered_map<Key, ReactiveMemberInstancePtr> members;
        rx::composite_subscription aggregatorSubscription;
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
            const ReactiveQueryContextBasePtr,
            std::vector<std::reference_wrapper<ReactiveMemberEntry>>&);

        ReactiveQueryInstance(
            const core::Query&,
            const types::IReactiveQuerySpacePtr&,
            std::vector<std::reference_wrapper<ReactiveMemberEntry>>&);

        ~ReactiveQueryInstance();

        const types::ReactiveMemberValueStream& stream() const;

        template<typename ...Args>
        static ReactiveQueryInstancePtr create(Args&& ...args){
            return std::make_shared<ReactiveQueryInstance>(
                std::forward<Args>(args)...);
        }

    private:
        const ContextPtr context;
    };
}