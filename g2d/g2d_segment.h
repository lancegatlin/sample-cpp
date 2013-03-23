#ifndef __G2D_SEGMENT_H
#define __G2D_SEGMENT_H

#include <g2d/g2d_point.h>

/*
    File: g2d_segment.h
    Author: lance.gatlin@yahoo.com
    Date: 01 Aug 2008
    Version: 1
    
    Overview: 
        1) Declares class Segment which represents a line segment in 2d space 
        represented as two Points. Provides:
                a) Constructors: Default, (Point, Point)
                b) Uses default copy constructor
                c) Accessors for begin and end points and dx,dy
                d) Function to calculate distance between the points
                e) Function to calculate the slope between the points
                f) Function to calculate the y-intercept (y=mx+b)
                e) Functions to calculate the angle between the two points
                f) Equality (equal, operator ==)
                g) Uses default assignment to self
                h) ostream stream (operator <<)
*/


namespace g2d {
    
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
    
    float_type dx() const { return end().x() - begin().x(); };
    float_type dy() const { return end().y() - begin().y(); };
    
    // distance between the two points?
    float_type d() const { return getDistance(); };
    float_type getDistance() const { return begin().d(end()); };
    
    // slope between the two points?
    float_type m() const { return getSlope(); };
    float_type getSlope() const { return begin().d(end()); };
    
    // y-intercept
    float_type b() const { return getYIntercept(); };
    float_type getYIntercept() const { return begin().b(m()); };
    
    // angle between the two points
    Radians theta() const { return getTheta(); };
    Radians getTheta() const { return begin().getTheta(end()); };
    
    // Equality
    bool operator ==(const this_t &rhs) const
    { return equal(rhs); };
    bool equal(const this_t &rhs) const
    { return _begin == rhs._begin && _end == rhs._end; };

    // Default assignment to self
};

// ostream streamer
std::ostream &operator <<(std::ostream &out, const Segment &s)
{
    out << '(' << s.begin() << ")-(" << s.end() << ')';
    return out;
}

} // namespace g2d 

#endif
