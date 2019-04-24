#pragma once

#include "nan.h"
#include "rx.hh"

namespace rx::platform::node{
    class NodeSubscription{
    public:
        static rx::composite_subscription toCppSubscription(v8::Local<v8::Object> subscription);
    };
}