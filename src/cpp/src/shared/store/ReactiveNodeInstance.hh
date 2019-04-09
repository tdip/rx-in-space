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
        ReactiveNodeInstance(rx::observable<core::ContextPtr>&&);
        ~ReactiveNodeInstance();

        rx::observable<core::ContextPtr> observable();

        void onNext(core::ContextPtr& value);

        static ReactiveNodeInstancePtr create(rx::observable<core::ContextPtr>&&){

        }

    private:
        ReactiveNodeInstanceSubject subject;
        const rx::composite_subscription nodeSubscription;
    };
}