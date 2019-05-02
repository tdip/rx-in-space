#pragma once

#include <unordered_map>

#include "core/foundations/Key.hh"

#include "core/space/IReactiveSpace.hh"

#include "structures/space/ReactiveMember.hh"

#include "util/SimpleSubject.hh"

namespace rx::space::structures{
    using namespace core;

    using ReactiveSpaceCollection = std::unordered_map<int64_t, ReactiveMember>;

    using ReactiveUpdateSubject = util::SimpleSubject<std::reference_wrapper<ReactiveUpdates>>;

    using DeltaObservable = rx::observable<std::reference_wrapper<ReactiveUpdates>>;

    struct ReactiveSpaceContext{
        ReactiveSpaceCollection spaces;
        ReactiveUpdateSubject updates;
    };

    using MemberDelta = std::optional<IReactiveQuerySpacePtr>;

    using SpaceDelta = std::unordered_map<int64_t, MemberDelta>;

    /**
     * Standard reactive spaces that uses a dictionary
     * to implement it's functionality.
     */
    class ReactiveSpace : IReactiveSpace{
    public:
        ReactiveSpace();

        virtual ReactiveMemberValueStream query(const core::PowerSetIdentifier&) override;
        virtual IReactiveQuerySpacePtr link(const core::PowerSetIdentifier&) override;
        virtual std::optional<exceptions::UpdateException> update(const ReactiveUpdates&) override;

        template<typename ...Args>
        static IReactiveSpacePtr create(Args&& ...args){
            return std::make_shared<ReactiveSpace>(
                std::forward<Args>(args)...);
        }
    private:
        typedef std::shared_ptr<ReactiveSpaceContext> ContextPtr;

        const std::optional<core::PowerSetIdentifier> scope;
        const ContextPtr context;

        ReactiveSpace(const core::SetIdentifier&, const ContextPtr&);

        DeltaObservable deltas(const core::PowerSetIdentifier&) const;
        void notify(const ReactiveUpdates&) const;
    };
}