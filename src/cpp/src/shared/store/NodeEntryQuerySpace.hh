#pragma once

#include "rx.hh"

#include <unordered_map>
#include <memory>

#include "core/QueryArgs.hh"

#include "store/IReactiveNodeStream.hh"
#include "store/IReactiveQuerySpace.hh"
#include "store/INodeReactiveQuerySpace.hh"

#include "util/SimpleSubject.hh"

namespace rx::space::store{

    class NodeEntryQuerySpaceStream : public IReactiveNodeStream{

        public:
        NodeEntryQuerySpaceStream(
            IReactiveQuerySpace& _outerSpace,
            core::QueryArgs& _query,
            IReactiveNodeStreamPtr innerStream) :
            outerSpace(_outerSpace),
            query(_query),
            source(std::move(_subject)){}

        virtual const rx::observable<ReactiveNodeValue>& observable() const override;

        void activate();

        void deactivate();

        private:
        IReactiveQuerySpace& outerSpace;
        const util::SimpleSubject<ReactiveNodeValue> subject;
        const core::QueryArgs query;
        IReactiveNodeStreamPtr inner;
    };

    /**
     * Query space for a reactive node. This query space will
     * activate all queries when the node it is asociated to
     * becomes active (is selected by a query for instance)
     * and will de-activate the query space if the node asociated
     * to it becomes inactive.
     */
    class NodeEntryQuerySpace: public INodeReactiveQuerySpace{

        public:
        NodeEntryQuerySpace(IReactiveQuerySpace& _outerSpace): outerSpace(_outerSpace) {} 

        virtual IReactiveNodeStreamPtr query(core::QueryArgs&&) override;
        virtual void activate() override;
        virtual void deactivate() override;

        private:
        long id;
        bool isActive;
        IReactiveQuerySpace& outerSpace;
        std::unordered_map<long, std::weak_ptr<NodeEntryQuerySpaceStream>> streams;
    };
};