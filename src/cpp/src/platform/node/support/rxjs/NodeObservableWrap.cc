#include "NodeObservableWrap.hh"

#include <memory>

#include "debug.hh"

#include "quantifio/helpers.hh"

#include "rxjs/NodeSubscription.hh"

namespace rx::platform::node{

    const std::string K_SUBSCRIBE = "subscribe";

    NodeObservableWrap::NodeObservableWrap(v8::Local<v8::Value> _observable) : observable(_observable) {}

    void NodeObservableWrap::onNext(const Nan::FunctionCallbackInfo<v8::Value>& value){
        SubscriptionContext* wrapper = (SubscriptionContext*)value.Data().As<v8::External>()->Value();
        wrapper->subscriber.on_next(value[0]);
    }

    std::optional<rx::observable<v8::Local<v8::Value>>> NodeObservableWrap::toCppObservable(
        v8::Local<v8::Value> observable){

        v8::Local<v8::Function> subscribe;
        if(!v8::quantifio::get(observable, K_SUBSCRIBE, subscribe)){
            return std::nullopt;
        }

        const std::shared_ptr<NodeObservableWrap> wrapper = std::make_shared<NodeObservableWrap>(
            observable);

        return  rx::create<v8::Local<v8::Value>>(
            [wrapper]
            (rx::subscriber<v8::Local<v8::Value>> subscriber){
                std::unique_ptr<SubscriptionContext> context = std::unique_ptr<SubscriptionContext>(
                    new SubscriptionContext{
                        rx::composite_subscription(),
                        std::move(subscriber)
                    });
                wrapper->onSubscribe(*context);

                subscriber.add([subscription = std::move(context)](){
                    subscription->subscription.unsubscribe();
                });
            });
    }

    void NodeObservableWrap::onSubscribe(SubscriptionContext& subscriber) const{
        v8::Local<v8::Value> localObservable = observable.Get(Nan::GetCurrentContext()->GetIsolate());

        v8::Local<v8::Function> subscribe;
        ASSERT_EVAL(
            v8::quantifio::get(localObservable, K_SUBSCRIBE, subscribe),
            "Provided object is not an observable.");

        v8::Local<v8::External> data = Nan::New<v8::External>(&subscriber);

        v8::Local<v8::Function> onValue = Nan::New<v8::FunctionTemplate>(
            onNext,
            data)
            ->GetFunction();

        const int argc = 1;
        v8::Local<v8::Value> argv[argc] = { onValue };

        v8::Local<v8::Object> subscription = Nan::CallAsFunction(
            subscribe,
            localObservable.As<v8::Object>(),
            argc,
            argv)
            .ToLocalChecked()
            .As<v8::Object>();

        subscriber.subscription.add(NodeSubscription::toCppSubscription(subscription));
    }
}