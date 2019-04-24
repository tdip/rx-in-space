#pragma once

#include "nan.h"

namespace v8::quantifio{
    bool get(v8::Local<v8::Value>, const std::string&, v8::Local<v8::Function>&);
}