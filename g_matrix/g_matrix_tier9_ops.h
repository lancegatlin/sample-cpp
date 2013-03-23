/*
    File: g_matrix_tier9_ops.h
    Author: lance.gatlin@yahoo.com
    Date: 19 Sep 2008
    Version: 1

    Overview: 
	1) Declares and implements |=, +=, -=, *=, /=, ostream << for AnyMatrix
*/

/********************************* AnyMatrix Ops *********************************/

// AnyMatrix op-equal functions are pass "by reference" since an AnyMatrix is not an alias(pointer)

// AnyMatrix |= ConceptMatrix
template<class ConceptMatrixStorage1, class ConceptMatrix2>
inline g_matrix::AnyMatrix<ConceptMatrixStorage1> &operator |=(g_matrix::AnyMatrix<ConceptMatrixStorage1> &lhs, const ConceptMatrix2 &rhs)
{ g_matrix::matrix_column_merge(rhs, lhs); return lhs; }

// AnyMatrix += ConceptMatrix
template<class ConceptMatrixStorage1, class ConceptMatrix2>
inline g_matrix::AnyMatrix<ConceptMatrixStorage1> &operator +=(g_matrix::AnyMatrix<ConceptMatrixStorage1> &lhs, const ConceptMatrix2 &rhs)
{ g_matrix::matrix_add(lhs, rhs, lhs); return lhs; }

// AnyMatrix -= ConceptMatrix
template<class ConceptMatrixStorage1, class ConceptMatrix2>
inline g_matrix::AnyMatrix<ConceptMatrixStorage1> &operator -=(g_matrix::AnyMatrix<ConceptMatrixStorage1> &lhs, const ConceptMatrix2 &rhs)
{ g_matrix::matrix_subtract(lhs, rhs, lhs); return lhs; }

// AnyMatrix *= float_type
template<class ConceptMatrixStorage>
inline g_matrix::AnyMatrix<ConceptMatrixStorage> &operator *=(const g_matrix::AnyMatrix<ConceptMatrixStorage> &lhs, g_matrix::float_ptype rhs)
{ g_matrix::matrix_multiply(lhs, rhs, lhs); return lhs; }

// AnyMatrix /= float_type
template<class ConceptMatrix>
inline g_matrix::AnyMatrix<ConceptMatrix> &operator /=(g_matrix::AnyMatrix<ConceptMatrix> &lhs, g_matrix::float_ptype rhs)
{ g_matrix::matrix_multiply(lhs,(1/rhs), lhs); return lhs; }

// output text dump of matrix content
template<class ConceptMatrix>
inline std::ostream &operator <<(std::ostream &lhs, const g_matrix::AnyMatrix<ConceptMatrix> &rhs)
{ return g_matrix::matrix_dump(lhs, rhs); }

// insert streamable version of matrix content
template<class ConceptMatrix>
inline std::ostringstream &operator <<(std::ostringstream &lhs, const g_matrix::AnyMatrix<ConceptMatrix> &rhs)
{ return g_matrix::matrix_insert(lhs, rhs); }

// extract streamable version of matrix content
template<class ConceptMatrix>
inline std::istringstream &operator >>(std::istringstream &lhs, g_matrix::AnyMatrix<ConceptMatrix> &rhs)
{ return g_matrix::matrix_extract(lhs, rhs); }
