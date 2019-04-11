#pragma once

#include <map>
#include <set>

#include "core/QueryArgs.hh"
#include "core/OutputSet.hh"

#include "store/IReactiveNode.hh"
#include "store/IReactiveNodeStream.hh"
#include "store/IReactiveQuerySpace.hh"
#include "store/Property.hh"
#include "store/ReactiveNodeEntry.hh"
#include "store/ReactiveNodeStream.hh"
#include "store/QueryContext.hh"

namespace rx::space::store{

    using Key = std::set<Property>;

    Key fromQuery(const core::QueryArgs&);

    Key fromOutputSet(const core::OutputSet&);

    class ReactiveNodeCollection : public IReactiveQuerySpace{
    public:
        /**
        * Query the reactive space for values matching the
        * given query. The resulting stream will yield the
        * latest valeus that match the query. If new nodes
        * matching the query become available, they will
        * be added to the reactive stream.
        */ 
        virtual IReactiveNodeStreamPtr query(const  core::QueryArgs&) override;

        /**
         * Set the data source for a particular reactive node.
         * This will update a single node based on the query
         * given to it. Nodes can only have a single source
         * meaning that if a source for the node already exits,
         * it will be replaced with this source.
         */
        //void update(core::OutputSet&&, IReactiveNodeSource&);
    private:

        /**
         * Create the context required to observe values of
         * the set matching the given query. The <isWeak>
         * argument determines wether the observables inside
         * the context will remain active as long as the
         * context is alive or whether this context plays
         * no role determining if the observables of itself
         * are active or not.
         */
        QueryContextPtr queryContext(bool isWeak, const core::QueryArgs&) const;

        std::vector<std::weak_ptr<ReactiveNodeStream>> activeQueries;
        std::map<Key, ReactiveNodeEntry> reactiveNodes;
    };
}