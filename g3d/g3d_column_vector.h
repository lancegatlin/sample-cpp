#ifndef __G3D_COLUMN_VECTOR_H
#define __G3D_COLUMN_VECTOR_H

#include <g3d/g3d_global.h>
#include <g_global/g_column_vector.h>

/*
    File: g3d_column_vector.h
    Author: lance.gatlin@yahoo.com
    Date: 01 Aug 2008
    Version: 1
    
    Overview: 
        1) Declares g3d::ColumnVector as a typedef of AnyColumnVector with 4
        columns
*/

namespace g3d {
    
typedef ::g_global::AnyColumnVector<4> ColumnVector;

} // namespace g3d

#endif
