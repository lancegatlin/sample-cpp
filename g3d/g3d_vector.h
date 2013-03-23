#ifndef __G3D_VECTOR_H
#define __G3D_VECTOR_H

#include <g3d/g3d_point.h>
#include <g3d/g3d_column_vector.h>
#include <g3d/g3d_matrix.h>

/*
    File: g3d_vector.h
    Author: lance.gatlin@yahoo.com
    Date: 01 Aug 2008
    Version: 1
    
    Overview: 
        1) Declares class Vector which represents a vector in 3d space as a
        point. Derived from Point. Provides:
                a) Constructors: Default/DNE, (Point), (x,y,z float_type)
                b) Uses default copy constructor
                c) Accessors for magnitude and direction
                d) Calculation functions: dotproduct and crossproduct
                e) Function to make the vector a distance of 1 from origin 
                (unit vector)
                g) Uses default assignment to self
                i) Math operations Vector<->Vector or Vector<->float_type 
                (+,-,*,/)
                j) Math operations Vector<->Matrix (*)
        2) Declares g3d::Ray as a typedef of Vector
                
*/

namespace g3d {
    
class Vector : public Point {
    public:
    // Constructors
    Vector(DoesNotExist dne) : Point(dne) { };
    Vector(const Point &p) : Point(p) { };
    Vector(float_ptype __x=0, float_ptype __y=0, float_ptype __z=0)
    : Point(__x, __y, __z) { };
    
    // Default copy constructor
    
    // Accessors
    float_type magnitude() const { return Point::d(); };
    Vector direction() const { return getUnitVector(); };
    
    // Calculations
    float_type dotproduct(const Vector &v) const 
    { 
        return x() * v.x() + y() * v.y() + z() * v.z(); 
    };
    
    Vector crossproduct(const Vector &v) const 
    {
        return Vector(  
                        y() * v.z() - z() * v.y()
                        ,z() * v.x() - x() * v.z()
                        ,x() * v.y() - y() * v.x()
                    );
    }
    
    // Turn vector into length 1 from origin
    void makeUnitVector()
    {
        float_type _d = d();
        *this = Vector(x()/_d, y()/_d, z()/_d);
    }
    
    Vector getUnitVector() const
    {
        float_type _d = d();
        return Vector(x()/_d, y()/_d, z()/_d);
    }
    
    // Default assignment to self
};

// Vector % Vector (distance between two vectors)
inline float_type operator %(const Vector &lhs, const Vector &rhs)
{ return lhs.d(rhs); };
// Vector * Vector (dotproduct)
inline float_type operator *(const Vector &lhs, const Vector &rhs)
{ return lhs.dotproduct(rhs); }

// The following is exactly the same as Point above
// It is repeated for Vector to ensure when applying vector operators
// a Vector type is returned
// Vector + Vector
inline Vector operator +(const Vector &lhs, const Vector &rhs)
{
    return Vector(lhs.x() + rhs.x(), lhs.y() + rhs.y(), lhs.z() + rhs.z());
}

// Vector += Vector
inline Vector &operator +=(Vector &lhs, const Vector &rhs)
{
    return lhs = lhs + rhs;
}

// Vector - Vector
inline Vector operator -(const Vector &lhs, const Vector &rhs)
{
    return Vector(lhs.x() - rhs.x(), lhs.y() - rhs.y(), lhs.z() - rhs.z());
}

// Vector -= Vector
inline Vector &operator -=(Vector &lhs, const Vector &rhs)
{
    return lhs = lhs - rhs;
}

// Vector * float_type
inline Vector operator *(const Vector &lhs, float_type rhs)
{
    return Vector(lhs.x() * rhs, lhs.y() * rhs, lhs.z() * rhs);
}

// float_type * Vector
inline Vector operator *(float_type lhs, const Vector &rhs)
{
    return Vector(rhs.x() * lhs, rhs.y() * lhs, rhs.z() * lhs);
}

// Vector *= float_type
inline Vector &operator *=(Vector &lhs, float_type rhs)
{
    return lhs = lhs * rhs;
}

// Vector / float_type
inline Vector operator /(const Vector &lhs, float_type rhs)
{
    return Vector(lhs.x() / rhs, lhs.y() / rhs, lhs.z() / rhs);
}

// Vector / float_type
inline Vector &operator /=(Vector &lhs, float_type rhs)
{
    return lhs = lhs / rhs;
}

// Vector * Matrix
inline Vector operator *(const Vector &lhs, const Matrix &rhs)
{
    ColumnVector v;
    v[0] = lhs.x();
    v[1] = lhs.y();
    v[2] = lhs.z();
    v[3] = 1;
    v *= rhs;
    
    return Vector(v[0], v[1], v[2]);
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

// Vector is also a ray
typedef Vector Ray;

} // namespace g3d
#endif
