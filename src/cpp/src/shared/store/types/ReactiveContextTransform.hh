#pragma once

#include "core/ReactiveValueContext.hh"

namespace rx::space::store::types{

    class ReactiveContextTransform;

    using ReactiveContextTransformPtr = std::shared_ptr<ReactiveContextTransform>;

    class ReactiveContextTransform{
    public:
        virtual core::ReactiveValueContextPtr map(core::ReactiveValueContextPtr in){ return in; }

        static ReactiveContextTransformPtr identity(){
            return std::make_shared<ReactiveContextTransform>();
        }
    };
}