#pragma once

#include <functional>
#include <unordered_map>
#include <memory>

#include "rx.hh"

#include "core/Query.hh"
#include "core/OutputSet.hh"

#include "store/types/IReactiveSpaceMember.hh"

#include "util/ObservableSubjectBase.hh"

namespace rx::space::store::infrastructure{

    struct ReactiveMemberEntryContext{
        const core::OutputSet outputSet;
        /**
         * The current node that provides values to the set
         * corresponding to this node entry.
         */
        types::IReactiveSpaceMemberPtr activeNode;
    };

    /**
     * Wrapper class to store reactive nodes
     * in the reactive space. This class is also
     * in charge of activating the node when
     * requested and de-activate it when no
     * query is using it.
     */
    class ReactiveMemberEntry{

    typedef std::shared_ptr<ReactiveMemberEntryContext> ContextPtr;

    public:
        ReactiveMemberEntry(
            const core::OutputSet&,
            const types::IReactiveSpaceMemberPtr&);

        ~ReactiveMemberEntry();


        const core::OutputSet& outputSet() const;

        /**
         * Check whether this node belongs to
         * the set specified by the given
         * Query and if all required properties
         * are in the query.
         */
        bool matches(const core::Query&) const;

        types::IReactiveSpaceMemberPtr getMember() const;

        /**
         * Change the reactive node that produces the
         * values for the set identified by this
         * node entry.
         */
        void setMember(types::IReactiveSpaceMemberPtr&&) const;

    private:
        const ContextPtr context;
    };

    using ReactiveMemberEntryPtr = std::unique_ptr<ReactiveMemberEntry>;
}