#pragma once

#include <variant>

namespace rx::space::core{
    /**
     * Type that describes the structural representation of types
     * stored in a reactive space
     */
    template<typename Scalars>
    class ValueAst{

        typedef ValueAst<Scalars> RecValue;

        public:
        explicit ValueAst(std::variant<Scalars, std::vector<RecValue>>&& _value)
            : value(std::move(_value)){}

        template<typename T>
        constexpr bool holds_alternative() const {
                return std::holds_alternative<T>(value);
        }

        template<typename T>
        constexpr T get() const{
                return std::get<T>(value);
        }

        template<typename T>
        constexpr T& get() {
                return std::get<T>(value);
        }
        
        private:
            std::variant<Scalars, std::vector<RecValue>> value;
    };
}