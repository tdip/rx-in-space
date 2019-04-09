#pragma once

#include "rx.hh"

#include "core/Context.hh"

#include "util/ObservableSubjectBase.hh"

namespace rx::space::store{

    using ReactiveNodeInstanceSubject = util::ObservableSubject<core::ContextPtr, std::function<void()>, std::function<void()>>;

    class ReactiveNodeInstance{
    public:
        ReactiveNodeInstance(const rx::observable<core::ContextPtr>&);
        ~ReactiveNodeInstance();

        const rx::observable<core::ContextPtr>& observable() const;

    private:
        const rx::composite_subscription nodeSubscription;
        void onValue(core::ContextPtr& value);
        ReactiveNodeInstanceSubject subject;
    };
}