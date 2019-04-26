#pragma once

#include "nan.h"

#include "rx-in-space.hh"

namespace rx::space::platform::adapters{
    class ReactiveSpaceMemberAdapter : public store::types::IReactiveSpaceMember {
    public:
        ReactiveSpaceMemberAdapter(v8::Local<v8::Object>);

        virtual store::types::MemberValue query(
            const store::types::IReactiveQuerySpace&,
            const core::Query&) override;
    private:
        const store::types::ReactiveMemberValueStream observable;
    };
}