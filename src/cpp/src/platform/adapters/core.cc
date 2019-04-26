#include "adapters/core.hh"

#include "quantifio/v8.hh"

namespace rx::space::platform::adapters{

    namespace MemberPropertyValue{
        std::optional<core::MemberPropertyValue> fromPlatform(v8::Local<v8::Value> value){
            return v8::quantifio::String::fromPlatform(value);
        }
    }

    namespace MemberProperties{
        std::optional<core::MemberProperties> fromPlatform(v8::Local<v8::Value> value){
            core::MemberProperties result;

            if(!value->IsObject()){
                return std::nullopt;
            }

            v8::Local<v8::Object> properties = value.As<v8::Object>();
            v8::Local<v8::Array> keys = properties->GetOwnPropertyNames();

            for(uint32_t i = 0; i < keys->Length(); i++){

                v8::Local<v8::Value> vKey = keys->Get(i);

                if(!vKey->IsString()){
                    continue;
                }

                v8::Local<v8::Value> platformProperty = properties->Get(vKey);
                auto property = MemberPropertyValue::fromPlatform(platformProperty);

                if(!property.has_value()){
                    return std::nullopt;
                }

                result.emplace(
                    std::piecewise_construct,
                    std::forward_as_tuple(
                        v8::quantifio::String::fromPlatform(vKey.As<v8::String>()).value),
                    std::forward_as_tuple(property.value));
            }

            return result;
        }
    }

    namespace OutputSet{
        std::optional<core::OutputSet> fromPlatform(v8::Local<v8::Value> value){

            auto members = fromPlatform(v8::quantifio::get(value, "properties"));
            if(members.has_value()){
                return core::OutputSet{
                    std::move(members.value),
                    std::vector<core::OutputSetSelector>{ core::BaseSelector::All }
                };
            }

            return std::nullopt;
        }
    }

    namespace ReactiveContext{
        core::ReactiveValueContextPtr fromPlatform(v8::Local<v8::Value>);
    }
}