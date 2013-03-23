#ifndef __G2D_COLUMN_VECTOR_H
#define __G2D_COLUMN_VECTOR_H

#include <g2d/g2d_global.h>
#include <g_global/g_column_vector.h>

/*
    File: g2d_column_vector.h
    Author: lance.gatlin@yahoo.com
    Date: 01 Aug 2008
    Version: 1
    
    Overview: 
        1) Declares g2d::ColumnVector as a typedef of AnyColumnVector with 3
        columns
*/

namespace g2d {
    
typedef ::g_global::AnyColumnVector<3> ColumnVector;

} // namespace g2d


#endif
