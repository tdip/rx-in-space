#pragma once

#include "nan.h"

#include "rx-in-space.hh"

namespace rx::space::platform::adapters{
    class ReactiveSpaceMemberAdapter : public store::types::IReactiveSpaceMember {
    public:
        ReactiveSpaceMemberAdapter::ReactiveSpaceMemberAdapter(
            rx::observable<v8::Local<v8::Value>> os);

        static std::optional<store::types::IReactiveSpaceMemberPtr> create(v8::Local<v8::Value>);

        virtual store::types::MemberValue query(
            const store::types::IReactiveQuerySpace&,
            const core::Query&) override;
    private:
        const store::types::ReactiveMemberValueStream observable;
    };
}