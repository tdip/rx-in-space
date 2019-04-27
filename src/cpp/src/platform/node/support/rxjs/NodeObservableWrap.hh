#pragma once

#include "nan.h"
#include "rx.hh"

namespace rx::platform::node{

    struct SubscriptionContext{
        rx::composite_subscription subscription;
        rx::subscriber<v8::Local<v8::Value>> subscriber;
    };

    /**
     * Class that allows using an observable created
     * with the rxjs javascript library as a standard
     * RxCpp observable that emits a v8::Value stream.
     * 
     * This observables will issue events in the same
     * v8::Context they were created.
     */
    class NodeObservableWrap{
    public:
        NodeObservableWrap(v8::Local<v8::Value>);

        static std::optional<rx::observable<v8::Local<v8::Value>>> toCppObservable(
            v8::Local<v8::Value> observable);
    private:
        const Nan::Persistent<v8::Value> observable;

        void onSubscribe(SubscriptionContext&) const;

        static void onNext(const Nan::FunctionCallbackInfo<v8::Value>&);
    };
}