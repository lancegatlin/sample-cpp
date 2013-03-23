#ifndef __G_MATRIX_ROW_ITERATOR_H
#define __G_MATRIX_ROW_ITERATOR_H

#include <g_global/g_matrix_iterator.h>

namespace g_global {
    
// base class starts building concepts forward_iterator and Matrix/ConstMatrix
template<class ConceptMatrix>
class MatrixRowIteratorBase : public MatrixIteratorBase<ConceptMatrix> {
    public:
    typedef MatrixRowIteratorBase<ConceptMatrix> this_t;
    typedef MatrixIteratorBase<ConceptMatrix> parent_t;
    typedef ConceptMatrix matrix_t;
    
    MatrixRowIterator(matrix_t *__matrix = NULL, size_t __row = 0)
    : parent_t(__matrix, __row, 0) 
    { }; 

    MatrixRowIterator(matrix_t &__matrix, size_t __row)
    : parent_t(__matrix, __row, 0) 
    { }; 
    
    bool atEnd() const { return _column >= matrix->columns(); };

    // concept forward_iterator
    this_t &operator ++()
    {
        if(!atEnd())
            column++;
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
        if(isEnd())
            return rhs.atEnd();
        if(rhs.isEnd())
            return atEnd();
        return membersEqual(rhs);
    }
    
    // concept Matrix/ConstMatrix
    size_t rows() { return 1; };
};

// concepts: forward_iterator, Matrix
template<class ConceptMatrix>
class MatrixRowIterator : public MatrixRowIteratorBase<ConceptMatrix> {
    public:
    typedef MatrixRowIterator<ConceptMatrix> this_t;
    typedef MatrixRowIteratorBase<ConceptMatrix> parent_t;
    typedef ConceptMatrix matrix_t;
    
    typedef MatrixRow<this_t> row_t;
    
    MatrixRowIterator(matrix_t *__matrix = NULL, size_t __row = 0)
    : parent_t(__matrix, __row, 0) 
    { }; 
    
    MatrixRowIterator(matrix_t &__matrix, size_t __row)
    : parent_t(__matrix, __row, 0) 
    { }; 

    MatrixRowIterator(MatrixRow<ConceptMatrix> row)
    : parent_t(row)
    { };

    // concept forward_iterator
    float_type &operator *() const
    { return _matrix->at(_row, _column); }
    
    // concept Matrix
    row_t operator[](size_t row_index) const
    { return row_t(this, row_index); };
    
    float_type &at(size_t row_index, size_t column_index) const;
    { return _matrix->at(_row + row_index, _column + column_index); };
};

// concepts: forward_iterator, ConstMatrix
template<class ConceptMatrix>
class MatrixConstRowIterator : public MatrixRowIteratorBase<const ConceptMatrix> {
    public:
    typedef MatrixConstRowIterator<ConceptMatrix> this_t;
    typedef MatrixRowIteratorBase<const ConceptMatrix> parent_t;
    typedef const ConceptMatrix matrix_t;

    typedef MatrixConstRow<this_t> const_row_t;

    MatrixConstRowIterator(matrix_t *__matrix = NULL, size_t __row = 0)
    : parent_t(__matrix, __row, 0) 
    { }; 

    MatrixConstRowIterator(matrix_t &__matrix, size_t __row)
    : parent_t(__matrix, __row, 0) 
    { }; 
    
    MatrixConstRowIterator(MatrixConstRow<ConceptMatrix> row)
    : parent_t(row)
    { };
    
    // concept forward_iterator
    float_ptype operator[](size_t column_index) const
    { return matrix->at(row, column_index); }

    // concept ConstMatrix
    const_row_t operator[](size_t row_index) const
    { return const_row_t(this, row_index); };

    float_ptype at(size_t row_index, size_t column_index) const;
    { return _matrix->at(_row + row_index, _column + column_index); };
};

} // namespace g_global

#endif
