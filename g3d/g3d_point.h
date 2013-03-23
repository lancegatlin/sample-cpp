#ifndef __G3D_POINT_H
#define __G3D_POINT_H

#include <ostream>
#include <g3d/g3d_global.h>

/*
    File: g3d_point.h
    Author: lance.gatlin@yahoo.com
    Date: 01 Aug 2008
    Version: 1
    
    Overview: 
        1) Declares class Point which represents a point in 3d space with a
        x,y and z float_type value. Provides:
                a) Constructors: Default, DNE, (x,y,z float_type)
                b) Uses default copy constructor
                c) Accessors for x,y,z
                d) Function to calculate distance to origin (0,0,0) or a 
                specified point
                e) Function to test if a point exists
                f) Equality (equal, operator ==)
                g) Uses default assignment to self
                h) Comparision (compare, operator <)
                i) Math operations Point<->Point or Point<->float_type (+,-,*,/)
                j) ostream stream (operator <<)
*/

namespace g3d {
    
class Point {
    float_type _x,_y,_z;
    
    public:
    typedef Point this_t;

    // Constructors
    Point(DoesNotExist dne)
    : _x(dne), _y(dne), _z(dne) { };
    
    Point(
        float_ptype __x = 0
        ,float_ptype __y = 0
        ,float_ptype __z = 0
    )
    : _x(__x), _y(__y), _z(__z) { };
    // Default copy constructor
    
    // Accessors
    float_ptype x() const { return _x; };
    float_ptype y() const { return _y; };
    float_ptype z() const { return _z; };
    void x(float_ptype f) { _x = f; };
    void y(float_ptype f) { _y = f; };
    void z(float_ptype f) { _z = f; };
    
    // Distance to origin or a specified point
    float_type d() const
    { return getDistance(); };
    float_type getDistance() const
    { return Point(0,0,0).getDistanceTo(*this); };
    
    float_type d(const Point &p2) const { return getDistanceTo(p2); };
    float_type getDistanceTo(const Point &p2) const
    {
        // d = sqrt[(x2-x1)^2 +(y2-y1)^2]
        float_type xv = p2.x() - x();
        float_type yv = p2.y() - y();
        float_type zv = p2.z() - z();
        return std::sqrt(xv*xv+yv*yv+zv*zv);
    }
    
    // Does the point exist?
    bool exists() const
    { return fexists(x()) && fexists(y()) && fexists(z()); }


    // Equality
    bool operator ==(const this_t &rhs) const 
    { return equal(rhs); };
    bool equal(const this_t &rhs) const
    { 
        return fequal(x(), rhs.x()) 
             && fequal(y(), rhs.y()) 
             && fequal(z(), rhs.z());
    };
    
    // Comparison
    bool operator < (const this_t &rhs) const
    { return compare(rhs); };
    bool compare(const this_t &rhs) const
    {
        if(fless(x(),rhs.x()))
            return true;
            
        if(fequal(x(),rhs.x()))
        {
            if(fless(y(),rhs.y()))
                return true;
            if(fequal(y(),rhs.y()))
                return fless(z(),rhs.z());
        }
        return false;
    }
    
    // Assignment
    // Default assignment to self
};

// Point + Point
Point operator +(const Point &lhs, const Point &rhs)
{
    return Point(lhs.x() + rhs.x(), lhs.y() + rhs.y(), lhs.z() + rhs.z());
}

// Point += Point
Point &operator +=(Point &lhs, const Point &rhs)
{
    return lhs = lhs + rhs;
}

// Point - Point
Point operator -(const Point &lhs, const Point &rhs)
{
    return Point(lhs.x() - rhs.x(), lhs.y() - rhs.y(), lhs.z() - rhs.z());
}

// Point -= Point
Point &operator -=(Point &lhs, const Point &rhs)
{
    return lhs = lhs - rhs;
}

// Point * float_type
Point operator *(const Point &lhs, float_ptype rhs)
{
    return Point(lhs.x() * rhs, lhs.y() * rhs, lhs.z() * rhs);
}

// float_tyep * Point
Point operator *(float_ptype lhs, const Point &rhs)
{
    return Point(rhs.x() * lhs, rhs.y() * lhs, rhs.z() * lhs);
}

// Point *= float_type
Point &operator *=(Point &lhs, float_ptype rhs)
{
    return lhs = lhs * rhs;
}

// Point / float_type
Point operator /(const Point &lhs, float_ptype rhs)
{
    return Point(lhs.x() / rhs, lhs.y() / rhs, lhs.z() / rhs);
}

// Point /= float_type
Point &operator /=(Point &lhs, float_ptype rhs)
{
    return lhs = lhs / rhs;
}

// ostream streamer
std::ostream &operator <<(std::ostream &out, const Point &p)
{
    out << p.x() << ',' << p.y() << ',' << p.z();
    return out;
}

} // namespace g3d

#endif
