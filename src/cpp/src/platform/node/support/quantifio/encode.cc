#include "quantifio/encode.hh"

namespace v8::quantifio{

    namespace String{
        std::optional<std::string> fromPlatform(v8::Local<v8::Value> value){

            if(!value->IsString()){
                return std::nullopt;
            }

            v8::Local<v8::String> input = value.As<v8::String>();
            char buffer[input->Length()];

            Nan::DecodeWrite(
                buffer,
                input->Length(),
                input,
                Nan::Encoding::UTF8);

            return std::string(buffer);
        }
    }
}