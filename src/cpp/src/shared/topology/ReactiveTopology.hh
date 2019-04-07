#pragma once

#include "core/Update.hh"

#include "store/ReactiveNodeCollection.hh"

namespace rx::space::topology{

    /**
     * A reactive topology is a reactive node
     * collection enhanced with relationships
     * between the nodes and the ability to
     * generate new nodes based on the output
     * of other nodes
     */
    class ReactiveTopology{

    public:
    void update(core::UpdateArgs&&);

    private:
        store::ReactiveNodeCollection nodeSet;

        void update(core::SetValue&&);
    };
}