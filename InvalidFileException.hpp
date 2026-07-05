#ifndef INVALIDFILEEXCEPTION_HPP
#define INVALIDFILEEXCEPTION_HPP

#include <exception>

class InvalidFileException : public std::exception {
public:
    virtual const char* what() const noexcept {
        return "----- Invalid File Exception -----\n";
    }
};

#endif
