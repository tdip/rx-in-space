#pragma once

#include <vector>

#include "core/Query.hh"

#include "store/types/ReactiveMemberValueStream.hh"

namespace rx::space::store::infrastructure{

    /**
     * Class responsible for re-combining the streams
     * from the various members that match a query using
     * the methdod specified by said query.
     */
    class ReactiveQueryAggregator{
    public:
        ReactiveQueryAggregator(
            const core::Query&,
            std::vector<types::ReactiveMemberValueStream&>);

        ~ReactiveQueryAggregator();

        const types::ReactiveMemberValueStream& steam() const;
    };
}