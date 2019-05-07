#pragma once

#include <memory>
#include <variant>

#include "core/foundations/Key.hh"

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
        virtual ReactiveMemberValueStream query(const KeyPowerSet&) = 0;

        /**
         * Get a reacitve space that immitates the behavior of
         * this space for the keys belonging to the given
         * power set.
         */
        virtual IReactiveQuerySpacePtr link(const KeyPowerSet&) = 0;

        virtual ~IReactiveQuerySpace() = default;
    };
}
