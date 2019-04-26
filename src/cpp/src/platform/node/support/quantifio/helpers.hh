#pragma once

#include "nan.h"

namespace v8::quantifio{
    v8::Local<v8::Value> get(v8::Local<v8::Value> value, const std::string& key);
    bool get(v8::Local<v8::Value>, const std::string&, v8::Local<v8::Function>&);
}