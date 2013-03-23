#ifndef __G3D_PLANE_H
#define __G3D_PLANE_H

#include <g3d/g3d_vector.h>

/*
    File: g3d_plane.h
    Author: lance.gatlin@yahoo.com
    Date: 01 Aug 2008
    Version: 1
    
    Overview: 
        1) Declares class g3d::Plane which represents a plane in 3d space as
        plane that is perpendicular to a Vector normal (line extending from 
        the origin) with a k value that specifies where along the line the 
        plane lies. Provides:
            a) Constructors: Default/DNE, (Vector, float_type k), (3 clockwise Points)
            b) Default copy constructor
            b) Accessors for the normal and k values
            c) Functions to test if a point lies in a plane or below/above the 
            plane
            d) Default assignment to self
            e) Equality (equal, operator ==)
*/

namespace g3d {
    
class Plane {
    Vector _normal;
    float_type _k;
    
    public:
    typedef Plane this_t;
    
    // Constructors
    Plane(DoesNotExist dne = DoesNotExist()) : _normal(dne), _k(DoesNotExist()) { };
    Plane(Vector __normal, float_ptype __k=0)
    : _normal(__normal), _k(__k) { };
    
    // Clockwise points
    Plane(const Point &p1, const Point &p2, const Point &p3)
    {
        Vector v1 = p1-p2, v2 = p3-p2;
        _normal = v1.crossproduct(v2);
        _k = _normal.dotproduct(p1);
        _normal.makeUnitVector();
    }
    // Default copy constructor
    
    // Accessors
    Vector normal() const { return _normal; };
    float_type k() const { return _k; };
    void normal(const Vector &v) { _normal = v; };
    void k(float_type __k) { _k = __k; };
    
    // Point lies in the plane?
    bool pointLiesInPlane(const Point &p) const
    {
        return tryPoint(p) == 0;
    }
    
    float_type tryPoint(const Point &p) const
    {
        return (p * normal()) - k();
    }
    float_type operator()(const Point &p) const
    { return tryPoint(p); };
    
    // Equality
    bool operator ==(const this_t &rhs)
    { return compare(rhs); }
    bool compare(const this_t &rhs)
    { return _normal == rhs._normal && _k == rhs._k; };
    
    // Assignment
    // Default assignment to self
};

} // namespace g3d

#endif
