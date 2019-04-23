#pragma once

#include <unordered_set>

#include "store/infrastructure/Property.hh"

namespace rx::space::store::infrastructure{
    using Key = std::unordered_set<Property>;
}