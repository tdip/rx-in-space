#include "NodeObservableWrap.hh"

#include <memory>

#include "debug.hh"

#include "quantifio/helpers.hh"

namespace rx::platform::node{

    const rx::observable<v8::Local<v8::Value>> NodeObservableWrap::toCppObservable(v8::Local<v8::Object> observable){
        const std::shared_ptr<NodeObservableWrap> wrapper = std::make_shared<NodeObservableWrap>(observable);

        return  rx::create<v8::Local<v8::Value>>(
            [wrapper]
            (rx::subscriber<v8::Local<v8::Value>> subscriber){
                subscriber.add([wrapper, subscription = wrapper->onSubscribe(subscriber)](){
                    subscription.unsubscribe();
                });
            });
    }

    rx::composite_subscription NodeObservableWrap::onSubscribe(rx::subscriber<v8::Local<v8::Value>>& susbcriber) const{
        v8::Local<v8::Object> localObservable = observable.Get(Nan::GetCurrentContext()->GetIsolate());

        v8::Local<v8::Function> subscribe;
        ASSERT_EVAL(
            v8::quantifio::get(localObservable, "subscribe", subscribe),
            "Provided object is not an observable.");

        v8::Local<v8::External> data = Nan::New<v8::External>(this);

        v8::Local<v8::Function> onValue = Nan::New<v8::FunctionTemplate>(
            onNext,
            data)
            ->GetFunction();

        const int argc = 1;
        v8::Local<v8::Value> argv[argc] = { onValue };

        v8::Local<v8::Object> subscription = Nan::CallAsFunction(
            subscribe,
            localObservable,
            argc,
            argv)
            .ToLocalChecked()
            .As<v8::Object>();

        rx::composite_subscription result;
        result.add([subscription = Nan::Persistent<v8::Object>(subscription)](){

        });

        return result;
    }
}