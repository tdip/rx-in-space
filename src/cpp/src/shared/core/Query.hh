#pragma once

#include "core/MemberProperty.hh"
#include "core/MergeStrategy.hh"
#include "core/Type.hh"

namespace rx::space::core{
    /**
     * Specifies a set of nodes of reactive values being subscribed
     * to and the mechanism that will be used to aggregate the
     * values comming from different nodes.
     */
    struct Query{
        MemberProperties query;
        MergeStrategy mergeStrategy;
    };
}