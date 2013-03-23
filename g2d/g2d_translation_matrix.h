#ifndef __G2D_TRANSLATION_MATRIX_H
#define __G2D_TRANSLATION_MATRIX_H

#include <g2d/g2d_matrix.h>

/*
    File: g2d_translation_matrix.h
    Author: lance.gatlin@yahoo.com
    Date: 01 Aug 2008
    Version: 1
    
    Overview: 
        1) Declares class TranslationMatrix which is used to translate 
        (relocate) objects in 2d space. Derived from Matrix. Provides:
                a) Constructors: (x,y float_type)
                b) Uses default copy constructor
                c) Uses default assignment to self
                
*/

namespace g2d {
    
class TranslationMatrix : public Matrix {
    public:
    TranslationMatrix(float_ptype tx, float_type ty)
    {
        m[0][0] = 1; m[0][1] = 0; m[0][2] = -tx;
        m[1][0] = 0; m[1][1] = 1; m[1][2] = -ty;
        m[2][0] = 0; m[2][1] = 0; m[2][2] = 1;
    }
    
    // Default copy constructor
    
    // Default assignment to self
};


} // namespace g2d

#endif
