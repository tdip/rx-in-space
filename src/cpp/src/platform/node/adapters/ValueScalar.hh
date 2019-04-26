#pragma once

#include "nan.h"

#include "rx-in-space.hh"

namespace rx::space::platform::adapters{

    /**
     * Wrapper around a v8::Object so it gets
     * exposed as a IScalar that can be
     * used in a reactive space.
     */
    class ValueScalar : public core::IScalar{
    public:
        ValueScalar(v8::Local<v8::Value>);
        static core::IScalarPtr fromPlatform(v8::Local<v8::Value>);
    private:
        const Nan::Persistent<v8::Value> value;
    };
}