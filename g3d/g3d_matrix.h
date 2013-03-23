#ifndef __G3D_MATRIX_H
#define __G3D_MATRIX_H

#include <g3d/g3d_global.h>
#include <g_global/g_matrix.h>
#include <g3d/g3d_column_vector.h>

/*
    File: g3d_matrix.h
    Author: lance.gatlin@yahoo.com
    Date: 01 Aug 2008
    Version: 1
    
    Overview: 
        1) Declares g3d::Matrix as a typedef of template class AnyMatrix with 
        four rows and four columns.
        2) Declares g3d::IdentityMatrix as a typedef of template class 
        AnyIdentityMatrix with four rows and four columns.
*/

namespace g3d {
    
typedef ::g_global::StaticMatrix<4,4> Matrix;

} // namespace g3d

#endif
