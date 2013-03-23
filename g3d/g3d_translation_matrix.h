#ifndef __G3D_TRANSLATION_MATRIX_H
#define __G3D_TRANSLATION_MATRIX_H

#include <g3d/g3d_matrix.h>

/*
    File: g3d_translation_matrix.h
    Author: lance.gatlin@yahoo.com
    Date: 01 Aug 2008
    Version: 1
    
    Overview: 
        1) Declares class TranslationMatrix which is used to translate 
        (relocate) objects in 3d space. Derived from Matrix. Provides:
                a) Constructors: (x,y,z float_type)
                b) Uses default copy constructor
                c) Uses default assignment to self
                
*/

namespace g3d {
    
class TranslationMatrix : public Matrix {
    public:
    // Constructors
    TranslationMatrix(float_ptype tx, float_type ty, float_type tz)
    {
        m[0][0] = 1; m[0][1] = 0; m[0][2] = 0; m[0][3] = -tx;
        m[1][0] = 0; m[1][1] = 1; m[1][2] = 0; m[1][3] = -ty;
        m[2][0] = 0; m[2][1] = 0; m[2][2] = 1; m[2][3] = -tz;
        m[3][0] = 0; m[3][1] = 0; m[3][2] = 0; m[3][3] = 1;
    }
    // Default copy constructor
    
    // Default assignment to self
};


} // namespace g2d

#endif
