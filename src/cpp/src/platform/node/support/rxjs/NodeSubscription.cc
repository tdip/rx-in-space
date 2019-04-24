#include "rxjs/NodeSubscription.hh"

#include "debug.hh"

#include "quantifio/helpers.hh"

namespace rx::platform::node{

    void unsubscribe(Nan::Persistent<v8::Object> persistentSubscription){
        v8::Local<v8::Object> subscription = persistentSubscription.Get(
            Nan::GetCurrentContext()->GetIsolate());

        v8::Local<v8::Function> unsubscribe;
        ASSERT_EVAL(
            v8::quantifio::get(subscription, "unsubscribe", unsubscribe),
            "The object is not a subscription");

        const int argc = 0;
        v8::Local<v8::Value> argv[argc];

        Nan::CallAsFunction(
            unsubscribe,
            subscription,
            argc,
            argv);
    }

    rx::composite_subscription NodeSubscription::toCppSubscription(v8::Local<v8::Object> localSubscription){
        rx::composite_subscription result;

        result.add(
            [subscription = Nan::Persistent<v8::Object>(localSubscription)]
            (){ unsubscribe(subscription); });

        return result;
    }
}