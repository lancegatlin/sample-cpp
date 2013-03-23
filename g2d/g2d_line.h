#ifndef __G2D_LINE_H
#define __G2D_LINE_H

#include <g2d/g2d_point.h>

/*
    File: g2d_line.h
    Author: lance.gatlin@yahoo.com
    Date: 01 Aug 2008
    Version: 1
    
    Overview: 
        1) Declares class Line to represent a line in 2d space. Represents 
        a line as a Slope and a float_type (ay - bx - c = 0). Provides:
                a) Constructors: Default, DNE, (a,b,c float_type) (Point, Point)
                ,(Segment)
                b) Default copy constructor
                c) Accessors for slope, a,b,c and y,m,b of y=mx+b
                d) Accessors to test if line is vertical/horizontal
                e) Function to calculate the y-intercept and x-intercept
                f) Function to calculate the point of intersection of two lines
                g) Function to calculate the y value given an x value (y=mx+b)
                h) Function to test if a point lies on a line
                e) Equality to self (equal, operator ==)
                f) Assignment to Segment (assign, operator =)
                g) Default assignment to self
                h) ostream streamer (operator <<)
*/

namespace g2d {
    
// ay - bx - c =0
// ay=bx+c
// y= bx/a + c/a
// m = b/a
// b(y-intercept) = c/a
class Line {
    Slope _slope; // _slope.x = a ; slope.y = b so that m=b/a
    float_type _c; 
    
    public:
    typedef Line this_t;
    
    // Constructors
    Line() { };
    
    Line(DoesNotExist dne) 
    : _slope(dne), _c(dne) { };
    
    Line(float_ptype __a=0, float_ptype __b=0,float_ptype __c=0) 
    // m=b/a so a must be x value and b must be y value to get m=y/x
    : _slope(__a,__b), _c(__c) { };
    
    Line(const Point &p1, const Point &p2)
    { *this = Segment(p1,p2); }
    
    Line(const Segment &s)
    { *this = s; }
    
    // Default copy constructor
    
    // Accessors
    Slope slope() const { return _slope; };
    void slope(const Slope &s) { _slope = s; };
    
    float_ptype a() const { return slope().x(); };
    float_ptype b() const { return slope().y(); };
    float_ptype c() const { return _c; };
    void a(float_ptype f) { slope().x(f); };
    void b(float_ptype f) { slope().y(f); };
    void c(float_ptype f) { _c = f; };

    bool isVertical() const 
    { return fequal(a(),0); };
    
    bool isHorizontal() const 
    { return fequal(b(),0); };
    
    
    // y=mx+b
    float_type m() const { return slope().m(); };
    float_type getSlope() const { return slope().m(); };
    float_type y_b() const { return getYIntercept(); };
    
    // y-intercept
    float_type getYIntercept() const 
    { 
        if(isVertical())
            return DoesNotExist();
        else if(isHorizontal())
            return c();
            
        return c()/a(); 
    };

    // x-intercept
    float_type getXIntercept() const 
    { 
        if(isVertical())
            return c();
        else if(isHorizontal())
            return DoesNotExist();
        // ay-bx-c=0
        // a0-bx-c=0
        // -bx=c
        // x=c/-b
        
        return c() / -b();
    };

    // get the slope that is perpendicular to this lines slope
    Slope getPerpendicularSlope() const
    { return Slope(-b(),a()); }
    
    // Calculate the point of intersection of two lines
    Point getIntersectionPointWith(const Line &l) const
    {
/*
        This method should work, but in the end you have to convert to 
        slope intercept anyways to calculate y from x
        
        // a1y-b1x-c1=0
        // a2y-b2x-c1=0
        // a1=a2*N
        // N=a1/a2
        // Subtract the equations to cancel y
        // a1y-b1x-c1=0
        // - N[a2y-b2x-c2]=0
        // b=-b1+(b2*N)
        // c=-c1+c2
        // bx+c=0
        // bx=-c
        // x=-c/b
        
        // ay-bx-c=0
        // ay-bx-c=0
        // ay=bx+c
        float_type a1=a(),b1=b(),c1=c();
        float_type a2=l.a(),b2=l.b(),c2=l.c();
        
        float_type n = a1/a2;
        float_type b = -b1 + (b2 * n);
        float_type c = -c1+c2;
        
        if(b == 0)
            return Point(DoesNotExist());
            
        float_type x = -c/b;
        
        return Point(x,*this(x));*/

        // y=m1(x) + b1
        // y=m2(x) + b2
        // m1(x) + b1 = m2(x) + b2
        // m1(x) - m2(x) = b2 - b1
        // x(m1-m2) = b2 - b1
        // x = b2 - b1
        //     -------
        //     m1- m2
        
        float_type m1 = m(), m2 = l.m();
        float_type b1 = b(), b2 = l.b();

        float_type dm = m1 - m2;
        if(fequal(dm,0))
            return Point(DoesNotExist());
        float_type x = (b2 - b1) / dm;
        float_type y = m1 * x + b1;
        return Point(x,y);
    }
    
    // Get y value from x value (y=mx+b)
    float_type getYFromX(float_type x) const
    {
        return m() * x + b();
    }
    float_type operator()(float_type x) const
    { return getYFromX(x); };
    
    // Get value of ay-bx-c given a point
    // 0 = point lies on the line +/- above/below line
    float_type getValueFromPoint(const Point &p) const
    { 
        return a() * p.y() - b() * p.x() - c();
    }
    float_type operator()(const Point &p) const
    { return getValueFromPoint(p); };
    
    // Equality
    bool operator == (const this_t &rhs) const
    { return compare(rhs); };
    bool compare(const this_t &rhs) const
    {
        return slope() == rhs.slope() && fequal(c(), rhs.c());
    }
    
    // Assignment     
    this_t &operator= (const Segment &s)
    { assign(s); return *this; };
    void assign(const Segment &s)
    {
        // ay - bx - c = 0
        // -c = bx - ay
        // c = ay - bx
        slope(s.end() - s.begin());
        
        // If this is a vertical line 
        if(isVertical())
        {
            // _c stores the x position
            c(s.begin().x());
            // Standardize slope for comparisions to other vertical lines
            slope(Slope(0,1));
        }
        else if(isHorizontal())
        {
            // _c stores the y position
            c(s.begin().y());
            // Standardize slope for comparisions to other horizontal lines
            slope(Slope(1,0));
        }
        // Otherwise calculate c normally
        else 
        {
            c(a() * s.begin().y() - b() * s.begin().x());
        }
    }
    
    // Default assignment to self
};

// ostream streamer
std::ostream &operator << (std::ostream &out, const Line &l)
{
    out << "y=[" << l.m() << "]x + " << l.b();
    return out;
}

} // namespace g2d

#endif
