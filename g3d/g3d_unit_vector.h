#ifndef __G3D_UNIT_VECTOR_H
#define __G3D_UNIT_VECTOR_H

#include <g3d/g3d_vector.h>

/*
    File: g3d_unit_vector.h
    Author: lance.gatlin@yahoo.com
    Date: 01 Aug 2008
    Version: 1
    
    Overview: 
        1) Declares class UnitVector which represents a vector with a distance 
        of 1 from the origin. Derived from Vector.
                a) Constructors: DNE, (x,y,z float_type), (Vector)
                b) Uses default copy constructor
                c) Uses default assignment to self
*/

namespace g3d {
    
class UnitVector : public Vector {
    public:
    // Constructors
    UnitVector(DoesNotExist dne) : Vector(dne) { };
    UnitVector(float_ptype __x, float_ptype __y, float_ptype __z)
    : Vector(__x, __y, __z) { makeUnitVector(); };
    UnitVector(const Vector &v)
    : Vector(v) { makeUnitVector(); };
    // Default copy constructor
    
    // Default assignment to self
};

} // namespace g3d

#endif
