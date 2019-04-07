#pragma once

#include <memory>

#include "rx.hh"

#include "core/Context.hh"
#include "core/QuerySet.hh"

#include "store/IReactiveNode.hh"
#include "store/IReactiveNodeSource.hh"

namespace rx::space::store{

    class ReactiveNode: public IReactiveNode{

    public:
        bool matches(const core::QuerySet& query) const;

        void setSource(IReactiveNodeSource& os);

        const rx::observable<core::Context>& observable();
    };

    using ReactiveNodePtr = std::shared_ptr<ReactiveNode>;
    using ReactiveNodeWPtr = std::weak_ptr<ReactiveNode>;
}