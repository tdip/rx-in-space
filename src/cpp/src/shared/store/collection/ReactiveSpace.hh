#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include "store/types/IReactiveQuerySpace.hh"

#include "store/infrastructure/Key.hh"
#include "store/infrastructure/ReactiveMemberEntry.hh"
#include "store/infrastructure/ReactiveQueryInstance.hh"

namespace rx::space::store::collection{

    using namespace infrastructure;
    using namespace types;

    struct ReactiveSpaceContext{
        std::unordered_map<Key, ReactiveMemberEntry> members;
        std::vector<std::weak_ptr<ReactiveQueryInstance>> activeQueries;
    };

    class ReactiveSpace : public IReactiveQuerySpace {
    typedef std::shared_ptr<ReactiveSpaceContext> ContextPtr;

    public:
        ReactiveSpace(ContextPtr& _context);
        ReactiveSpace();

        virtual ReactiveMemberValueStream query(const core::Query&) override;

        void update(const core::OutputSet&, const types::IReactiveSpaceMemberPtr&);

    private:
        const ContextPtr context;

        IReactiveQuerySpacePtr getQuerySubspace(const core::Query&) const;
    };
}