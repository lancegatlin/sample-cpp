#ifndef __G2D_VECTOR_H
#define __G2D_VECTOR_H

#include <g2d/g2d_point.h>
#include <g2d/g2d_column_vector.h>
#include <g2d/g2d_matrix.h>

/*
    File: g2d_vector.h
    Author: lance.gatlin@yahoo.com
    Date: 01 Aug 2008
    Version: 1
    
    Overview: 
        1) Declares class Vector which represents a vector in 2d space as a
        point. Derived from Point. Provides:
                a) Constructors: Default, DNE, (Point), (x,y float_type)
                b) Uses default copy constructor
                c) Accessors for magnitude and direction
                d) Calculation functions: dotproduct and crossproduct
                e) Function to make the vector a distance of 1 from origin 
                (unit vector)
                g) Uses default assignment to self
                i) Math operations Vector<->Vector or Vector<->float_type 
                (+,-,*,/)
                j) Math operations Vector<->Matrix (*)
        2) Declares g2d::Ray as a typedef of Vector
                
*/

namespace g2d {
    
class Vector : public Point {
    public:
    Vector(DoesNotExist dne) : Point(dne) { };
    Vector(const Point &p) : Point(p) { };
    Vector(float_ptype __x=0, float_ptype __y=0)
    : Point(__x, __y) { };
    
    // Default copy constructor
    
    // Accessors
    float_type magnitude() const { return Point::d(); };
    Radians direction() const { return theta(); };

    // Calculations
    float_type dotproduct(const Vector &v) const { return x() * v.x() + y() * v.y(); };
    
    void makeUnitVector()
    {
        float_type _d = d();
        x(x()/_d);
        y(y()/_d);
    }
};

// Vector % Vector (distance between two vectors)
float_type operator %(const Vector &lhs, const Vector &rhs)
{ return lhs.d(rhs); };

// Vector * Vector (dotproduct)
float_type operator *(const Vector &lhs, const Vector &rhs)
{ return lhs.dotproduct(rhs); }

// The following is exactly the same as Point above
// It is repeated for Vector to ensure when applying vector operators
// a Vector type is returned
// Vector + Vector
Vector operator +(const Vector &lhs, const Vector &rhs)
{
    return Vector(lhs.x() + rhs.x(), lhs.y() + rhs.y());
}

// Vector += Vector
Vector &operator +=(Vector &lhs, const Vector &rhs)
{
    return lhs = lhs + rhs;
}

// Vector - Vector
Vector operator -(const Vector &lhs, const Vector &rhs)
{
    return Vector(lhs.x() - rhs.x(), lhs.y() - rhs.y());
}

// Vector -= Vector
Vector &operator -=(Vector &lhs, const Vector &rhs)
{
    return lhs = lhs - rhs;
}

// Vector * float_type
Vector operator *(const Vector &lhs, float_type rhs)
{
    return Vector(lhs.x() * rhs, lhs.y() * rhs);
}

// Vector *= float_type
Vector &operator *=(Vector &lhs, float_type rhs)
{
    return lhs = lhs * rhs;
}

// Vector / rhs
Vector operator /(const Vector &lhs, float_type rhs)
{
    return Vector(lhs.x() / rhs, lhs.y() / rhs);
}

// Vector /= rhs
Vector &operator /=(Vector &lhs, float_type rhs)
{
    return lhs = lhs / rhs;
}

// Vector * Matrix
inline Vector operator *(const Vector &lhs, const Matrix &rhs)
{
    ColumnVector v;
    v[0] = lhs.x();
    v[1] = lhs.y();
    v[2] = 1;
    v *= rhs;
    
    return Vector(v[0], v[1]);
}

// Matrix * Vector
inline Vector operator *(const Matrix &lhs, const Vector &rhs)
{
    return rhs * lhs;
}

// Vector *= Matrix
inline Vector &operator *=(Vector &lhs, const Matrix &rhs)
{
    return lhs = lhs * rhs;
}

typedef Vector Ray;

} // namespace g2d
#endif
