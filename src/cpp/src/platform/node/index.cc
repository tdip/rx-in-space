#include "nan.h"

#include "rxjs/rxjs.hh"

#include "NodeReactiveSpace.hh"

namespace rx::space::platform::node{
    void init(v8::Local<v8::Object> exports){
        rx::platform::node::CppObservableWrap::init(exports);
        NodeReactiveSpace::init(exports);
    }
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-function-type"
NODE_MODULE(RxInSpace, rx::space::platform::node::init);
#pragma GCC diagnostic popl