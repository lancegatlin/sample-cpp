#ifndef __G_MATRIX_TIER3_OPS
#define __G_MATRIX_TIER3_OPS

/*
    File: g_matrix_tier3_ops.h
    Author: lance.gatlin@yahoo.com
    Date: 19 Sep 2008
    Version: 1

    Overview: 
	1) Declares and implments +=, -=, *= operation for matrix arrays
*/

namespace g_matrix {

// workaround typedef for return type of MatrixArray ops
template<unsigned long ROWS, unsigned long COLUMNS>
struct matrix_array {
    typedef g_matrix::float_type (&reference)[ROWS][COLUMNS];
    typedef const g_matrix::float_type (&const_reference)[ROWS][COLUMNS];
};


} // namespace g_matrix

// MatrixArray += ConceptMatrix
template<unsigned long ROWS, unsigned long COLUMNS, class ConceptMatrix2>
inline typename g_matrix::matrix_array<ROWS,COLUMNS>::reference operator +=(g_matrix::float_type (&lhs)[ROWS][COLUMNS], const ConceptMatrix2 &rhs)
{ g_matrix::matrix_add(lhs, rhs, lhs); return lhs; }

// MatrixArray -= ConceptMatrix
template<unsigned long ROWS, unsigned long COLUMNS, class ConceptMatrix2>
inline typename g_matrix::matrix_array<ROWS,COLUMNS>::reference operator -=(g_matrix::float_type (&lhs)[ROWS][COLUMNS], const ConceptMatrix2 &rhs)
{ g_matrix::matrix_subtract(lhs, rhs, lhs); return lhs; }

// MatrixArray *= ConceptMatrix
template<unsigned long ROWS, unsigned long COLUMNS, class ConceptMatrix2>
inline typename g_matrix::matrix_array<ROWS,COLUMNS>::reference operator *=(g_matrix::float_type (&lhs)[ROWS][COLUMNS], const ConceptMatrix2 &rhs)
{ g_matrix::matrix_multiply_equal(lhs, rhs); return lhs; }

#endif
