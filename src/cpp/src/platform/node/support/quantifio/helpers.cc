#include "quantifio/helpers.hh"

v8::Local<v8::Value> get(v8::Local<v8::Value> value, const std::string& key){
    if(!value->IsObject()){
        return Nan::Undefined();
    }

    return value.As<v8::Object>()->Get(Nan::Encode(key.c_str(), key.length(), Nan::Encoding::UTF8));
}

bool get(v8::Local<v8::Value> value, const std::string& key, v8::Local<v8::Function>& result){
    v8::Local<v8::Value> tmp = get(value, key);

    if(tmp->IsFunction()){
        result = tmp.As<v8::Function>();
        return true;
    }

    return false;
}