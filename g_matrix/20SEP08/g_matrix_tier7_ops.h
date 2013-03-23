#ifndef __G_MATRIX_TIER7_OPS_H
#define __G_MATRIX_TIER7_OPS_H

/*
    File: g_matrix_tier7_ops.h
    Author: lance.gatlin@yahoo.com
    Date: 19 Sep 2008
    Version: 1

    Overview: 
	1) Declares and implements |, +,  -, *, / for MatrixRow, MatrixColumn, AnyMatrix and matrix arrays
*/

/*
Removed due to ambiguity errors with:
AnyMatrix<S> + Row

Ambiguity between operator +(AnyMatrix, ConceptMatrix) and operator +(Row, ConceptMatrix)

Downside:
If ConceptMatrix is not a Column, Row or AnyMatrix then:
ConceptMatrix + Row has to be written Row + ConceptMatrix


// ConceptMatrix + Row
template<class ConceptMatrix1, class ConceptMatrix2>
DynamicMatrix operator +(const ConceptMatrix1 &lhs, g_matrix::MatrixRow<ConceptMatrix2> rhs)
{
    g_matrix::DynamicMatrix retv(   std::max(lhs.rows(),rhs.rows())
                                    ,std::max(lhs.columns(),rhs.columns())
                                    );
    
    matrix_add(lhs,rhs,retv);
        
    return retv;
}
*/



/********************************* Row Ops ************************************/
// Row op-equal functions are pass "by value" since a Row is really an alias(pointer) for a ConceptMatrix

// Row | ConceptMatrix
template<class ConceptMatrix1, class ConceptMatrix2>
inline g_matrix::DynamicMatrix operator |(g_matrix::MatrixRow<ConceptMatrix1> lhs, const ConceptMatrix2 &rhs)
{ return g_matrix::matrix_column_merge(lhs, rhs); }

// Row + ConceptMatrix
template<class ConceptMatrix1, class ConceptMatrix2>
inline g_matrix::DynamicMatrix operator +(g_matrix::MatrixRow<ConceptMatrix1> lhs, const ConceptMatrix2 &rhs)
{ return g_matrix::matrix_add(lhs, rhs); }

// Row - ConceptMatrix
template<class ConceptMatrix1, class ConceptMatrix2>
inline g_matrix::DynamicMatrix operator -(g_matrix::MatrixRow<ConceptMatrix1> lhs, const ConceptMatrix2 &rhs)
{ return g_matrix::matrix_subtract(lhs, rhs); }

// Row * ConceptMatrix
template<class ConceptMatrix1, class ConceptMatrix2>
inline g_matrix::DynamicMatrix operator *(g_matrix::MatrixRow<ConceptMatrix1> lhs, const ConceptMatrix2 &rhs)
{ return g_matrix::matrix_multiply(lhs, rhs); }

// Row * float_type
template<class ConceptMatrix>
inline g_matrix::DynamicMatrix operator *(g_matrix::MatrixRow<ConceptMatrix> lhs, g_matrix::float_ptype rhs)
{ return g_matrix::matrix_multiply(lhs, rhs); }

// Row / float_type
template<class ConceptMatrix>
inline g_matrix::DynamicMatrix operator /(g_matrix::MatrixRow<ConceptMatrix> lhs, g_matrix::float_ptype rhs)
{ return g_matrix::matrix_divide(lhs,rhs); };

/********************************* Column Ops ************************************/
// Column op-equal functions are pass "by value" since a Column is really an alias(pointer) for a ConceptMatrix

// Column | ConceptMatrix
template<class ConceptMatrix1, class ConceptMatrix2>
inline g_matrix::DynamicMatrix operator |(g_matrix::MatrixColumn<ConceptMatrix1> lhs, const ConceptMatrix2 &rhs)
{ return g_matrix::matrix_column_merge(lhs, rhs); }

// Column + ConceptMatrix
template<class ConceptMatrix1, class ConceptMatrix2>
inline g_matrix::DynamicMatrix operator +(g_matrix::MatrixColumn<ConceptMatrix1> lhs, const ConceptMatrix2 &rhs)
{ return g_matrix::matrix_add(lhs, rhs); }

// Column - ConceptMatrix
template<class ConceptMatrix1, class ConceptMatrix2>
inline g_matrix::DynamicMatrix operator -(g_matrix::MatrixColumn<ConceptMatrix1> lhs, const ConceptMatrix2 &rhs)
{ return g_matrix::matrix_subtract(lhs, rhs); }

// Column * ConceptMatrix
template<class ConceptMatrix1, class ConceptMatrix2>
inline g_matrix::DynamicMatrix operator *(g_matrix::MatrixColumn<ConceptMatrix1> lhs, const ConceptMatrix2 &rhs)
{ return g_matrix::matrix_multiply(lhs, rhs); }

// Column * float_type
template<class ConceptMatrix>
inline g_matrix::DynamicMatrix operator *(g_matrix::MatrixColumn<ConceptMatrix> lhs, g_matrix::float_ptype rhs)
{ return g_matrix::matrix_multiply(lhs, rhs); }

// Column / float_type
template<class ConceptMatrix>
inline g_matrix::DynamicMatrix operator /(g_matrix::MatrixColumn<ConceptMatrix> lhs, g_matrix::float_ptype rhs)
{ return g_matrix::matrix_divide(lhs,rhs); };

/********************************* AnyMatrix Ops *********************************/

// AnyMatrix op-equal functions are pass "by reference" since an AnyMatrix is not an alias(pointer)

// AnyMatrix | ConceptMatrix
template<class ConceptMatrixStorage1, class ConceptMatrix2>
inline g_matrix::DynamicMatrix operator |(const g_matrix::AnyMatrix<ConceptMatrixStorage1> &lhs, const ConceptMatrix2 &rhs)
{ return g_matrix::matrix_column_merge(lhs, rhs); }

// AnyMatrix + ConceptMatrix
template<class ConceptMatrixStorage1, class ConceptMatrix2>
inline g_matrix::DynamicMatrix operator +(const g_matrix::AnyMatrix<ConceptMatrixStorage1> &lhs, const ConceptMatrix2 &rhs)
{ return g_matrix::matrix_add(lhs, rhs); }

// AnyMatrix - ConceptMatrix
template<class ConceptMatrixStorage1, class ConceptMatrix2>
inline g_matrix::DynamicMatrix operator -(const g_matrix::AnyMatrix<ConceptMatrixStorage1> &lhs, const ConceptMatrix2 &rhs)
{ return g_matrix::matrix_subtract(lhs, rhs); }

// AnyMatrix * ConceptMatrix
template<class ConceptMatrixStorage1, class ConceptMatrix2>
inline g_matrix::DynamicMatrix operator *(const g_matrix::AnyMatrix<ConceptMatrixStorage1> &lhs, const ConceptMatrix2 &rhs)
{ return g_matrix::matrix_multiply(lhs, rhs); }

// AnyMatrix * float_type
template<class ConceptMatrixStorage>
inline g_matrix::DynamicMatrix operator *(const g_matrix::AnyMatrix<ConceptMatrixStorage> &lhs, g_matrix::float_ptype rhs)
{ return g_matrix::matrix_multiply(lhs, rhs); }

// AnyMatrix / float_type
template<class ConceptMatrixStorage>
inline g_matrix::DynamicMatrix operator /(const g_matrix::AnyMatrix<ConceptMatrixStorage> &lhs, g_matrix::float_ptype rhs)
{ return g_matrix::matrix_divide(lhs,rhs); };

/********************************* MatrixArray Ops *********************************/

// MatrixArray | ConceptMatrix
template<unsigned long ROWS, unsigned long COLUMNS, class ConceptMatrix2>
inline g_matrix::DynamicMatrix operator |(const g_matrix::float_type (&lhs)[ROWS][COLUMNS], const ConceptMatrix2 &rhs)
{ return g_matrix::matrix_column_merge(lhs, rhs); }

// MatrixArray + ConceptMatrix
template<unsigned long ROWS, unsigned long COLUMNS, class ConceptMatrix2>
inline g_matrix::DynamicMatrix operator +(g_matrix::float_type (&lhs)[ROWS][COLUMNS], const ConceptMatrix2 &rhs)
{ return g_matrix::matrix_add(lhs, rhs); }

// MatrixArray - ConceptMatrix
template<unsigned long ROWS, unsigned long COLUMNS, class ConceptMatrix2>
inline g_matrix::DynamicMatrix operator -(const g_matrix::float_type (&lhs)[ROWS][COLUMNS], const ConceptMatrix2 &rhs)
{ return g_matrix::matrix_subtract(lhs, rhs); }

// MatrixArray * ConceptMatrix
template<unsigned long ROWS, unsigned long COLUMNS, class ConceptMatrix2>
inline g_matrix::DynamicMatrix operator *(const g_matrix::float_type (&lhs)[ROWS][COLUMNS], const ConceptMatrix2 &rhs)
{ return g_matrix::matrix_multiply(lhs, rhs); }

/*

Compiler doesn't like these

    //    `g_matrix::DynamicMatrix operator*(const g_matrix::float_type (&)[ROWS][COLUMNS], const double&)' 
    // must have an argument of class or enumerated type 

// MatrixArray * float_type
template<unsigned long ROWS, unsigned long COLUMNS, class ConceptMatrix2>
inline g_matrix::DynamicMatrix operator *(const g_matrix::float_type (&lhs)[ROWS][COLUMNS], g_matrix::float_ptype rhs)
{ return g_matrix::matrix_multiply(lhs, rhs); }

// MatrixArray *= float_type
template<unsigned long ROWS, unsigned long COLUMNS, class ConceptMatrix2>
inline typename g_matrix::matrix_array<ROWS,COLUMNS>::reference operator *=(g_matrix::float_type (&lhs)[ROWS][COLUMNS], g_matrix::float_ptype rhs)
{ g_matrix::matrix_multiply(lhs, rhs, lhs); return lhs; }

// MatrixArray / float_type
template<unsigned long ROWS, unsigned long COLUMNS, class ConceptMatrix2>
inline g_matrix::DynamicMatrix operator /(const g_matrix::float_type (&lhs)[ROWS][COLUMNS], g_matrix::float_ptype rhs)
{ return g_matrix::matrix_divide(lhs,rhs); };

// MatrixArray /= float_type
template<unsigned long ROWS, unsigned long COLUMNS, class ConceptMatrix2>
inline typename g_matrix::matrix_array<ROWS,COLUMNS>::reference operator /=(g_matrix::float_type (&lhs)[ROWS][COLUMNS], g_matrix::float_ptype rhs)
{ g_matrix::matrix_divide(lhs,rhs); return lhs; }
*/

#endif
