#ifndef __G2D_POINT_H
#define __G2D_POINT_H

#include <ostream>
#include <g2d/g2d_global.h>
#include <g_global/g_trig.h>

/*
    File: g2d_point.h
    Author: lance.gatlin@yahoo.com
    Date: 01 Aug 2008
    Version: 1
    
    Overview: 
        1) Declares class Point which represents a point in 2d space with a
        x and y float_type value. Provides:
                a) Constructors: Default, DNE, Radians, (x,y,z float_type)
                b) Uses default copy constructor
                c) Accessors for x,y,z
                d) Function to calculate distance to origin (0,0) or a 
                specified point
                e) Function to calculate slope between origin and point
                f) Function to calculate slope between two points
                g) Function to calculate y-intercept given a slope and point
                h) Function to test if a point exists
                i) Function to calculate the angle the angle between two points
                j) Function to calculate the angle the angle between origin and 
                this point
                f) Equality (equal, operator ==)
                g) Uses default assignment to self
                h) Comparision (compare, operator <)
                i) Math operations Point<->Point or Point<->float_type (+,-,*,/)
                j) ostream stream (operator <<)
        2) Declares g2d::Slope to be a typedef of Point
*/

namespace g2d {
    
class Point {
    float_type _x,_y;
    
    public:
    typedef Point this_t;

    // Constructors
    Point(DoesNotExist dne)
    : _x(dne), _y(dne) { };
    
    Point(
        float_ptype __x = 0
        ,float_ptype __y = 0
    )
    : _x(__x), _y(__y) { };
    
    Point(Radians __angle)
    : _x(cosine(__angle)), _y(sine(__angle)) { };

    Point(Degrees __angle)
    : _x(cosine(__angle)), _y(sine(__angle)) { };
    
    // Default copy constructor
    
    // Accessors
    float_ptype x() const { return _x; };
    float_ptype y() const { return _y; };
    void x(float_ptype f) { _x = f; };
    void y(float_ptype f) { _y = f; };
    
    // distance to origin?
    float_type d() const { return getDistanceToOrigin(); };
    float_type getDistanceToOrigin() const
    {
        return std::sqrt(_x*_x+_y*_y);
    }

    // distance to a point?
    float_type d(const Point &p2) const { return getDistanceTo(p2); };
    float_type getDistanceTo(const Point &p2) const
    {
        float_type xv = p2.x() - x();
        float_type yv = p2.y() - y();
        return std::sqrt(xv*xv+yv*yv);
    }
    
    // slope between origin and point?
    float_type m() const { return getSlope(); };
    float_type getSlope() const
    {
        if(fequal(x(),0))
            return DoesNotExist();
            
        return y() / x();
    }
    
    // slope between two points?
    float_type m(const Point &p2) const { return getSlopeTo(p2); };
    float_type getSlopeTo(const Point &p2) const
    {
        // Y2-Y1
        //------
        // X2-X1
        float_type dx = p2.x() - x();
        
        if(fequal(dx,0))
            return DoesNotExist();
            
        return (p2.y() - y()) / dx;
    }
    
    // given a slope, y-intercept?
    float_type b(float_ptype m) const { return getYInterceptWith(m); };
    float_type getYInterceptWith(float_ptype m) const
    {
        // y=mx+b
        // b=y-mx
        return y()-(m*x());
    }
    
    // point exists?
    bool exists() const
    { return fexists(x()) && fexists(y()); }

    // Calculate angle from origin
    Radians theta() const { return getTheta(); };
    Radians getTheta() const 
    {
        float_type theta, _dx = x(), _dy = y();
        
        // Handle vertical line
        if ( fequal(_dx,0) )
        {
            // If end y is greater than begin y
            if ( fequal(y(),0) )
                // Veritcal line points upward
                theta = (3.0/2)*PI;
            else
                // Veritcal line points downward
                theta = (1.0/2)*PI;
        }
        else
        {
            // Use arctan to get angle of segment
            theta = std::atan( _dy/_dx );
            
            // If end x is greater than begin x
            if ( fgreater(x(), 0) )
                // Fix theta for quads 1/2
                return theta;
            else
                // Fix theta for quads 3/4
                theta = PI + theta;
        };
        
        return theta;
    };

    
    // Calculate angle between two points
    Radians theta(const Point &end) const { return theta(end); };
    Radians getTheta(const Point &end) const;

    // Equality
    bool operator ==(const this_t &rhs) const 
    { return compare(rhs); };
    bool compare(const this_t &rhs) const
    { return    fequal(x(), rhs.x()) && fequal(y(), rhs.y()); };
                
    // Default assignment to self    
};

// Point + Point
Point operator +(const Point &lhs, const Point &rhs)
{
    return Point(lhs.x() + rhs.x(), lhs.y() + rhs.y());
}

// Point += Point
Point &operator +=(Point &lhs, const Point &rhs)
{
    return lhs = lhs + rhs;
}

// Point - Point
Point operator -(const Point &lhs, const Point &rhs)
{
    return Point(lhs.x() - rhs.x(), lhs.y() - rhs.y());
}

// Point -= Point
Point &operator -=(Point &lhs, const Point &rhs)
{
    return lhs = lhs - rhs;
}

// Point * Point
Point operator *(const Point &lhs, float_ptype rhs)
{
    return Point(lhs.x() * rhs, lhs.y() * rhs);
}

// Point *= Point
Point &operator *=(Point &lhs, float_ptype rhs)
{
    return lhs = lhs * rhs;
}

// Point / Point
Point operator /(const Point &lhs, float_ptype rhs)
{
    return Point(lhs.x() / rhs, lhs.y() / rhs);
}

// Point /= Point
Point &operator /=(Point &lhs, float_ptype rhs)
{
    return lhs = lhs / rhs;
}

// ostream streamer
std::ostream &operator <<(std::ostream &out, const Point &p)
{
    out << p.x() << ',' << p.y();
    return out;
}

// Implementation
inline Radians Point::getTheta(const Point &end) const 
{
    Point d = end - *this;
    return d.theta();
}

typedef Point Slope;

} // namespace g2d

#endif
