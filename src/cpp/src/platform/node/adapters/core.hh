#pragma once

#include <optional>

#include "nan.h"

#include "rx-in-space.hh"

namespace rx::space::platform::adapters{

    namespace MemberProperties{
        std::optional<core::MemberProperties> fromPlatform(v8::Local<v8::Object>);
    }

    namespace OutputSet{
        std::optional<core::OutputSet> fromPlatform(v8::Local<v8::Object>);
    }

    namespace ReactiveValueContext{
        core::ReactiveValueContextPtr fromPlatform(v8::Local<v8::Value>);
    }
}