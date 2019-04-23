#pragma once

#include <functional>
#include <memory>
#include <optional>

#include "core/ReactiveValueContext.hh"

#include "store/types/IReactiveSpaceMember.hh"
#include "store/types/ReactiveContextTransform.hh"
#include "store/types/ReactiveMemberValueStream.hh"

#include "util/SimpleSubject.hh"

namespace rx::space::store::infrastructure{

    class ReactiveMemberInstance;

    /**
     * Helper class that executes a query on a reactive space member
     * and subscribes to the stream of results. If the query returns
     * a sub-spaces, it will continue executing the query until
     * a stream is obtained.
     */
    class ActiveMemberContext{
    public:
        ActiveMemberContext(
            const core::Query&,
            const types::IReactiveQuerySpace&,
            const types::IReactiveSpaceMemberPtr,
            const std::function<void(core::ReactiveValueContextPtr)>);

        ~ActiveMemberContext();
    private:
        const types::IReactiveSpaceMemberPtr activeMember;
        const std::unique_ptr<ReactiveMemberInstance> activeMemberInstance;
        const rx::composite_subscription activeMemberSubscription;
    };

    struct ReactiveMemberInstanceContext{
        const util::SimpleSubject<core::ReactiveValueContextPtr> subject;
        const types::IReactiveQuerySpacePtr space;
        const types::ReactiveContextTransformPtr contextMapper;
        std::unique_ptr<ActiveMemberContext> activeMemberContext;
    };

    /**
     * Special class that creates a subscription to a member in
     * a reactive space set on a particualr query. It provides
     * a single stream of values as the result of the query. This
     * stream will continue to be valid even if the unterlying
     * reactive space member is changed.
     */
    class ReactiveMemberInstance{
    typedef std::shared_ptr<ReactiveMemberInstanceContext> ContextPtr;
    typedef std::weak_ptr<ReactiveMemberInstanceContext> ContextWPtr;

    public:
        ReactiveMemberInstance(
            const core::Query&,
            types::IReactiveSpaceMemberPtr,
            const types::IReactiveQuerySpacePtr);

        ReactiveMemberInstance(
            const types::ReactiveContextTransformPtr,
            const core::Query&,
            types::IReactiveSpaceMemberPtr,
            const types::IReactiveQuerySpacePtr);

        const types::ReactiveMemberValueStream& stream() const;

        void setActiveMember(const core::Query&, types::IReactiveSpaceMemberPtr);

    private:
        const ContextPtr context;
        const ContextWPtr wContext;
        const std::function<void(core::ReactiveValueContextPtr)> onActiveMemberValue;

        static void onMemberInstanceValue(const ContextWPtr, core::ReactiveValueContextPtr);
    };

    using ReactiveMemberInstancePtr = std::shared_ptr<ReactiveMemberInstance>;
}