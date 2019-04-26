#include "NodeReactiveSpace.hh"

#include "adapters/core.hh"
#include "adapters/ReactiveSpaceMember.hh"

namespace rx::space::platform::node{

    NodeReactiveSpace::NodeReactiveSpace() :
        reactiveSpace(std::make_unique<ReactiveSpace>()) {}

    void NodeReactiveSpace::query(const Nan::FunctionCallbackInfo<v8::Value>& info){}

    void NodeReactiveSpace::update(const Nan::FunctionCallbackInfo<v8::Value>& info){

        std::optional<core::OutputSet> outputSet;
        std::optional<store::types::IReactiveSpaceMemberPtr> member;

        if(
            info.Length() < 2
            || !(outputSet = adapters::OutputSet::fromPlatform(info[0])).has_value()
            || !(member = adapters::ReactiveSpaceMemberAdapter::create(info[1])).has_value()){

            Nan::ThrowError(
                "The 'update' method of 'NodeReactiveSpace' requires two argumnts.");
            return;
        }

        NodeReactiveSpace* space = ObjectWrap::Unwrap<NodeReactiveSpace>(info.This());
        space->reactiveSpace->update(outputSet.value(), member.value());
        info.GetReturnValue().SetUndefined();
    }

    void NodeReactiveSpace::newObject(const Nan::FunctionCallbackInfo<v8::Value>& info){

        if(
            info.Length() < 1){

            Nan::ThrowError("'NodeReactiveSpace' constructor requires the 'rxjs' module as argument.");
            return;
        }

        if(info.IsConstructCall()){
            NodeReactiveSpace* wrapped = new NodeReactiveSpace();
        }
    }

    void NodeReactiveSpace::init(v8::Local<v8::Object> exports){
        v8::Local<v8::FunctionTemplate> newObjectTemplate = Nan::New<v8::FunctionTemplate>(newObject);
        newObjectTemplate->SetClassName(Nan::New("NodeReactiveSpace").ToLocalChecked());
        newObjectTemplate->InstanceTemplate()->SetInternalFieldCount(0);

        Nan::SetPrototypeMethod(newObjectTemplate, "update", update);

        constructor.Reset(newObjectTemplate->GetFunction());
        exports->Set(
            Nan::New("NodeReactiveSpace").ToLocalChecked(),
            newObjectTemplate->GetFunction());
    }
}