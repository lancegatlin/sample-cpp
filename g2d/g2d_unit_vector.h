#ifndef __G2D_UNIT_VECTOR_H
#define __G2D_UNIT_VECOTR_H

#include <g2d/g2d_vector.h>

/*
    File: g2d_unit_vector.h
    Author: lance.gatlin@yahoo.com
    Date: 01 Aug 2008
    Version: 1
    
    Overview: 
        1) Declares class UnitVector which represents a vector with a distance 
        of 1 from the origin. Derived from Vector.
                a) Constructors: DNE, (x,y float_type), (Vector)
                b) Function to calculate the angle between two unit vectors
                c) Function to calculate the unit vector perpendicular to this
                unit vector
                d) Uses default copy constructor
                e) Uses default assignment to self
*/

namespace g2d {
    
class UnitVector : public Vector {
    public:
    // Constructors
    UnitVector(DoesNotExist dne) : Vector(dne) { };
    UnitVector(float_ptype __x, float_ptype __y)
    : Vector(__x, __y) { makeUnitVector(); };
    UnitVector(const Vector &v)
    : Vector(v) { makeUnitVector(); };
    // Default copy constructor
    
    // Workaround so that perpendicular doesn't normalize when not needed
    private:
    UnitVector(const Point &p, bool)
    : Vector(p) { };

    public:
    // Calculate the angle between two unit vectors assuming 0,0 as origin
    Radians theta(const UnitVector &u) const
    { return getThetaBetween(u); }
    Radians getThetaBetween(const UnitVector &u) const
    {
        return acos(fabs(dotproduct(u)));
    }

    // Calculate the unit vector perpendicular to this unit vector
    UnitVector perpendicular() const
    { return getPerpendicular(); };
    UnitVector getPerpendicular() const
    {
        return UnitVector(Point(-y(),x()),true);
    }
    
    // Default assignment to self    
};

} // namespace g2d

#endif
