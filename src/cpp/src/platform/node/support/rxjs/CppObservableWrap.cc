#include "rxjs/CppObservableWrap.hh"

#include "quantifio/helpers.hh"

namespace rx::platform::node{

    CppObservableWrap::CppObservableWrap(
        const rx::observable<v8::Local<v8::Value>>& _observable) :
        observable(_observable){}

    v8::Local<v8::Object> CppObservableWrap::toNodeObservable(
        const rx::observable<v8::Local<v8::Value>>& observable){

        v8::Local<v8::Function> ctor = constructor.Get(Nan::GetCurrentContext()->GetIsolate());
        const int argc = 1;
        v8::Local<v8::Value> argv[] = { Nan::New<v8::External>(
            &const_cast<rx::observable<v8::Local<v8::Value>>&>(observable)) };

        v8::Local<v8::Value> nodeObservable = Nan::CallAsConstructor(
            ctor,
            argc,
            argv)
            .ToLocalChecked();

        return nodeObservable.As<v8::Object>();
    }

    void CppObservableWrap::subscribe(
        const Nan::FunctionCallbackInfo<v8::Value>& callback){
        v8::Local<v8::Function> onNext; 

        if(
            callback.Length() < 1
            || !v8::quantifio::get(callback[0], "next", onNext)){

            Nan::ThrowError("Subscribe requires a subscriber as argument");
            return;
        }

        CppObservableWrap* wrapper = ObjectWrap::Unwrap<CppObservableWrap>(callback.This());
        rx::composite_subscription* subs = new  rx::composite_subscription;
        v8::Local<v8::Object> arg1 = callback[0].As<v8::Object>();

        subs->add(
            wrapper->observable.subscribe(
                [/*subscriber = Nan::Persistent<v8::Object>(arg1)*/]
                (v8::Local<v8::Value> value){

                    v8::Local<v8::Object> localSubscriber;/* = subscriber.Get(
                        Nan::GetCurrentContext()->GetIsolate());*/
                    v8::Local<v8::Function> next;

                    if(!v8::quantifio::get(localSubscriber, "next", next)){
                        Nan::ThrowError("Subscribe requires a subscriber as argument");
                    }

                    const int argc = 1;
                    v8::Local<v8::Value> argv[argc] = { value };
                    Nan::CallAsFunction(next, localSubscriber, argc, argv);
                }));

        v8::Local<v8::Function> unsubscribe = Nan::New<v8::FunctionTemplate>(
            unSubscribe,
            Nan::New<v8::External>(subs))
            ->GetFunction();

        callback.GetReturnValue().Set(unsubscribe);
    }

    void CppObservableWrap::unSubscribe(const Nan::FunctionCallbackInfo<v8::Value>& info){

        if(info.Data().IsEmpty()){
            return;
        }

        rx::composite_subscription* subs = (rx::composite_subscription*) info.Data()
            .As<v8::External>()
            ->Value();

        subs->unsubscribe();
        info.Data().Clear();
        delete subs;
        info.GetReturnValue().SetUndefined();
    }

    void CppObservableWrap::init(v8::Local<v8::Object> exports){
        Nan::HandleScope scope;
        v8::Local<v8::FunctionTemplate> newObjectTemplate = Nan::New<v8::FunctionTemplate>(newObject);
        newObjectTemplate->SetClassName(Nan::New("CppObservable").ToLocalChecked());
        newObjectTemplate->InstanceTemplate()->SetInternalFieldCount(1);

        Nan::SetPrototypeMethod(newObjectTemplate, "subscribe", subscribe);

        constructor.Reset(newObjectTemplate->GetFunction());
    }

    void CppObservableWrap::newObject(const Nan::FunctionCallbackInfo<v8::Value>& info){

        if(
            info.Length() < 1
            || !info[0]->IsExternal()){
            Nan::ThrowError("CppObservableWrap requires a native rx observable as argument");
            return;
        }

        rx::observable<v8::Local<v8::Value>>* observable = (rx::observable<v8::Local<v8::Value>>*)info[0].As<v8::External>()->Value();

        if(info.IsConstructCall()){
            CppObservableWrap* wrap = new CppObservableWrap(*observable);
            wrap->Wrap(info.This());
            info.GetReturnValue().Set(info.This());
        }else{
            const int argc = 1;
            v8::Local<v8::Value> argv[argc] = { info[0] };
            v8::Local<v8::Function> ctor = Nan::New<v8::Function>(constructor);
            info.GetReturnValue().Set(
                ctor->NewInstance(
                    Nan::GetCurrentContext(),
                    argc,
                    argv)
                    .ToLocalChecked());
        }
    }
}