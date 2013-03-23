#ifndef __G_MATRIX_COLUMN_ITERATOR_H
#define __G_MATRIX_COLUMN_ITERATOR_H

#include <g_global/g_matrix_iterator.h>

namespace g_global {
    
// base class starts building concepts forward_iterator and Matrix/ConstMatrix
template<class ConceptMatrix>
class MatrixColumnIteratorBase : public MatrixIteratorBase<ConceptMatrix> {
    public:
    typedef MatrixColumnIteratorBase<ConceptMatrix> this_t;
    typedef MatrixIteratorBase<ConceptMatrix> parent_t;
    typedef ConceptMatrix matrix_t;
    
    MatrixColumnIterator(matrix_t *__matrix = NULL, size_t __column = 0)
    : parent_t(__matrix, 0, __column) 
    { }; 
    
    MatrixColumnIterator(matrix_t &__matrix, size_t __column)
    : parent_t(__matrix, 0, __column) 
    { }; 
    
    bool atEnd() const { return _row >= matrix->rows(); };

    // concept forward_iterator
    this_t &operator ++()
    {
        if(!atEnd())
            row++;
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
    size_t columns() { return 1; };
};

// concepts: forward_iterator, Matrix
template<class ConceptMatrix>
class MatrixColumnIterator : public MatrixColumnIteratorBase<ConceptMatrix> {
    public:
    typedef MatrixColumnIterator<ConceptMatrix> this_t;
    typedef MatrixColumnIteratorBase<ConceptMatrix> parent_t;
    typedef ConceptMatrix matrix_t;
    
    typedef MatrixRow<this_t> row_t;
    
    MatrixColumnIterator(matrix_t *__matrix = NULL, size_t __column = 0)
    : parent_t(__matrix, 0, __column) 
    { }; 
    
    MatrixColumnIterator(matrix_t &__matrix, size_t __column)
    : parent_t(__matrix, 0, __column) 
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
class MatrixConstColumnIterator : public MatrixColumnIteratorBase<const ConceptMatrix> {
    public:
    typedef MatrixConstColumnIterator<ConceptMatrix> this_t;
    typedef MatrixColumnIteratorBase<const ConceptMatrix> parent_t;
    typedef const ConceptMatrix matrix_t;

    typedef MatrixConstRow<this_t> const_column_t;

    MatrixColumnIterator(matrix_t *_matrix = NULL, size_t _column = 0)
    : parent_t(_matrix, _column, 0) 
    { }; 
    
    MatrixColumnIterator(matrix_t &_matrix, size_t _column)
    : parent_t(_matrix, _column, 0) 
    { }; 

    // concept forward_iterator
    float_ptype operator[](size_t column_index) const
    { return matrix->at(row, column_index); }

    // concept ConstMatrix
    const_column_t operator[](size_t row_index) const
    { return const_column_t(this, row_index); };

    float_ptype at(size_t row_index, size_t column_index) const;
    { return _matrix->at(_column + row_index, _column + column_index); };
};

} // namespace g_global

#endif
