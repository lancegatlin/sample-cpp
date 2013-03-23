#ifndef __G_MATRIX_TIER2_CLASS_MATRIXITERATOR_H
#define __G_MATRIX_TIER2_CLASS_MATRIXITERATOR_H

/*
    File: g_matrix_tier2_class_MatrixIterator.h
    Author: lance.gatlin@yahoo.com
    Date: 19 Sep 2008
    Version: 1

    Overview: 
	1) Declares and implements the MatrixIterator class
*/

namespace g_matrix {

// base class starts building concepts forward_iterator and Matrix/ConstMatrix
template<class ConceptMatrix>
class MatrixIteratorBase {
    protected:
    ConceptMatrix *_matrix;
    size_t _row, _column;
    
    public:
    typedef MatrixIteratorBase<ConceptMatrix> this_t;
    typedef ConceptMatrix matrix_t;
    
    MatrixIteratorBase(matrix_t *__matrix = NULL, size_t __row = 0, size_t __column = 0)
    : _matrix(__matrix), _row(__row), _column(__column)
    { };

    MatrixIteratorBase(matrix_t &__matrix, size_t __row = 0, size_t __column = 0)
    : _matrix(&__matrix), _row(__row), _column(__column)
    { };
    
    // accessors
    size_t row() const { return _row; };
    size_t column() const { return _column; };
    matrix_t *matrix() const { return _matrix; };
    
    bool atEnd() const { return isEnd() ? true : _row >= _matrix->rows(); };
    bool isEnd() const { return _matrix == NULL; };
    bool membersEqual(const this_t &rhs) const 
    { return _matrix == rhs._matrix && _row == rhs._row && _column == rhs._column; };
    
    // concept forward_iterator
    this_t &operator ++()
    {
        _column++;
        if(_column >= _matrix->columns())
        {
            _row++;
            _column = 0;
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
        if(isEnd())
            return rhs.atEnd();
        if(rhs.isEnd())
            return atEnd();
        return membersEqual(rhs);
    }

    // concept Matrix
    size_t rows() const { return _matrix->rows() - _row; };
    size_t columns() const { return _matrix->columns() - _column; };
};

// concepts: forward_iterator, Matrix
template<class ConceptMatrix>
class MatrixIterator : public MatrixIteratorBase<ConceptMatrix> {
    public:
    typedef MatrixIterator<ConceptMatrix> this_t;
    typedef MatrixIteratorBase<ConceptMatrix> parent_t;
    typedef ConceptMatrix matrix_t;
    
    MatrixIterator(matrix_t *__matrix = NULL, size_t __row = 0, size_t __column = 0)
    : parent_t(__matrix, __row, __column) 
    { }; 

    MatrixIterator(matrix_t &__matrix, size_t __row = 0, size_t __column = 0)
    : parent_t(__matrix, __row, __column) 
    { }; 

    // concept forward_iterator
    float_type &operator *() const
    { return (*parent_t::_matrix)(parent_t::_row, parent_t::_column); }
    
    // concept Matrix
    float_type &operator()(size_t row_index, size_t column_index) const
    { return (*parent_t::_matrix)(parent_t::_row + row_index, parent_t::_column + column_index); };
    
    operator MatrixIterator<const ConceptMatrix> () const
    { return *(MatrixIterator<const ConceptMatrix>)this; };
};

// concepts: forward_iterator, ConstMatrix
template<class ConceptMatrix>
class MatrixIterator<const ConceptMatrix> : public MatrixIteratorBase<const ConceptMatrix> {
    public:
    typedef MatrixIterator<const ConceptMatrix> this_t;
    typedef MatrixIteratorBase<const ConceptMatrix> parent_t;
    typedef const ConceptMatrix matrix_t;
    
    MatrixIterator(matrix_t *__matrix = NULL, size_t __row = 0, size_t __column = 0)
    : parent_t(__matrix, __row, __column) 
    { }; 

    MatrixIterator(matrix_t &__matrix, size_t __row = 0, size_t __column = 0)
    : parent_t(__matrix, __row, __column) 
    { }; 

    // concept forward_iterator
    float_ptype operator *() const
    { return (*parent_t::_matrix)(parent_t::_row, parent_t::_column); }

    // concept ConstMatrix
    float_ptype operator()(size_t row_index, size_t column_index) const
    { return (*parent_t::_matrix)(parent_t::_row + row_index, parent_t::_column + column_index); };
};

} // namsepace g_matrix

#endif
