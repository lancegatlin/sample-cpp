#ifndef __G_MATRIX_SLICE_ITERATOR_H
#define __G_MATRIX_SLICE_ITERATOR_H

#include <g_global/g_matrix_iterator.h>

namespace g_global {
    
template<class ConceptMatrix>
class MatrixSliceIteratorBase : public MatrixIteratorBase<ConceptMatrix> {
    size_t _row_end, _column_end;
    
    public:
    typedef MatrixSliceIteratorBase<ConceptMatrix> this_t;
    typedef MatrixIteratorBase<ConceptMatrix> parent_t;
    typedef ConceptMatrix matrix_t;
    
    MatrixSliceIteratorBase(matrix_t *__matrix = NULL
                    ,size_t __row_begin = 0
                    ,size_t __row_end = 0
                    ,size_t __column_begin = 0
                    ,size_t __column_end = 0)
    : parent_t(__matrix, __row_begin, __column_begin)
    , _row_end(__row_end)
    , _column_end(__column_end) 
    { }; 
    MatrixSliceIteratorBase(matrix_t &__matrix
                    ,size_t __row_begin
                    ,size_t __row_end
                    ,size_t __column_begin
                    ,size_t __column_end)
    : parent_t(__matrix, __row_begin, __column_begin)
    , _row_end(__row_end)
    , _column_end(__column_end) 
    { }; 

    size_t row_end() { return row_end; };
    size_t column_end() { return column_end; };
    
    bool atEnd() const { return parent_t::_row >= row_end; };

    this_t &operator ++()
    {
        parent_t::_column++;
        if(parent_t::_column >= _column_end)
        {
            parent_t::_row++;
            parent_t::_column = 0;
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
        if(parent_t::isEnd())
            return rhs.atEnd();
        if(rhs.parent_t::isEnd())
            return atEnd();
        return membersEqual(rhs);
    }

    // concept Matrix
    size_t rows() const { return _row_end - parent_t::_row; };
    size_t columns() const { return _column_end - parent_t::_column; };
};

template<class ConceptMatrix>
class MatrixSliceIterator : public MatrixSliceIteratorBase<ConceptMatrix> {
    public:
    typedef MatrixSliceIterator<ConceptMatrix> this_t;
    typedef MatrixSliceIteratorBase<ConceptMatrix> parent_t;
    typedef ConceptMatrix matrix_t;

    typedef MatrixRow<this_t> row_t;
        
    MatrixSliceIterator(matrix_t *__matrix = NULL
                    ,size_t __row_begin = 0
                    ,size_t __row_end = 0
                    ,size_t __col_begin = 0
                    ,size_t __col_end = 0)
    : parent_t(__matrix, __row_begin, __row_end, __col_begin, __col_end) 
    { }; 
    MatrixSliceIterator(matrix_t &__matrix
                    ,size_t __row_begin
                    ,size_t __row_end
                    ,size_t __col_begin
                    ,size_t __col_end)
    : parent_t(__matrix, __row_begin, __row_end, __col_begin, __col_end) 
    { }; 

    // concept forward_iterator
    float_type &operator *() const
    { return (*parent_t::_matrix)(parent_t::_row, parent_t::_column); }
    
    // concept Matrix
    float_type &operator()(size_t row_index, size_t column_index) const
    { return (*parent_t::_matrix)(parent_t::_row + row_index, parent_t::_column + column_index); };
};

template<class ConceptMatrix>
class MatrixConstSliceIterator : public MatrixSliceIteratorBase<ConceptMatrix> {
    public:
    typedef MatrixConstSliceIterator<ConceptMatrix> this_t;
    typedef MatrixSliceIteratorBase<const ConceptMatrix> parent_t;
    typedef const ConceptMatrix matrix_t;
    
    MatrixConstSliceIterator(matrix_t *__matrix = NULL
                    ,size_t __row_begin = 0
                    ,size_t __row_end = 0
                    ,size_t __col_begin = 0
                    ,size_t __col_end = 0)
    : parent_t(__matrix, __row_begin, __row_end, __col_begin, __col_end) 
    { }; 
    MatrixConstSliceIterator(matrix_t &__matrix
                    ,size_t __row_begin
                    ,size_t __row_end
                    ,size_t __col_begin
                    ,size_t __col_end)
    : parent_t(__matrix, __row_begin, __row_end, __col_begin, __col_end) 
    { }; 

    // concept forward_iterator
    float_ptype operator *() const
    { return (*parent_t::_matrix)(parent_t::_row, parent_t::_column); }

    // concept ConstMatrix
    float_ptype operator()(size_t row_index, size_t column_index) const
    { return (*parent_t::_matrix)(parent_t::_row + row_index, parent_t::_column + column_index); };
};

} // namespace g_global

#endif
