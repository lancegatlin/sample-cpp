/*
    File: g_matrix_tier1_exception.h
    Author: lance.gatlin@yahoo.com
    Date: 19 Sep 2008
    Version: 1

    Overview: 
	1) Declares and implements MatrixOutOfBounds and MatrixReserveFail exceptions
        
*/

#include <exception>

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
