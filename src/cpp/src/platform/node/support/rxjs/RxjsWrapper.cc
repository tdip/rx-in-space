#include "rxjs/RxjsWrapper.hh"

#include "debug.hh"

#include "quantifio/helpers.hh"

namespace rx::platform::node{

    v8::Local<v8::Object> RxjsWrapper::create(const rx::observable<v8::Local<v8::Value>> observable) const{
        v8::Local<v8::Object> localRxjs = rxjs.Get(Nan::GetCurrentContext()->GetIsolate());
        v8::Local<v8::Function> create;
        
        ASSERT_EVAL(
            v8::quantifio::get(localRxjs, "create", create),
            "rxjs is not the javascript implementation of RX");

        v8::Local<v8::Function> subscribe = Nan::New<v8::FunctionTemplate>(
            subscribeImplementation);
    }

    static void subscribeImplementation(const Nan::FunctionCallbackInfo<v8::Value>&){

    }
}