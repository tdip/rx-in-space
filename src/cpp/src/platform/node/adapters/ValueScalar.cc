#include "adapters/ValueScalar.hh"

namespace rx::space::platform::adapters{
    ValueScalar::ValueScalar(v8::Local<v8::Value> _value) :
        value(_value) {}

    core::IScalarPtr fromPlatform(v8::Local<v8::Value> value){
        return std::make_shared<ValueScalar>(value);
    }
}