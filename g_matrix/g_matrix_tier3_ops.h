/*
    File: g_matrix_tier3_ops.h
    Author: lance.gatlin@yahoo.com
    Date: 19 Sep 2008
    Version: 1

    Overview: 
	1) Declares and implements +=, -=, *= operation for matrix arrays
*/

// MatrixArray += ConceptMatrix
template<unsigned long ROWS, unsigned long COLUMNS, class ConceptMatrix2>
inline typename g_matrix::MatrixConcept<g_matrix::float_type[ROWS][COLUMNS]>::reference operator +=(g_matrix::float_type (&lhs)[ROWS][COLUMNS], const ConceptMatrix2 &rhs)
{ g_matrix::matrix_add(lhs, rhs, lhs); return lhs; }

// MatrixArray -= ConceptMatrix
template<unsigned long ROWS, unsigned long COLUMNS, class ConceptMatrix2>
inline typename g_matrix::MatrixConcept<g_matrix::float_type[ROWS][COLUMNS]>::reference operator -=(g_matrix::float_type (&lhs)[ROWS][COLUMNS], const ConceptMatrix2 &rhs)
{ g_matrix::matrix_subtract(lhs, rhs, lhs); return lhs; }

// MatrixArray *= ConceptMatrix
template<unsigned long ROWS, unsigned long COLUMNS, class ConceptMatrix2>
inline typename g_matrix::MatrixConcept<g_matrix::float_type[ROWS][COLUMNS]>::reference operator *=(g_matrix::float_type (&lhs)[ROWS][COLUMNS], const ConceptMatrix2 &rhs)
{ g_matrix::matrix_multiply_equal(lhs, rhs); return lhs; }
