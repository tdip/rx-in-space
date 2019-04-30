#pragma once

#include <memory>
#include <variant>

#include "core/foundations/Identifiers.hh"

#include "core/space/ReactiveMemberValueStream.hh"

namespace rx::space::core{

    class IReactiveQuerySpace;

    using IReactiveQuerySpacePtr = std::shared_ptr<IReactiveQuerySpace>;

    /**
     * Interface representing a space of reactive values grouped
     * into sets.
     * 
     * Reactive values can be located by using the appropiate
     * set identiifer.
     */
    class IReactiveQuerySpace{
        public:
        /**
         * Get an observable to all the values of the set matching
         * the given identifier.
         */
        virtual ReactiveMemberValueStream query(const core::PowerSetIdentifier&) = 0;

        /**
         * Split the reactive space into a subspace containing only
         * the members corresponding to the given set.
         */
        virtual IReactiveQuerySpacePtr link(const core::PowerSetIdentifier&) = 0;

        virtual ~IReactiveQuerySpace() = default;
    };
}
