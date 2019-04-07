#pragma once

#include "store/ReactiveNodeInstance.hh"

namespace rx::space::store{

    /**
     * Class repsponsible for storing all the resources
     * that are required to perform a query and later
     * provide the reactive values of that query.
     */
    class QueryContext{
    public:
        void addNodeInstance(ReactiveNodeInstance&& instance);
    };
}