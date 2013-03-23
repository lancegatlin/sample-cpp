#ifndef __G3D_SEGMENT_H
#define __G3D_SEGMENT_H

#include <g3d/g3d_point.h>

/*
    File: g3d_segment.h
    Author: lance.gatlin@yahoo.com
    Date: 01 Aug 2008
    Version: 1
    
    Overview: 
        1) Declares class Segment which represents a line segment in 3d space 
        represented as two Points. Provides:
                a) Constructors: Default, (Point, Point)
                b) Uses default copy constructor
                c) Accessors for begin and end points
                d) Function to calculate distance between the points
                e) Functions to calculate the x,y or z distances between the points
                f) Equality (equal, operator ==)
                g) Uses default assignment to self
                h) ostream stream (operator <<)
*/

namespace g3d {
    
class Segment {
    Point _begin,_end;
    
    public:
    typedef Segment this_t;
    
    // Constructors
    Segment() { };
    Segment(const Point &__begin, const Point &__end) 
    : _begin(__begin), _end(__end) { };
    
    // Default copy constructor
    
    // Accessors
    const Point &begin() const { return _begin; };
    const Point &end() const { return _end; };
    void begin(const Point &p) { _begin = p; };
    void end(const Point &p) { _end = p; };
    
    // distance between the two points?
    float_type d() const { return getDistance(); };
    float_type getDistance() const { return begin().d(end()); };
    
    // x,y,z distance between two points?
    float_type dx() const { return end().x() - begin().x(); };
    float_type dy() const { return end().y() - begin().y(); };
    float_type dz() const { return end().z() - begin().z(); };
    
    // Equality
    bool operator ==(const this_t &rhs)
    { return equals(rhs); };
    bool equals(const this_t &rhs)
    { return begin() == rhs.begin() && end() == rhs.end(); };

    // Default assignment to self
    
/*    bool operator <(const this_t &rhs)
    { return less(rhs); };
    
    bool less(const this_t &rhs)    
    { return begin() < rhs.begin() && end() < rhs.end(); };*/
};

std::ostream &operator <<(std::ostream &out, const Segment &s)
{
    out << '(' << s.begin() << ")-(" << s.end() << ')';
    return out;
}

} // namespace g3d 

#endif
