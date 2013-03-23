#ifndef __G_MATRIX_H
#define __G_MATRIX_H

#include <algorithm>
#include <iostream>
#include <iterator>
#include <g_global/g_global.h>
#include <g_global/g_column_vector.h>
#include <g_global/g_matrix_exception.h>
#include <g_global/g_matrix_algorithm.h>
#include <g_global/g_matrix_static_storage.h>
#include <g_global/g_matrix_dynamic_storage.h>
#include <g_global/g_matrix_submatrix_storage.h>
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
    typedef AnyMatrix<MatrixSubMatrixStorage<this_t> > submatrix_t;
    typedef typename storage_t::construct_parameters_t construct_parameters_t;
    
    class row_t {
        this_t *matrix;
        size_t row_zero_based_index;
        
        public:
        row_t(this_t *_matrix, size_t _row_zero_based_index)
        : matrix(_matrix), row_zero_based_index(_row_zero_based_index)
        { };
        
        float_ptype operator[](size_t column_zero_based_index) const
        { return matrix->at(row_zero_based_index, column_zero_based_index); };

        float_type &operator[](size_t column_zero_based_index)
        { return matrix->at(row_zero_based_index, column_zero_based_index); };
        
        size_t getRow() const { return row_zero_based_index; };        
        this_t *getMatrix() const { return matrix; };        
    };
    class const_row_t {
        const this_t *matrix;
        size_t row_zero_based_index;
        
        public:
        const_row_t(const this_t *_matrix, size_t _row_zero_based_index)
        : matrix(_matrix), row_zero_based_index(_row_zero_based_index)
        { };
        const_row_t(const row_t &copy_me)
        : matrix(copy_me.getMatrix()), row_zero_based_index(copy_me.getRow())
        { };
        
        float_ptype operator[](size_t column_zero_based_index) const
        { return matrix->at(row_zero_based_index, column_zero_based_index); };

        size_t getRow() const { return row_zero_based_index; };        
        const this_t *getMatrix() const { return matrix; };        
    };
    
    AnyMatrix() { zero(); };
    
    AnyMatrix(construct_parameters_t p)
    : parent_t(p) 
    { zero(); };
    
    template<class AnyStorage>
    AnyMatrix(const AnyMatrix<AnyStorage> &copy_me)
    : parent_t(copy_me)
    { };

    // iterator
    class const_iterator {
        const matrix_t *matrix;
        size_t row, column;
        
        public:
        typedef const_iterator this_t;
        
        const_iterator(const matrix_t *_matrix = NULL, size_t _row = 0, size_t _column = 0)
        : matrix(_matrix), row(_row), column(_column)
        { };
        
        float_ptype operator *() const 
        { 
            return matrix->at(row,column); 
        }
        
        this_t &operator ++()
        {
            column++;
            if(column >= matrix->columns())
            {
                row++;
                column = 0;
            }
            return *this;
        }
        
        this_t operator ++(int)
        {
            this_t retv(*this);
            operator ++();
            return retv;
        }
        
        bool operator != (const this_t &rhs) const
        { return !operator ==(rhs); };
        
        bool operator == (const this_t &rhs) const
        {
            if(matrix == NULL)
                return rhs.row >= rhs.matrix->rows();
            if(rhs.matrix == NULL)
                return row >= matrix->rows();
            return matrix == rhs.matrix && row == rhs.row && column == rhs.column;
        }
    };
    class iterator {
        matrix_t *matrix;
        size_t row, column;
        
        public:
        typedef iterator this_t;
        
        iterator(matrix_t *_matrix = NULL, size_t _row = 0, size_t _column = 0)
        : matrix(_matrix), row(_row), column(_column)
        { };
        
        float_type &operator *() const 
        { return matrix->at(row,column); }
        
        this_t &operator ++()
        {
            column++;
            if(column >= matrix->columns())
            {
                row++;
                column = 0;
            }
            return *this;
        }
        
        this_t operator ++(int)
        {
            this_t retv(*this);
            operator ++();
            return retv;
        }
        
        bool operator != (const this_t &rhs) const
        { return !operator ==(rhs); };
        
        bool operator == (const this_t &rhs) const
        {
            if(matrix == NULL)
                return rhs.row >= rhs.matrix->rows();
            if(rhs.matrix == NULL)
                return row >= matrix->rows();
            return matrix == rhs.matrix && row == rhs.row && column == rhs.column;
        }

        this_t &operator =(float_ptype f)
        { 
            parent_t::matrix->at(parent_t::row,parent_t::column) = f;
            return *this;
        }
    };
        
    const_iterator begin() const { return const_iterator(this); };
    const_iterator end() const { return const_iterator(); };
    iterator begin() { return iterator(this); };
    iterator end() { return iterator(); };
    
    // No bounds checking
    const_row_t operator [](size_t row_zero_based_index) const
    { return at(row_zero_based_index); };
    
    row_t operator [](size_t row_zero_based_index)
    { return at(row_zero_based_index); };

    const_row_t at(size_t row_zero_based_index) const
    { return const_row_t(this, row_zero_based_index); };
    
    row_t at(size_t row_zero_based_index)
    { return row_t(this, row_zero_based_index); };
    
    float_ptype at(size_t row_zero_based_index, size_t column_zero_based_index) const
    { return parent_t::at(row_zero_based_index, column_zero_based_index); };
   
    float_type &at(size_t row_zero_based_index, size_t column_zero_based_index)
    { return parent_t::at(row_zero_based_index, column_zero_based_index); };

    // Mutators
    void zero() { fill(0.0); };
    void fill(float_ptype value) { matrix_fill(*this, value); };
    
    void setIdentity() { matrix_set_identity(*this); }
    
    // Assignment
    template<class AnyStorage>
    this_t &operator =(const AnyMatrix<AnyStorage> &copy_me)
    { parent_t::operator =(copy_me); return *this; };
    
    // Equality
    template<class AnyStorage>
    bool operator ==(const AnyMatrix<AnyStorage> &rhs) const
    { return equal(rhs); };
    
    template<class AnyStorage>
    bool equal(const AnyMatrix<AnyStorage> &rhs) const
    { return matrix_equal(*this, rhs); }
    
    // Get a submatrix that excludes a row and column (for calculating determinant)
    submatrix_t getSubMatrix(size_t xi, size_t xj) const
    { submatrix_t(submatrix_t::construct(*this, xi, xj)); };
    
    // Determinant
    float_type getDeterminant() const
    { return matrix_determinant(*this); };
};


// Matrix + Matrix
template<class S1, class S2>
AnyMatrix<S1> operator +(const AnyMatrix<S1> &lhs,const AnyMatrix<S2> &rhs)
{
    AnyMatrix<S1> retv;
    
    matrix_add(lhs,rhs,retv);
        
    return retv;
}

// Matrix += Matrix
template<class S1, class S2>
AnyMatrix<S1> &operator +=(AnyMatrix<S1> &lhs,const AnyMatrix<S2> &rhs)
{
    lhs = lhs + rhs;
    return lhs;
}

// Matrix::row += Matrix::const_row_t
template<class S1, class S2>
typename AnyMatrix<S1>::row_t operator +=(typename AnyMatrix<S1>::row_t lhs,typename AnyMatrix<S2>::const_row_t rhs)
{
    matrix_add_rows(*lhs.getMatrix(), lhs.getRow(), *rhs.getMatrix(), rhs.getRow(), *lhs.getMatrix(), lhs.getRow());
        
    return lhs;
}

// Matrix * float_type
template<class S>
AnyMatrix<S> operator *(const AnyMatrix<S> &lhs, float_ptype rhs)
{
    AnyMatrix<S> retv;
    
    matrix_multiply(lhs,rhs,retv);
    
    return retv;
}

// Matrix / float_type
template<class S>
AnyMatrix<S> operator /(const AnyMatrix<S> &lhs, float_ptype rhs)
{
    AnyMatrix<S> retv;
    
    matrix_multiply(lhs,(1/rhs),retv);
    
    return retv;
}

// Matrix *= float_type
template<class S>
AnyMatrix<S> &operator *=(AnyMatrix<S> &lhs,float_ptype rhs)
{
    lhs = lhs * rhs;
    return lhs;
}

// Matrix /= float_type
template<class S>
AnyMatrix<S> &operator /=(AnyMatrix<S> &lhs,float_ptype rhs)
{
    lhs = lhs / rhs;
    return lhs;
}

// Matrix::row *= float_type
template<class S1, class S2>
typename AnyMatrix<S1>::row_t operator *=(typename AnyMatrix<S1>::row_t lhs, float_ptype rhs)
{
    matrix_multiply_row(*lhs.getMatrix(), lhs.getRow(), rhs);
        
    return lhs;
}

// Matrix::row /= float_type
template<class S1, class S2>
typename AnyMatrix<S1>::row_t operator /=(typename AnyMatrix<S1>::row_t lhs, float_ptype rhs)
{
    matrix_multiply_row(*lhs.getMatrix(), lhs.getRow(), (1/rhs));
        
    return lhs;
}

// Matrix * Matrix
template<class S1, class S2>
AnyMatrix<S1> operator *(const AnyMatrix<S1> &lhs,const AnyMatrix<S2> &rhs)
{
    AnyMatrix<S1> retv;
    
    matrix_multiply(lhs,rhs,retv);
    
    return retv;
}

// Matrix *= Matrix
template<class S1, class S2>
AnyMatrix<S1> &operator *=(AnyMatrix<S1> &lhs,const AnyMatrix<S2> &rhs)
{
    lhs = lhs * rhs;
    return lhs;
}

// Identity Matrix
template<class S>
class AnyIdentityMatrix : public AnyMatrix<S> {
    public:
    typedef AnyMatrix<S> parent_t;
    typedef AnyIdentityMatrix<S> this_t;
    
    AnyIdentityMatrix() { parent_t::setIdentity(); };
};

// output text dump of matrix content
template<class S>
std::ostream &operator <<(std::ostream &out, const AnyMatrix<S> &m)
{
    matrix_dump(out, m);
    return out;
}

class DynamicMatrix : public AnyMatrix<MatrixDynamicStorage> {
    public:
    typedef AnyMatrix<MatrixDynamicStorage> parent_t;
    typedef DynamicMatrix this_t;
    typedef parent_t::construct_parameters_t construct_parameters_t;
    
    DynamicMatrix() { };
    
    DynamicMatrix(construct_parameters_t p)
    : parent_t(p) 
    { };
    
    DynamicMatrix(size_t rows, size_t columns)
    : parent_t(construct_parameters_t(rows, columns)) 
    { };
    
    template<class AnyStorage>
    DynamicMatrix(const AnyMatrix<AnyStorage> &copy_me)
    : parent_t(copy_me)
    { };

    template<class Matrix>
    DynamicMatrix(  const Matrix &slice_me
                ,size_t row_begin
                ,size_t row_end
                ,size_t column_begin
                ,size_t column_end
            )
    : parent_t(construct_parameters_t(row_end - row_begin, column_end - column_begin))
    {
        matrix_slice(slice_me, row_begin, row_end, column_begin, column_end, *this);
    };
};

template<unsigned long ROWS, unsigned long COLUMNS>
class StaticMatrix : public AnyMatrix<MatrixStaticStorage<ROWS,COLUMNS> > {
    public:
    typedef AnyMatrix<MatrixStaticStorage<ROWS,COLUMNS> > parent_t;
    typedef StaticMatrix<ROWS,COLUMNS> this_t;
    typedef typename parent_t::construct_parameters_t construct_parameters_t;
    
    StaticMatrix() { };
    
    StaticMatrix(construct_parameters_t p)
    : parent_t(p) 
    { };
    
    template<class AnyStorage>
    StaticMatrix(const AnyMatrix<AnyStorage> &copy_me)
    : parent_t(copy_me)
    { };
};

class IdentityMatrix : public AnyMatrix<MatrixIdentityStorage> {
    public:
    typedef AnyMatrix<MatrixIdentityStorage> parent_t;
    typedef IdentiyMatrix this_t;
    
    IdentityMatrix() { };
};


} // namespace g_global

#endif
