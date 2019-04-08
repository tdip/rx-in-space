#pragma once

#include <memory>

namespace rx::space::store{
    class IReactiveQuerySpace{};

    using IReactiveQuerySpacePtr = std::unique_ptr<IReactiveQuerySpace>;
}
