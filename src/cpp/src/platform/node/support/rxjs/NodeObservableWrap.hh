#pragma once

#include "nan.h"
#include "rx.hh"

namespace rx::platform::node{

    class NodeObservableWrap{
    public:
        NodeObservableWrap(v8::Local<v8::Object>);

        static const rx::observable<v8::Local<v8::Value>> toCppObservable(v8::Local<v8::Object> observable);
    private:
        const Nan::Persistent<v8::Object> observable;

        rx::composite_subscription onSubscribe(rx::subscriber<v8::Local<v8::Value>>&);

        static void onNext(const Nan::FunctionCallbackInfo<v8::Value>&);
    };
}