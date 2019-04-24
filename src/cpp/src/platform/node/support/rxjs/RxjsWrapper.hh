#pragma once

#include "nan.h"
#include "rx.hh"

namespace rx::platform::node{
    class RxjsWrapper{
    public:
        RxjsWrapper(v8::Local<v8::Value>);

        v8::Local<v8::Object> create(const rx::observable<v8::Local<v8::Value>>) const;
    private:
        Nan::Persistent<v8::Object> rxjs;

        static void subscribeImplementation(const Nan::FunctionCallbackInfo<v8::Value>&);
    };
}