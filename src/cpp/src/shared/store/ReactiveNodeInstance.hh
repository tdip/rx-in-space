#pragma once

#include <memory>

#include "rx.hh"

#include "core/Context.hh"

#include "util/ObservableSubjectBase.hh"

namespace rx::space::store{

    using ReactiveNodeInstanceSubject = util::ObservableSubject<core::ContextPtr, std::function<void()>, std::function<void()>>;

    class ReactiveNodeInstance;

    using ReactiveNodeInstancePtr = std::unique_ptr<ReactiveNodeInstance>;

    class ReactiveNodeInstance{
    public:
        ReactiveNodeInstance(const rx::observable<core::ContextPtr>&&);
        ~ReactiveNodeInstance();

        const rx::observable<core::ContextPtr> observable() const;

        void onNext(core::ContextPtr& value) const;

        static ReactiveNodeInstancePtr create(rx::observable<core::ContextPtr>&&){

        }

    private:
        const ReactiveNodeInstanceSubject subject;
        const rx::composite_subscription nodeSubscription;
    };
}