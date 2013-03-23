#ifndef __G_MATRIX_TIER4_OPS_H
#define __G_MATRIX_TIER4_OPS_H

/*
    File: g_matrix_tier4_ops.h
    Author: lance.gatlin@yahoo.com
    Date: 19 Sep 2008
    Version: 1

    Overview: 
	1) Declares and implements |=, +=, -=, *=, /= and ostream << for MatrixRow and MatrixColumn
*/

/********************************* Row Ops ************************************/
// Row op-equal functions are pass "by value" since a Row is really an alias(pointer) for a ConceptMatrix

// Row |= ConceptMatrix
template<class ConceptMatrix1, class ConceptMatrix2>
inline g_matrix::MatrixRow<ConceptMatrix1> operator |=(g_matrix::MatrixRow<ConceptMatrix1> lhs, const ConceptMatrix2 &rhs)
{ g_matrix::matrix_column_merge(rhs, lhs); return lhs; }

// Row += ConceptMatrix
template<class ConceptMatrix1, class ConceptMatrix2>
inline g_matrix::MatrixRow<ConceptMatrix1> operator +=(g_matrix::MatrixRow<ConceptMatrix1> lhs, const ConceptMatrix2 &rhs)
{ g_matrix::matrix_add(lhs, rhs, lhs); return lhs; }

// Row -= ConceptMatrix
template<class ConceptMatrix1, class ConceptMatrix2>
inline g_matrix::MatrixRow<ConceptMatrix1> operator -=(g_matrix::MatrixRow<ConceptMatrix1> lhs, const ConceptMatrix2 &rhs)
{ g_matrix::matrix_subtract(lhs, rhs, lhs); return lhs; }

// Row *= ConceptMatrix
template<class ConceptMatrix1, class ConceptMatrix2>
inline g_matrix::MatrixRow<ConceptMatrix1> operator *=(g_matrix::MatrixRow<ConceptMatrix1> lhs, const ConceptMatrix2 &rhs)
{ g_matrix::matrix_multiply_equal(lhs, rhs); return lhs; }

// Row *= float_type
template<class ConceptMatrix>
inline g_matrix::MatrixRow<ConceptMatrix> operator *=(g_matrix::MatrixRow<ConceptMatrix> lhs, g_matrix::float_ptype rhs)
{ g_matrix::matrix_multiply(lhs, rhs, lhs); return lhs; }

// Row /= float_type
template<class ConceptMatrix>
inline g_matrix::MatrixRow<ConceptMatrix> operator /=(g_matrix::MatrixRow<ConceptMatrix> lhs, g_matrix::float_ptype rhs)
{ g_matrix::matrix_divide(lhs,rhs); return lhs; }

// output text dump of matrix content
template<class ConceptMatrix>
inline std::ostream &operator <<(std::ostream &lhs, g_matrix::MatrixRow<ConceptMatrix> rhs)
{ return g_matrix::matrix_dump(lhs, rhs); }

/********************************* Column Ops ************************************/
// Column op-equal functions are pass "by value" since a Column is really an alias(pointer) for a ConceptMatrix

// Column |= ConceptMatrix
template<class ConceptMatrix1, class ConceptMatrix2>
inline g_matrix::MatrixColumn<ConceptMatrix1> operator |=(g_matrix::MatrixColumn<ConceptMatrix1> lhs, const ConceptMatrix2 &rhs)
{ g_matrix::matrix_column_merge(rhs, lhs); return lhs; }

// Column += ConceptMatrix
template<class ConceptMatrix1, class ConceptMatrix2>
inline g_matrix::MatrixColumn<ConceptMatrix1> operator +=(g_matrix::MatrixColumn<ConceptMatrix1> lhs, const ConceptMatrix2 &rhs)
{ g_matrix::matrix_add(lhs, rhs, lhs); return lhs; }

// Column -= ConceptMatrix
template<class ConceptMatrix1, class ConceptMatrix2>
inline g_matrix::MatrixColumn<ConceptMatrix1> operator -=(g_matrix::MatrixColumn<ConceptMatrix1> lhs, const ConceptMatrix2 &rhs)
{ g_matrix::matrix_subtract(lhs, rhs, lhs); return lhs; }

// Column *= ConceptMatrix
template<class ConceptMatrix1, class ConceptMatrix2>
inline g_matrix::MatrixColumn<ConceptMatrix1> operator *=(g_matrix::MatrixColumn<ConceptMatrix1> lhs, const ConceptMatrix2 &rhs)
{ g_matrix::matrix_multiply_equal(lhs, rhs); return lhs; }

// Column *= float_type
template<class ConceptMatrix>
inline g_matrix::MatrixColumn<ConceptMatrix> operator *=(g_matrix::MatrixColumn<ConceptMatrix> lhs, g_matrix::float_ptype rhs)
{ g_matrix::matrix_multiply(lhs, rhs, lhs); return lhs; }

// Column /= float_type
template<class ConceptMatrix>
inline g_matrix::MatrixColumn<ConceptMatrix> operator /=(g_matrix::MatrixColumn<ConceptMatrix> lhs, g_matrix::float_ptype rhs)
{ g_matrix::matrix_divide(lhs,rhs); return lhs; }

// output text dump of matrix content
template<class ConceptMatrix>
inline std::ostream &operator <<(std::ostream &lhs, g_matrix::MatrixColumn<ConceptMatrix> rhs)
{ return g_matrix::matrix_dump(lhs, rhs); }

#endif
