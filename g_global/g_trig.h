#ifndef __G2D_TRIG_H
#define __G2D_TRIG_H

#include <g_global/g_global.h>

/*
    File: g_trig.h
    Author: lance.gatlin@yahoo.com
    Date: 01 Aug 2008
    Version: 1
    
    Overview: 
        1) Declares class Degrees to store an angle measured in degrees. Can be
        constructed from Radians
        2) Declares class Radians to store an angle measured in radians. Can be
        constructed from Degrees.
        2) Declares replacement functions for the std trig functions that force
        the passed angle to Radians
*/

namespace g_global {

class Radians;

class Degrees {
    float_type _degrees;
    public:
    typedef Degrees this_t;
    
    // Constructors
    Degrees() : _degrees() { };
    Degrees(const Radians &);
    Degrees(float_ptype __degrees) : _degrees(__degrees) { };
    // Default copy constructor
    
    // Accessors
    float_ptype degrees() const { return _degrees; };
    void degrees(float_ptype __degrees) { _degrees = __degrees; };
    operator float_type() { return _degrees; };
    
    // Equality
    bool operator ==(const this_t &rhs) const
    { return equal(rhs); };
    bool equal(const this_t &rhs) const
    { return _degrees == rhs._degrees; };
    
    // Default assignment to self
};

class Radians {
    float_type _radians;
    public:
    typedef Radians this_t;
    
    // Constructors
    Radians() : _radians() { };
    Radians(const Degrees &a)
    : _radians(a.degrees() * PI/180)
    { };
    Radians(float_ptype __radians) : _radians(__radians) { };
    // Default copy constructor
    
    // Accessors
    float_ptype radians() const { return _radians; };
    void radians(float_ptype __radians) { _radians = __radians; };
    operator float_type() { return _radians; };

    // Equality
    bool operator ==(const this_t &rhs) const
    { return equal(rhs); };
    bool equal(const this_t &rhs) const
    { return _radians == rhs._radians; };
    
    // Default assignment to self
};

Degrees::Degrees(const Radians &r)
: _degrees(r.radians() * 180/PI)
{ };


inline float_type cosine(const Radians &a) 
{ return std::cos(a.radians()); };

inline float_type sine(const Radians &a)
{ return std::sin(a.radians()); };

inline float_type tangent(const Radians &a)
{ return std::tan(a.radians()); };

inline Radians arcCosine(float_ptype value) 
{ return std::acos(value); };

inline Radians arcSine(float_ptype value)
{ return std::asin(value); };

inline Radians arcTangent(float_ptype value)
{ return std::atan(value); };

} // namespace g_global

#endif
