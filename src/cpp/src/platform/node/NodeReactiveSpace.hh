#pragma once

#include <memory>

#include "nan.h"

#include "rx-in-space.hh"

namespace rx::space::platform::node{
    
    /**
     * Javascript object that wraps around a
     * Reactive space.
     */
    class NodeReactiveSpace : public Nan::ObjectWrap{
    public:
        NodeReactiveSpace();
        static void query(const Nan::FunctionCallbackInfo<v8::Value>&);
        static void update(const Nan::FunctionCallbackInfo<v8::Value>&);

        static void init(v8::Local<v8::Object>);
    private:
        const std::unique_ptr<ReactiveSpace> reactiveSpace;
        static Nan::Persistent<v8::Function> constructor;

        static void newObject(const Nan::FunctionCallbackInfo<v8::Value>&);
    };
}