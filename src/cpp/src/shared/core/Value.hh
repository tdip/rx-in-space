#pragma once

#include <memory>
#include <variant>
#include <vector>

namespace rx::space::core{

    class IScalar{

    };

    using IScalarPtr = std::shared_ptr<IScalar>;

    /**
     * Holder for reactive values
     */
    class Value{
        public:
        explicit Value(std::variant<IScalarPtr, std::vector<Value>>&& _value)
            : value(std::move(_value)){}

        template<typename T>
        constexpr bool holds_alternative() const {
                return std::holds_alternative<T>(variant);
        }

        template<typename T>
        constexpr T get() const{
                return std::get<T>(variant);
        }

        template<typename T>
        constexpr T& get() {
                return std::get<T>(variant);
        }
        
        private:
            std::variant<IScalarPtr, std::vector<Value>> value;
    };

    using ValuePtr = std::shared_ptr<Value>;
}