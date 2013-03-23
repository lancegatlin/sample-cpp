#ifndef __G3D_SCALING_MATRIX_H
#define __G3D_SCALING_MATRIX_H

#include <g3d/g3d_matrix.h>

/*
    File: g3d_scaling_matrix.h
    Author: lance.gatlin@yahoo.com
    Date: 01 Aug 2008
    Version: 1
    
    Overview: 
        1) Declares class ScalingMatrix which is used to scale objects in 3d
        space. Derived from Matrix. Provides:
                a) Constructors: (scaling factor float_type), 
                (x,y,z scaling factors float_type)
                b) Uses default copy constructor
                c) Uses default assignment to self
                
*/

namespace g3d {
    
class ScalingMatrix : public Matrix {
    public:
    // Constructors
    ScalingMatrix(float_ptype s)
    {
        m[0][0] = s; m[0][1] = 0; m[0][2] = 0; m[0][3] = 0;
        m[1][0] = 0; m[1][1] = s; m[1][2] = 0; m[1][3] = 0;
        m[2][0] = 0; m[2][1] = 0; m[2][2] = s; m[2][3] = 0;
        m[3][0] = 0; m[3][1] = 0; m[3][2] = 0; m[3][3] = 1;
    }
    
    ScalingMatrix(float_ptype sx, float_ptype sy, float_ptype sz)
    {
        m[0][0] = sx; m[0][1] = 0; m[0][2] = 0; m[0][3] = 0;
        m[1][0] = 0; m[1][1] = sy; m[1][2] = 0; m[1][3] = 0;
        m[2][0] = 0; m[2][1] = 0; m[2][2] = sz; m[2][3] = 0;
        m[3][0] = 0; m[3][1] = 0; m[3][2] = 0; m[3][3] = 1;
    }
    // Default copy constructor
    
    // Default assignment to self
};


} // namespace g3d

#endif
