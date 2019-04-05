#pragma once

#include <map>
#include <string>
#include <variant>
#include <vector>

namespace rx::space::core{

    using QueryProperty = std::variant<std::string, std::vector<std::string>>;

    /**
    * Type that describes a set of reactive values that
    * exists within a reactive space.
    */ 
    using QuerySet = std::map<std::string, QueryProperty>;
}