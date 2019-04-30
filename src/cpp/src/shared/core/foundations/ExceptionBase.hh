#pragma once

#include <exception>

namespace rx::space::core::exceptions{
    class ExceptionBase : public std::exception{
        virtual const char* what() const throw(){
            return "An unknow exception happened";
        }
    };
}