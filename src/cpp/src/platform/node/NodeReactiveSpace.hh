#pragma once

#include <memory>

#include "nan.h"

#include "rx-in-space.hh"

namespace rx::space::platform::node{
    
    class NodeReactiveSpace : public Nan::ObjectWrap{
    public:
    
    private:
        static Nan::Persistent<v8::Function> constructor;
        const std::unique_ptr<ReactiveSpace> reactiveSpace;
    };
}