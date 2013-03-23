#ifndef __G_MATRIX_CLASS_MATRIXSLICE_H
#define __G_MATRIX_CLASS_MATRIXSLICE_H

/*
    File: g_matrix_tier3_class_MatrixSlice.h
    Author: lance.gatlin@yahoo.com
    Date: 19 Sep 2008
    Version: 1

    Overview: 
	1) Declares and impelemnts MatrixSlice
*/

namespace g_matrix {
    
template<class ConceptMatrix>
class MatrixSliceBase {
	ConceptMatrix *_matrix;
    size_t _row_begin,_row_end,_column_begin,_column_end;    
    
    public:
    typedef MatrixSliceBase<ConceptMatrix> this_t;
    typedef MatrixIteratorBase<ConceptMatrix> parent_t;
    typedef ConceptMatrix matrix_t;

    MatrixSliceBase(matrix_t *__matrix = NULL
                    ,size_t __row_begin = 0
                    ,size_t __column_begin = 0
                    ,size_t __row_end = 0
                    ,size_t __column_end = 0)
	: _matrix(__matrix)
	, _row_begin(__row_begin)
    , _row_end(__row_end)
	, _column_begin(__column_begin)
    , _column_end(__column_end) 
    { }; 
	
    MatrixSliceBase(matrix_t &__matrix
                    ,size_t __row_begin
                    ,size_t __column_begin
                    ,size_t __row_end
                    ,size_t __column_end)
	: _matrix(__matrix)
	, _row_begin(__row_begin)
    , _row_end(__row_end)
	, _column_begin(__column_begin)
    , _column_end(__column_end) 
    { }; 

	// default copy constructor
	// default assignment to self
	// default destructor
	
	matrix_t *matrix() const { return _matrix; };
    size_t row_begin() const { return _row_begin; };
    size_t row_end() const { return _row_end; };
    size_t column_begin() const { return _column_begin; };
    size_t column_end() const { return _column_end; };
    
    // concept Matrix
    size_t rows() const { return _row_end - _row_begin; };
    size_t columns() const { return _column_end - _column_begin; };
	
	protected:
	void checkOutOfBounds(size_t row, size_t column)
	{
		if(row >= rows()|| columns >= columns())
			throw MatrixOutOfBounds();
	}
};

template<class ConceptMatrix>
class MatrixSlice : public MatrixSliceBase<ConceptMatrix> {
    public:
    typedef MatrixSlice<ConceptMatrix> this_t;
    typedef MatrixSliceBase<ConceptMatrix> parent_t;
    typedef ConceptMatrix matrix_t;

    MatrixSlice(matrix_t *__matrix = NULL
                    ,size_t __row_begin = 0
                    ,size_t __col_begin = 0
                    ,size_t __row_end = 0
                    ,size_t __col_end = 0)
    : parent_t(__matrix, __row_begin, __col_begin, __row_end, __col_end) 
    { }; 
    MatrixSlice(matrix_t &__matrix
                    ,size_t __row_begin
                    ,size_t __col_begin
                    ,size_t __row_end
                    ,size_t __col_end)
    : parent_t(__matrix, __row_begin, __col_begin, __row_end, __col_end) 
    { }; 

    // concept Matrix
    float_type &operator()(size_t row_index, size_t column_index) const
    {
		parent_t::checkOutOfBounds(row_index, column_index);
		
		return (*parent_t::_matrix)(parent_t::_row_begin + row_index, parent_t::_column_begin + column_index); 
	};
    
    template<class ConceptMatrix1>
    this_t &operator =(const ConceptMatrix1 &assign_me)
    { matrix_copy(assign_me, *this); return *this; }

    this_t &operator =(const this_t &assign_me)
    { parent_t::operator =((const parent_t &)assign_me); return *this; }
    
    template<class ConceptMatrix1>
    bool operator ==(const ConceptMatrix1 &rhs)
    { matrix_equal(*this, rhs); };
    
    template<class ConceptMatrix1>
    void swap(ConceptMatrix1 &m)
    { matrix_swap(*this, m); };

    // allow pass by for temporary variables
    void swap(this_t m)
    { matrix_swap(*this, m); };

    operator MatrixSlice<const ConceptMatrix>() const
    { return *(MatrixSlice<const ConceptMatrix>)this; };    
};

template<class ConceptMatrix>
class MatrixSlice<const ConceptMatrix> : public MatrixSliceBase<ConceptMatrix> {
    public:
    typedef MatrixSlice<const ConceptMatrix> this_t;
    typedef MatrixSliceBase<const ConceptMatrix> parent_t;
    typedef const ConceptMatrix matrix_t;
    
    MatrixSlice(matrix_t *__matrix = NULL
                    ,size_t __row_begin = 0
                    ,size_t __col_begin = 0
                    ,size_t __row_end = 0
                    ,size_t __col_end = 0)
    : parent_t(__matrix, __row_begin, __col_begin, __row_end, __col_end) 
    { }; 
    MatrixSlice(matrix_t &__matrix
                    ,size_t __row_begin
                    ,size_t __col_begin
                    ,size_t __row_end
                    ,size_t __col_end)
    : parent_t(__matrix, __row_begin, __col_begin, __row_end, __col_end) 
    { }; 

	// default copy constructor
	// default destructor
	
    // concept ConstMatrix
    float_ptype operator()(size_t row_index, size_t column_index) const
    { 
		parent_t::checkOutOfBounds(row_index, column_index);
	
		return (*parent_t::_matrix)(parent_t::_row_begin + row_index, parent_t::_column_begin + column_index); 
	};

	// concept: Matrix
    float_type &operator()(size_t row_index, size_t column_index) const
    { return (*parent_t::_matrix)(parent_t::_row + row_index, column_index); };
};

} // namespace g_matrix

#endif
