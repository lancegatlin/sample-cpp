#ifndef __G3D_LINE_H
#define __G3D_LINE_H

#include <g3d/g3d_vector.h>
#include <g3d/g3d_segment.h>

/*
    File: g3d_line.h
    Author: lance.gatlin@yahoo.com
    Date: 01 Aug 2008
    Version: 1
    
    Overview: 
        1) Declares class Line to represent a line in 3d space. Represents 
        a line as an origin Vector and a direction Vector. Provides:
                a) Constructors: Default, DNE, (Vector, Vector), (Segment)
                b) Default copy constructor
                c) Accessor for the origin and direction vectors
                d) Function to calculate a point along the long given a 
                value k that is mutiplied by the direction vector
                e) Equality to self (equal, operator ==)
                f) Assignment to Segment (assign, operator =)
                g) Default assignment to self
                h) ostream streamer (operator <<)
*/

namespace g3d {
    
class Line {
    Vector _origin, _direction;
    
    public:
    typedef Line this_t;
    
    // Constructors
    Line() { };
    
    Line(DoesNotExist dne) 
    : _origin(dne), _direction(dne) { };

    Line(const Vector &__origin, const Vector &__direction)
    : _origin(__origin), _direction(__direction)
    { }

    Line(const Segment &s)
    { *this = s; }
    
    // Default copy constructor
    
    // Accessors
    const Vector &origin() const { return _origin; };
    const Vector &direction() const { return _direction; };
    void origin(const Vector &v) { _origin = v; };
    void direction(const Vector &v) { _direction = v; };
    
    // Find a point along the line (parametric)
    Point operator()(float_ptype k) const 
    { return getPointFromParameter(k); };
    Point getPointFromParameter(float_ptype k) const
    {
        return origin() + k * direction();
    }
    
    // Equality
    bool equal(const this_t &rhs) const
    {
        return origin() == rhs.origin() && direction() == rhs.direction();
    }
    bool operator ==(const this_t &rhs) const
    { return equal(rhs); };
    
    // Assignment
    this_t &operator= (const Segment &rhs)
    { assign(rhs); return *this; };
    void assign(const Segment &rhs)
    {
        _origin = rhs.begin();
        _direction = rhs.end() - rhs.begin();
    }
    // Default assignment to self
};

// ostream streamer
std::ostream &operator << (std::ostream &out, const Line &l)
{
    out << '<' << l.origin() << "> + k<" << l.direction() << '>';
    return out;
}

} // namespace g3d

#endif
