#ifndef __G_MATRIX_H
#define __G_MATRIX_H

/*
    File: g_matrix.h
    Author: lance.gatlin@yahoo.com
    Date: 19 Sep 2008
    Version: 2

    Overview: 
	1) Client header entry point        
*/

#include <g_global\g_global.h>

namespace g_matrix {

using namespace g_global;

#include "g_matrix_tier1_stats.h"
#include "g_matrix_tier1_class_MatrixConcept.h"
#include "g_matrix_tier1_exception.h"

#include "g_matrix_tier2_algorithm.h"
#include "g_matrix_tier2_class_MatrixIterator.h"

#include "g_matrix_tier3_class_MatrixDynamicStorage.h"
#include "g_matrix_tier3_class_MatrixStaticStorage.h"

#include "g_matrix_tier4_class_MatrixRow.h"
#include "g_matrix_tier4_class_MatrixColumn.h"

#include "g_matrix_tier6_class_MatrixSlice.h"

#include "g_matrix_tier8_class_AnyMatrix.h"

#include "g_matrix_tier9_class_DynamicMatrix.h"
#include "g_matrix_tier9_class_StaticMatrix.h"

#include "g_matrix_tier10_algorithm.h"

} // namespace g_matrix

#include "g_matrix_tier3_ops.h"
#include "g_matrix_tier5_ops.h"
#include "g_matrix_tier9_ops.h"
#include "g_matrix_tier11_ops.h"

#endif
