/*
    File: g_matrix_tier8_ops.h
    Author: lance.gatlin@yahoo.com
    Date: 19 Sep 2008
    Version: 1

    Overview: 
	1) Declares and implements |=, +=, -=, *=, /= and ostream << for MatrixSlice
*/

/********************************* Slice Ops ************************************/
// Slice op-equal functions are pass "by value" since a Slice is really an alias(pointer) for a ConceptMatrix

// Slice |= ConceptMatrix
template<class ConceptMatrix1, class ConceptMatrix2>
inline g_matrix::MatrixSlice<ConceptMatrix1> operator |=(g_matrix::MatrixSlice<ConceptMatrix1> lhs, const ConceptMatrix2 &rhs)
{ g_matrix::matrix_column_merge(rhs, lhs); return lhs; }

// Slice += ConceptMatrix
template<class ConceptMatrix1, class ConceptMatrix2>
inline g_matrix::MatrixSlice<ConceptMatrix1> operator +=(g_matrix::MatrixSlice<ConceptMatrix1> lhs, const ConceptMatrix2 &rhs)
{ g_matrix::matrix_add(lhs, rhs, lhs); return lhs; }

// Slice -= ConceptMatrix
template<class ConceptMatrix1, class ConceptMatrix2>
inline g_matrix::MatrixSlice<ConceptMatrix1> operator -=(g_matrix::MatrixSlice<ConceptMatrix1> lhs, const ConceptMatrix2 &rhs)
{ g_matrix::matrix_subtract(lhs, rhs, lhs); return lhs; }

// Slice *= float_type
template<class ConceptMatrix>
inline g_matrix::MatrixSlice<ConceptMatrix> operator *=(g_matrix::MatrixSlice<ConceptMatrix> lhs, g_matrix::float_ptype rhs)
{ g_matrix::matrix_multiply(lhs, rhs, lhs); return lhs; }

// Slice /= float_type
template<class ConceptMatrix>
inline g_matrix::MatrixSlice<ConceptMatrix> operator /=(g_matrix::MatrixSlice<ConceptMatrix> lhs, g_matrix::float_ptype rhs)
{ g_matrix::matrix_multiply(lhs,(1/rhs), lhs); return lhs; }

// output text dump of matrix content
template<class ConceptMatrix>
inline std::ostream &operator <<(std::ostream &lhs, g_matrix::MatrixSlice<ConceptMatrix> rhs)
{ return g_matrix::matrix_dump(lhs, rhs); }

// insert streamable version of matrix content
template<class ConceptMatrix>
inline std::ostringstream &operator <<(std::ostringstream &lhs, g_matrix::MatrixSlice<const ConceptMatrix> rhs)
{ return g_matrix::matrix_insert(lhs, rhs); }

// extract streamable version of matrix content
template<class ConceptMatrix>
inline std::istringstream &operator >>(std::istringstream &lhs, g_matrix::MatrixSlice<ConceptMatrix> &rhs)
{ return g_matrix::matrix_extract(lhs, rhs); }