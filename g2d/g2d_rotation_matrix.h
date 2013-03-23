#ifndef __G2D_ROTATION_MATRIX_H
#define __G2D_ROTATION_MATRIX_H

#include <g2d/g2d_matrix.h>

/*
    File: g3d_rotation_matrix.h
    Author: lance.gatlin@yahoo.com
    Date: 01 Aug 2008
    Version: 1
    
    Overview: 
        1) RotationMatrix provides a matrix to rotate an object about both
        axes by rotating at a particular angle. Derived from Matrix. Provides:
                a) Constructor: (angle float_type)
                b) Default copy constructor
                c) Default assignment to self
                b) Inherits from Matrix
            
*/

namespace g2d {
    
class RotationMatrix : public Matrix {
    public:
    RotationMatrix(const Radians &beta)
    {
        m[0][0] = cosine(beta); m[0][1] = sine(beta); m[0][2] = 0;
        m[1][0] = -sine(beta); m[1][1] = cosine(beta); m[1][2] = 0;
        m[2][0] = cosine(beta); m[2][1] = sine(beta); m[2][2] = 1;
    }
    
    // Default copy constructor
    
    // Default assignment to self
};

} // namespace g2d

#endif
