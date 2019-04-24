#pragma once

#include "nan.h"
#include "rx.hh"

namespace rx::platform::node{

    /**
     * Class that wrapps C++ observables to javascript
     * objects that have a subscribe method that can be
     * used with standard javascript subscribers.
     */
    class CppObservableWrap : public Nan::ObjectWrap{
    public:
        CppObservableWrap(const rx::observable<v8::Local<v8::Value>>&);

        static void init(v8::Local<v8::Object>);
        static v8::Local<v8::Object> toNodeObservable(const rx::observable<v8::Local<v8::Value>>&);
    private:
        const rx::observable<v8::Local<v8::Value>> observable;
        static Nan::Persistent<v8::Function> constructor;

        static void newObject(const Nan::FunctionCallbackInfo<v8::Value>& info);
        static void subscribe(const Nan::FunctionCallbackInfo<v8::Value>&);
        static void unSubscribe(const Nan::FunctionCallbackInfo<v8::Value>&);
    };
}