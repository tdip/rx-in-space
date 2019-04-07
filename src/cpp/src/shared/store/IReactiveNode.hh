#pragma once

#include <memory>

namespace rx::space::store{
    class IReactiveNode{};

    using IReactiveNodePtr = std::shared_ptr<IReactiveNode>;
}