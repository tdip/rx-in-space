#include "quantifio/function.hh"

#include "debug.hh"

#include "quantifio/helpers.hh"

namespace v8::quantifio{
    
    v8::Local<v8::Function> bind(v8::Local<v8::Function> fn, v8::Local<v8::Value> obj){
        v8::Local<v8::Function> nodeBind;

        ASSERT_EVAL(
            get(fn, "bind", nodeBind),
            "The given 'fn' object is not a function.");

        const int argc = 1;
        v8::Local<v8::Value> argv[argc] = { obj };

        return Nan::CallAsFunction(nodeBind, fn, argc, argv).ToLocalChecked();
    }

    bool getBound(
        v8::Local<v8::Value> obj, const std::string key, v8::Local<v8::Function>& result){

        if(!get(obj, key, result)){
            return false;
        }

        result = bind(obj, result);
        return true;
    }
}