#pragma once

#include <functional>
#include <memory>
#include <variant>
#include <vector>

#include "rx.hh"

#include "core/OutputSet.hh"
#include "core/QueryArgs.hh"
#include "core/QuerySet.hh"
#include "core/Value.hh"


#include "store/types/IReactiveQuerySpace.hh"
#include "store/types/ReactiveMemberValueStream.hh"

namespace rx::space::store::types{

    class IReactiveSpaceMember;

    using IReactiveSpaceMemberPtr = std::shared_ptr<IReactiveSpaceMember>;

    using MemberValue = std::variant<ReactiveMemberValueStream, IReactiveSpaceMemberPtr>;

    /**
     * This interface corresponds to a member that belongs to a reactive
     * space. A member can either be a stream of values across time or
     * another reactive space that internally contains members.
     */
    class IReactiveSpaceMember{
    public:

        /**
         * Given a reactive query space and a query, this method returns all the elements
         * of this reactive space that belong to the set specified by the query. It can
         * return another reactive space that will be subsequently queried using the same
         * query.
         */
        virtual const MemberValue query(const IReactiveQuerySpace&, const core::QueryArgs&) = 0;
    };
}