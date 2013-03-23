#ifndef __G3D_ROTATION_MATRIX_H
#define __G3D_ROTATION_MATRIX_H

#include <g3d/g3d_unit_vector.h>
#include <g3d/g3d_matrix.h>
#include <g_global/g_trig.h>

/*
    File: g3d_rotation_matrix.h
    Author: lance.gatlin@yahoo.com
    Date: 01 Aug 2008
    Version: 1
    
    Overview: 
        1) XRotationMatrix provides a matrix to rotate an object about the 
        x-axis by an angle argument passed to the constructor. Derived from 
        Matrix. Provides:
                a) Constructor: angle float_type 
                b) Default copy constructor
                c) Default assignment to self
                b) Inherits from Matrix
        2) YRotationMatrix provides a matrix to rotate an object about the 
        y-axis by an angle argument passed to the constructor. Derived from 
        Matrix. Provides:
                a) Constructor: angle float_type 
                b) Default copy constructor
                c) Default assignment to self
                b) Inherits from Matrix
        3) ZRotationMatrix provides a matrix to rotate an object about the 
        z-axis by an angle argument passed to the constructor. Derived from 
        Matrix. Provides:
                a) Constructor: angle float_type 
                b) Default copy constructor
                c) Default assignment to self
                b) Inherits from Matrix
        4) RotationMatrix provides a matrix to rotate an object about all 
        axes by rotating a particular angle around a given unit vector. Both
        arguments are passed to the constructor. Derived from Matrix. Provides:
                a) Constructor: (UnitVector, angle float_type)
                b) Default copy constructor
                c) Default assignment to self
                b) Inherits from Matrix
            
*/

namespace g3d {
    
class XRotationMatrix : public Matrix {
    public:
    // Constructors
    XRotationMatrix(const Radians &beta)
    {
        m[0][0] = 1; m[0][1] = 0; m[0][2] = 0; m[0][3] = 0;
        m[1][0] = 0; m[1][1] = cosine(beta); m[1][2] = -sine(beta); m[1][3] = 0;
        m[2][0] = 0; m[2][1] = sine(beta); m[2][2] = cosine(beta); m[2][3] = 0;
        m[3][0] = 0; m[3][1] = 0; m[3][2] = 0; m[3][3] = 1;
    }
    // Default copy constructor
    
    // Default assignment to self
};

class YRotationMatrix : public Matrix {
    public:
    // Constructors
    YRotationMatrix(const Radians &beta)
    {
        m[0][0] = cosine(beta); m[0][1] = 0; m[0][2] = sine(beta); m[0][3] = 0;
        m[1][0] = 0; m[1][1] = 1; m[1][2] = 0; m[1][3] = 0;
        m[2][0] = -sine(beta); m[2][1] = 0; m[2][2] = cosine(beta); m[2][3] = 0;
        m[3][0] = 0; m[3][1] = 0; m[3][2] = 0; m[3][3] = 1;
    }
    // Default copy constructor
    
    // Default assignment to self
};


class ZRotationMatrix : public Matrix {
    public:
    // Constructors
    ZRotationMatrix(const Radians &beta)
    {
        m[0][0] = cosine(beta); m[0][1] = -sine(beta); m[0][2] = 0; m[0][3] = 0;
        m[1][0] = sine(beta); m[1][1] = cosine(beta); m[1][2] = 0; m[1][3] = 0;
        m[2][0] = -sine(beta); m[2][1] = 0; m[2][2] = 1; m[2][3] = 0;
        m[3][0] = 0; m[3][1] = 0; m[3][2] = 0; m[3][3] = 1;
    }
    // Default copy constructor
    
    // Default assignment to self
};

class RotationMatrix : public Matrix {
    public:
    // Constructors
    RotationMatrix(const UnitVector &v, const Radians &beta)
    {
/*        float_type c = cosine(beta);
        float_type s = sine(beta);
        float_type t = 1 - c;
        float_type X = v.x();
        float_type Y = v.y();
        float_type Z = v.z();
        float_type XX = X * X;
        float_type YY = Y * Y;
        float_type ZZ = Z * Z;
        
        m[0][0] = t * XX + c; m[0][1] = t * X * Y - s * Z; m[0][2] = t * X * Z + s * Y; m[0][3] = 0;
        m[1][0] = t * X * Y + s * Z; m[1][1] = t * YY + c; m[1][2] = t * Y * Z - s * X; m[1][3] = 0;
        m[2][0] = t * X * Z - s * Y; m[2][1] = t * Y * Z + s * X; m[2][2] = t * ZZ + c; m[2][3] = 0;
        m[3][0] = 0; m[3][1] = 0; m[3][2] = 0; m[3][3] = 1;
        */
    }
    // Default copy constructor
    
    // Default assignment to self
};

} // namespace g2d

#endif
