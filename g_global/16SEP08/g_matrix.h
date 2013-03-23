#ifndef __G_MATRIX_H
#define __G_MATRIX_H

#include <algorithm>
#include <iostream>
#include <iterator>
#include <g_global/g_global.h>
#include <g_global/g_column_vector.h>
#include <g_global/g_matrix_algorithm.h>
#include <g_global/g_matrix_exception.h>
#include <g_global/g_matrix_row.h>
#include <g_global/g_matrix_column.h>
#include <g_global/g_matrix_iterator.h>
#include <g_global/g_matrix_slice_iterator.h>
#include <g_global/g_matrix_static_storage.h>
#include <g_global/g_matrix_dynamic_storage.h>
#include <g_global/g_matrix_adaptor_storage.h>
#include <g_global/g_matrix_identity_storage.h>

/*
    File: g_matrix.h
    Author: lance.gatlin@yahoo.com
    Date: 28 Aug 2008
    Version: 1

    Overview: 
        1) Declares and implements template class AnyMatrix. AnyMatrix 
        encapsulates a matrix of float_types. Provides:
            a) Default and copy constructors
            b) Access to internal matrix array by way of operator []
            c) Functions for filling or setting the values of the 
            matrix
            d) Assignment (assign, operator =)
            e) Equality (equal, operator ==)
            f) Function getDeterminant
        2) Declares math operators for Matrix<->Matrix[+,*], 
        Matrix<->float_type[*], AnyColumnVector<->Matrix[*]
        3) Declares AnyIdentityMatrix that is derived from AnyMatrix. On 
        construction automatically sets matrix to identity
        
*/

namespace g_global {

template<class MatrixStorage>
class AnyMatrix : public MatrixStorage {
    public:
    typedef MatrixStorage storage_t;
    typedef storage_t parent_t;
    typedef AnyMatrix<storage_t> this_t;
    typedef this_t matrix_t;

    typedef MatrixIterator<this_t> iterator;
    typedef MatrixConstIterator<this_t> const_iterator;
    typedef MatrixSliceIterator<this_t> slice_iterator;
    typedef MatrixConstSliceIterator<this_t> const_slice_iterator;
    
    typedef MatrixRow<this_t> row_t;
    typedef MatrixConstRow<this_t> const_row_t;
    typedef MatrixColumn<this_t> column_t;
    typedef MatrixConstColumn<this_t> const_column_t;
       
    AnyMatrix() { };

    // Iterator
    const_iterator begin() const { return const_iterator(this); };
    const_iterator end() const { return const_iterator(); };
    iterator begin() { return iterator(this); };
    iterator end() { return iterator(); };
    
    // No bounds checking
    const_row_t operator[](size_t row_zero_based_index) const
    { return const_row_t(this, row_zero_based_index); };
    
    row_t operator[](size_t row_zero_based_index)
    { return row_t(this, row_zero_based_index); };
    
    float_ptype operator()(size_t row_zero_based_index, size_t column_zero_based_index) const
    { return parent_t::operator()(row_zero_based_index, column_zero_based_index); };
   
    float_type &operator()(size_t row_zero_based_index, size_t column_zero_based_index)
    { return parent_t::operator()(row_zero_based_index, column_zero_based_index); };

    // Row/Column accessors
    row_t row(size_t row_zero_based_index)
    { return row_t(this, row_zero_based_index); };

    const_row_t row(size_t row_zero_based_index) const
    { return row_t(this, row_zero_based_index); };
    
    column_t column(size_t column_zero_based_index)
    { return column_t(this, column_zero_based_index); };

    const_column_t column(size_t column_zero_based_index) const
    { return column_t(this, column_zero_based_index); };
    
    // Mutators
    void zero() { fill(0.0); };
    void fill(float_ptype value) { matrix_fill(*this, value); };
    
    void setIdentity() { matrix_set_identity(*this); }
    
    // Assignment
    template<class ConceptMatrix>
    this_t &operator =(const ConceptMatrix &assign_me)
    { matrix_copy(assign_me, *this); return *this; };
    
    // Equality
    template<class ConceptMatrix>
    bool operator ==(const ConceptMatrix &rhs) const
    { return matrix_equal(*this, rhs); }
        
    iterator submatrix(size_t row_begin, size_t column_begin)
    { return iterator(this, row_begin, column_begin); };
    
    const_iterator submatrix(size_t row_begin, size_t column_begin) const
    { return const_iterator(this, row_begin, column_begin); };

    slice_iterator submatrix(size_t row_begin, size_t row_end, size_t column_begin, size_t column_end)
    { return slice_iterator (this, row_begin, row_end, column_begin, column_end); };
    
    const_slice_iterator submatrix(size_t row_begin, size_t row_end, size_t column_begin, size_t column_end) const
    { return const_slice_iterator(this, row_begin, row_end, column_begin, column_end); };

    // Determinant
    float_type getDeterminant() const
    { return matrix_determinant(*this); };

    template<class ConceptMatrix>
    void swap(ConceptMatrix &m) 
    { matrix_swap(*this, m); };

    void swap(this_t &m)
    { matrix_swap(*this, m); };
};

class DynamicMatrix : public AnyMatrix<MatrixDynamicStorage> {
    public:
    typedef AnyMatrix<MatrixDynamicStorage> parent_t;
    typedef DynamicMatrix this_t;
    
    DynamicMatrix() { };
    
    DynamicMatrix(size_t rows, size_t columns)
    {
        reserve(rows, columns); 
    };
    
    template<class ConceptMatrix>
    DynamicMatrix(const ConceptMatrix &copy_me)
    {
        reserve(copy_me.rows(), copy_me.columns());
        parent_t::operator=(copy_me);
    };

    template<class Matrix>
    DynamicMatrix(  const Matrix &slice_me
                ,size_t row_begin
                ,size_t row_end
                ,size_t column_begin
                ,size_t column_end
            )
    {
        reserve(row_end - row_begin, column_end - column_begin);
        matrix_slice(slice_me, row_begin, row_end, column_begin, column_end, *this);
    };
};

template<unsigned long ROWS, unsigned long COLUMNS>
class StaticMatrix : public AnyMatrix<MatrixStaticStorage<ROWS,COLUMNS> > {
    public:
    typedef AnyMatrix<MatrixStaticStorage<ROWS,COLUMNS> > parent_t;
    typedef StaticMatrix<ROWS,COLUMNS> this_t;
    
    StaticMatrix() { };
    
    template<class ConceptMatrix>
    StaticMatrix(const ConceptMatrix &copy_me)
    {
        parent_t::operator=(copy_me);
    };
};

class IdentityMatrix : public AnyMatrix<MatrixIdentityStorage> {
    public:
    typedef AnyMatrix<MatrixIdentityStorage> parent_t;
    typedef IdentityMatrix this_t;
    
    IdentityMatrix() { };
};

template<class ConceptMatrix>
class MatrixAdaptor : public AnyMatrix<MatrixAdaptorStorage<ConceptMatrix> > {
    public:
    typedef MatrixAdaptor<ConceptMatrix> this_t;
    typedef AnyMatrix<MatrixAdaptorStorage<ConceptMatrix> > parent_t;
    
    MatrixAdaptor() { };
    
    MatrixAdaptor(ConceptMatrix m)
    {
        matrix(m);
    }
};

template<class ConceptMatrix>
class SubMatrix : public MatrixAdaptor<MatrixSliceIterator<ConceptMatrix> > {
    public:
    typedef SubMatrix<ConceptMatrix> this_t;
    typedef MatrixAdaptor<MatrixSliceIterator<ConceptMatrix> > parent_t;
    
    SubMatrix(ConceptMatrix &m, size_t row_begin, size_t column_begin)
    : parent_t(MatrixSliceIterator<ConceptMatrix>(m, row_begin, m.rows(), column_begin, m.columns()))
    { }

    SubMatrix(ConceptMatrix &m, size_t row_begin, size_t row_end, size_t column_begin, size_t column_end)
    : parent_t(MatrixSliceIterator<ConceptMatrix>(m, row_begin, row_end, column_begin, column_end))
    { }
};

template<class ConceptMatrix>
class ConstSubMatrix : public MatrixAdaptor<MatrixConstSliceIterator<ConceptMatrix> > {
    public:
    typedef SubMatrix<ConceptMatrix> this_t;
    typedef MatrixAdaptor<MatrixConstSliceIterator<ConceptMatrix> > parent_t;
    
    ConstSubMatrix(const ConceptMatrix &m, size_t row_begin, size_t column_begin)
    : parent_t(MatrixConstSliceIterator<ConceptMatrix>(m, row_begin, m.rows(), column_begin, m.columns()))
    { }

    ConstSubMatrix(const ConceptMatrix &m, size_t row_begin, size_t row_end, size_t column_begin, size_t column_end)
    : parent_t(MatrixConstSliceIterator<ConceptMatrix>(m, row_begin, row_end, column_begin, column_end))
    { }
};

#include "g_matrix_ops.h"

} // namespace g_global

#endif
