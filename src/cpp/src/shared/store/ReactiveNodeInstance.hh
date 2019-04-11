#pragma once

#include <functional>
#include <memory>

#include "rx.hh"

#include "core/Context.hh"
#include "core/OutputSet.hh"

#include "util/ObservableSubjectBase.hh"

namespace rx::space::store{

    using ReactiveNodeInstanceSubject = util::ObservableSubject<core::ContextPtr, std::function<void()>, std::function<void()>>;

    using ReactiveNodeEntrySubject = util::ObservableSubject<core::ContextPtr, std::function<void()>, std::function<void()>>;

    struct ReactiveNodeContextBase{
        const core::OutputSet nodeSet;
        ReactiveNodeEntrySubject subject;
    };

    struct ReactiveNodeInstanceContext{
        const std::weak_ptr<ReactiveNodeContextBase> baseContext;
        const ReactiveNodeInstanceSubject subject;
        rx::composite_subscription nodeSubscription;
    };

    class ReactiveNodeInstance;

    using ReactiveNodeInstancePtr = std::unique_ptr<ReactiveNodeInstance>;

    class ReactiveNodeInstance{
    public:
        ReactiveNodeInstance(const bool, const std::shared_ptr<ReactiveNodeContextBase>);
        ~ReactiveNodeInstance();

        const rx::observable<core::ContextPtr> observable() const;

        static ReactiveNodeInstancePtr create(rx::observable<core::ContextPtr>&&){

        }

    private:
        const std::shared_ptr<ReactiveNodeInstanceContext> context;
    };
}