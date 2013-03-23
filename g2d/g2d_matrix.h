#ifndef __G2D_MATRIX_H
#define __G2D_MATRIX_H

#include <g2d/g2d_global.h>
#include <g_global/g_matrix.h>
#include <g2d/g2d_column_vector.h>

/*
    File: g2d_matrix.h
    Author: lance.gatlin@yahoo.com
    Date: 01 Aug 2008
    Version: 1
    
    Overview: 
        1) Declares g2d::Matrix as a typedef of template class AnyMatrix with 
        three rows and three columns.
        2) Declares g2d::IdentityMatrix as a typedef of template class 
        AnyIdentityMatrix with three rows and three columns.
*/

namespace g2d {
    
typedef ::g_global::AnyMatrix<3,3> Matrix;
typedef ::g_global::AnyIdentityMatrix<3,3> IdentityMatrix;

} // namespace g2d

#endif
