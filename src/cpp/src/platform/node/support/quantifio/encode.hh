#pragma once

#include <optional>
#include <string>

#include "nan.h"

namespace v8::quantifio{

    namespace String{
        std::optional<std::string> fromPlatform(v8::Local<v8::Value>);
    }
}