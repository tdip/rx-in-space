#pragma once

#include <map>
#include <set>

#include "core/QueryArgs.hh"
#include "core/OutputSet.hh"

#include "store/IReactiveNode.hh"
#include "store/IReactiveNodeSource.hh"
#include "store/IReactiveNodeStream.hh"
#include "store/Property.hh"
#include "store/QueryInstance.hh"
#include "store/ReactiveNode.hh"

namespace rx::space::store{

    using Key = std::set<Property>;

    Key fromQuery(const core::QueryArgs&);

    class ReactiveNodeCollection{
    public:
        /**
        * Query the reactive space for values matching the
        * given query. The resulting stream will yield the
        * latest valeus that match the query. If new nodes
        * matching the query become available, they will
        * be added to the reactive stream.
        */ 
        IReactiveNodeStreamPtr query(core::QueryArgs&&);

        /**
         * Set the data source for a particular reactive node.
         * This will update a single node based on the query
         * given to it. Nodes can only have a single source
         * meaning that if a source for the node already exits,
         * it will be replaced with this source.
         */
        void update(core::OutputSet&&, IReactiveNodeSource&);

    private:
        std::map<Key, ReactiveNodeWPtr> reactiveNodes;
        std::map<Key, QueryInstanceWPtr> reactiveQueries;
    };
}