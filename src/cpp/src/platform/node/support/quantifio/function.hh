#pragma once

#include "nan.h"

namespace v8::quantifio{

    v8::Local<v8::Function> bind(v8::Local<v8::Function>, v8::Local<v8::Value>);

    bool getBound(v8::Local<v8::Value>, const std::string, v8::Local<v8::Function>&);
}