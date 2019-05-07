#pragma once

#include <optional>
#include <tuple>
#include <vector>

#include "core/space/IReactiveQuerySpace.hh"
#include "core/space/UpdateException.hh"

namespace rx::space::core{

    class IReactiveSpace;

    using IReactiveSpacePtr = std::shared_ptr<IReactiveSpace>;

    struct SetMember{
        const ReactiveMemberValueStream member;
    };

    struct DeleteMember{};

    typedef std::variant<SetMember, DeleteMember> MemberOperation;

    struct MemberUpdate{
        KeySet key;
        MemberOperation operation;
    };

    typedef std::vector<MemberUpdate> MemberUpdates;

    struct SetSpace{
        const IReactiveSpacePtr space;
    };

    struct DeleteSpace{};

    typedef std::variant<SetSpace, DeleteSpace> SpaceOperation;

    struct SpaceUpdate{
        KeyPowerSet subspace;
        SpaceOperation operation;
    };

    typedef std::vector<SpaceUpdate> SpaceUpdates;

    /**
     * Interface for a reactive query space that has
     * internal reactive subspaces that can be updated.
     */
    class IReactiveSpace : public IReactiveQuerySpace{
    public:

        /**
         * Update a single reactive member to output the values produced
         * by the given stream.
         */
        virtual std::optional<exceptions::UpdateException> update(const MemberUpdates&) = 0;

        /**
         * Modifies the reactive space such that the given subsets of keys will
         * now be considered members of the new space. This implies that queries
         * selecting members of the given subsets will be handled by the given
         * reactive space.
         */
        virtual std::optional<exceptions::UpdateException> update(const SpaceUpdates&) = 0;
    };
}