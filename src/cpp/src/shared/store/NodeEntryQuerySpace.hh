#pragma once

#include "rx.hh"

#include <memory>
#include <vector>

#include "core/QueryArgs.hh"

#include "store/IReactiveNodeStream.hh"
#include "store/IReactiveQuerySpace.hh"
#include "store/INodeReactiveQuerySpace.hh"

#include "util/SimpleSubject.hh"

namespace rx::space::store{

    /**
     * Query space stream that can be activated and deactivated
     * without affecting the observable provided to the subscriber.
     */
    class NodeEntryQuerySpaceStream : public IReactiveNodeStream{

        public:
        NodeEntryQuerySpaceStream(
            IReactiveQuerySpace& _outerSpace,
            core::QueryArgs& _query) :
            outerSpace(_outerSpace),
            query(_query){}

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
    class NodeEntryQuerySpace : public INodeReactiveQuerySpace{

        public:
        NodeEntryQuerySpace(IReactiveQuerySpace& _outerSpace) :
        isActive(false),
        outerSpace(_outerSpace) {} 

        virtual IReactiveNodeStreamPtr query(const core::QueryArgs&) override;
        virtual void activate() override;
        virtual void deactivate() override;

        static INodeReactiveQuerySpacePtr create(IReactiveQuerySpace& space){
            return std::make_unique<NodeEntryQuerySpace>(space);
        }

        private:
        bool isActive;
        IReactiveQuerySpace& outerSpace;
        std::vector<std::weak_ptr<NodeEntryQuerySpaceStream>> streams;
    };
};