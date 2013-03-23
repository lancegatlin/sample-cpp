#ifndef __G_MATRIX_EXCEPTION_H
#define __G_MATRIX_EXCEPTION_H

#include <exception>

namespace g_global {
    
class MatrixOutOfBounds : public std::exception {
    public:
    MatrixOutOfBounds() throw() { };
    virtual const char* what() const throw()
    {
        return "Matrix[Out of Bounds]";
    }
};

class MatrixReserveFail : public std::exception {
    public:
    MatrixReserveFail() throw() { };
    virtual const char* what() const throw()
    {
        return "Matrix[Reserve fail]";
    }
};

}; // namespace g_global

#endif
