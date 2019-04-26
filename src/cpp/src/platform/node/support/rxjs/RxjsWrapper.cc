#include "rxjs/RxjsWrapper.hh"

#include "debug.hh"

#include "quantifio/v8.hh"

#include "rxjs/CppObservableWrap.hh"

namespace rx::platform::node{

    RxjsWrapper::RxjsWrapper(v8::Local<v8::Object> _rxjs)
        : rxjs(_rxjs) {}

    v8::Local<v8::Object> RxjsWrapper::create(const rx::observable<v8::Local<v8::Value>> observable) const{
        v8::Local<v8::Object> localRxjs = rxjs.Get(Nan::GetCurrentContext()->GetIsolate());
        v8::Local<v8::Function> create;
        
        ASSERT_EVAL(
            v8::quantifio::get(localRxjs, "create", create),
            "rxjs is not the javascript implementation of RX");

        v8::Local<v8::Object> observableWrap = CppObservableWrap::toNodeObservable(
            observable);
        v8::Local<v8::Function> subscribe;

        ASSERT_EVAL(
            v8::quantifio::getBound(observableWrap, "subscribe", subscribe),
            "Error, CppObservableWrap does not have a subscribe method");

        const int argc = 1;
        v8::Local<v8::Value> argv[argc] = { subscribe };

        return Nan::CallAsFunction(create, localRxjs, argc, argv)
            .ToLocalChecked()
            .As<v8::Object>();
    }
}