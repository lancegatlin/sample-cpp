#ifndef __G_GLOBAL_H
#define __G_GLOBAL_H

#include <iostream>
#include <cmath>
#include <limits>

/*
    File: g_global.h
    Author: lance.gatlin@yahoo.com
    Date: 01 Aug 2008
    Version: 1
    
    Overview: 
        1) Declares global values for both the g2d and g3d libaries.
        2) Declares class DoesNotExist for testing if a float_type does not exist
        3) Declares epislon value and provides functions for comparing float_types
        (less, equal, greater, etc) within epislon.
*/

namespace g_global {

//typedef long double float_type;
//typedef const long double & float_ptype;
typedef double float_type;
typedef const double & float_ptype;

const float_type PI = 3.14159265358979323846;

class DoesNotExist 
{ 
    public:
    operator float_type() { return std::numeric_limits<float_type>::quiet_NaN(); }; 
};

typedef DoesNotExist DNE;

//const float_type epsilon = numeric_limits<float_type>::epsilon();
const float_type epsilon = 0.000001;

inline bool fequal(float_ptype lhs, float_ptype rhs)
{
    return (((rhs - epsilon) < lhs) && (lhs <( rhs + epsilon)));
}

inline bool fless(float_ptype lhs, float_ptype rhs)
{
    return lhs <( rhs - epsilon);
}

inline bool fgreater(float_ptype lhs, float_ptype rhs)
{
    return lhs >( rhs + epsilon);
}

inline bool fless_equal(float_ptype lhs, float_ptype rhs)
{
    return fequal(lhs,rhs) || fless(lhs,rhs);
}

inline bool fgreater_equal(float_ptype lhs, float_ptype rhs)
{
    return fequal(lhs,rhs) || fgreater(lhs,rhs);
}

inline bool fexists(float_ptype f)
{
    return  f != std::numeric_limits<float_type>::quiet_NaN() 
            && f != std::numeric_limits<float_type>::signaling_NaN() 
            && f != std::numeric_limits<float_type>::infinity();
}


} // namespace gglobal

#endif
