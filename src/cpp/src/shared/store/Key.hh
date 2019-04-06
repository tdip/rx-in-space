#pragma once

#include <string>

namespace rx::space::store{

    using Predicate = std::string;

    using Property = std::pair<std::string, Predicate>;
}