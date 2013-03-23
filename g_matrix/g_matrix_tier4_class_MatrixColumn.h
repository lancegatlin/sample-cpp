/*
    File: g_matrix_tier4_class_MatrixColumn.h
    Author: lance.gatlin@yahoo.com
    Date: 19 Sep 2008
    Version: 1

    Overview: 
	1) Declares and implements MatrixColumn
*/

template<class ConceptMatrix>
class MatrixColumnBase {
    protected:
    ConceptMatrix *_matrix;
    size_t _column;
    
    public:
    typedef MatrixColumnBase<ConceptMatrix> this_t;
    typedef ConceptMatrix matrix_t;

    MatrixColumnBase(matrix_t *__matrix, size_t __column)
    : _matrix(__matrix), _column(__column)
    { };
    
    size_t column() const { return _column; };
    matrix_t *matrix() const { return _matrix; };
	
    // concept: Matrix
    size_t columns() const { return 1; };
    size_t rows() const { return _matrix->rows(); };
};

// concept: MatrixColumn
template<class ConceptMatrix>
class MatrixColumn : public MatrixColumnBase<ConceptMatrix> {
    public:
    typedef MatrixColumn<ConceptMatrix> this_t;
    typedef MatrixColumnBase<ConceptMatrix> parent_t;
    typedef ConceptMatrix matrix_t;
	typedef MatrixIterator<this_t> iterator;
	typedef MatrixIterator<const this_t> const_iterator;

    MatrixColumn(matrix_t *__matrix, size_t __column)
    : parent_t(__matrix,__column)
    { };
    
	// concept: MatrixColumn
    float_ptype operator[](size_t row) const
    { return (*parent_t::_matrix)(row, parent_t::_column); };

    float_type &operator[](size_t row)
    { return (*parent_t::_matrix)(row, parent_t::_column); };

    // concept: Matrix
    float_ptype operator()(size_t row_index, size_t column_index) const
    { return (*parent_t::_matrix)(row_index, parent_t::_column + column_index); };
    
    float_type &operator()(size_t row_index, size_t column_index)
    { return (*parent_t::_matrix)(row_index, parent_t::_column + column_index); };
    
	// concept: Matrix2
	iterator begin() { return iterator(this); };
	iterator end() { return iterator(); };
	const_iterator begin() const { return const_iterator(this); };
	const_iterator end() const { return const_iterator(); };

	template<class ConceptMatrix1>
    this_t &operator =(const ConceptMatrix1 &assign_me)
    { matrix_copy(assign_me, *this); return *this; }
    
    template<class ConceptMatrix1>
    bool operator ==(const ConceptMatrix1 &rhs) const
    { matrix_equal(*this, rhs); };

    template<class OtherConceptMatrix>
    void swap(OtherConceptMatrix &m)
    { matrix_swap(*this, m); };
	
	// Pass by value for temporaries
    void swap(this_t m)
    { matrix_swap(*this, m); };
    
	// Convert to const column if needed
    operator MatrixColumn<const ConceptMatrix>() const
    { return *(MatrixColumn<const ConceptMatrix> *)this; };

	// Convenience
	size_t max() const
	{
		size_t row, column;
		float_type max;

		matrix_max(*this, row, column, max);

		return row;
	}

	size_t min() const
	{
		size_t row, column;
		float_type min;

		matrix_min(*this, row, column, min);

		return row;
	}
};

// concept: MatrixConstColumn
template<class ConceptMatrix>
class MatrixColumn<const ConceptMatrix> : public MatrixColumnBase<const ConceptMatrix> {
    public:
    typedef MatrixColumn<ConceptMatrix> this_t;
    typedef const ConceptMatrix matrix_t;
    typedef MatrixColumnBase<matrix_t> parent_t;
	typedef MatrixIterator<const this_t> const_iterator;

    MatrixColumn(matrix_t *__matrix, size_t __column)
    : parent_t(__matrix,__column)
    { };
    
	// concept: MatrixConstColumn
    float_ptype operator[](size_t row) const
    { return (*parent_t::_matrix)(row, parent_t::_column); };

    // concept: ConstMatrix
    float_ptype operator()(size_t row_index, size_t column_index) const
    { return (*parent_t::_matrix)(row_index, parent_t::_column + column_index); };
    
	// concept: ConstMatrix2
	const_iterator begin() const { return const_iterator(this); };
	const_iterator end() const { return const_iterator(); };

	template<class ConceptMatrix1>
    bool operator ==(const ConceptMatrix1 &rhs) const
    { matrix_equal(*this, rhs); };

	// Convenience
	size_t max() const
	{
		size_t row, column;
		float_type max;

		matrix_max(*this, row, column, max);

		return row;
	}

	size_t min() const
	{
		size_t row, column;
		float_type min;

		matrix_min(*this, row, column, min);

		return row;
	}
};
