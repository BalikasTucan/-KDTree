#ifndef INVALIDDIMENSIONSEXCEPTION_HPP
#define INVALIDDIMENSIONSEXCEPTION_HPP

#include <exception>

class InvalidDimensionsException : public std::exception {
public:
    virtual const char* what() const noexcept {
        return "----- Invalid Dimensions Exception -----\n";
    }
};

#endif 
