/*
    File: g_matrix_tier4_class_MatrixRowh
    Author: lance.gatlin@yahoo.com
    Date: 19 Sep 2008
    Version: 1

    Overview: 
	1) Declares and implements MatrixRow
*/

template<class ConceptMatrix>
class MatrixRowBase {
    protected:
    ConceptMatrix *_matrix;
    size_t _row;
    
    public:
    typedef MatrixRowBase<ConceptMatrix> this_t;
    typedef ConceptMatrix matrix_t;

    MatrixRowBase(matrix_t *__matrix, size_t __row)
    : _matrix(__matrix), _row(__row)
    { };
	
	// Accessors
    size_t row() const { return _row; };
    matrix_t *matrix() const { return _matrix; };
    
	// concept: Matrix
	size_t rows() const { return 1; };
    size_t columns() const { return _matrix->columns(); };
};



// concept: MatrixRow
template<class ConceptMatrix>
class MatrixRow : public MatrixRowBase<ConceptMatrix> {
    public:
    typedef MatrixRow<ConceptMatrix> this_t;
    typedef MatrixRowBase<ConceptMatrix> parent_t;
    typedef ConceptMatrix matrix_t;
	typedef MatrixIterator<this_t> iterator;
	typedef MatrixIterator<const this_t> const_iterator;

    MatrixRow(matrix_t *__matrix, size_t __row)
    : parent_t(__matrix,__row)
    { };

	// concept: MatrixRow    
    float_type &operator[](size_t column)
    { return (*parent_t::_matrix)(parent_t::_row, column); };
    
    float_ptype operator[](size_t column) const
    { return (*parent_t::_matrix)(parent_t::_row, column); };

    // concept: Matrix
    float_ptype operator()(size_t row_index, size_t column_index) const
    { return (*parent_t::_matrix)(parent_t::_row + row_index, column_index); };
    
    float_type &operator()(size_t row_index, size_t column_index)
    { return (*parent_t::_matrix)(parent_t::_row + row_index, column_index); };
    
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

	// Convert to const row if needed
    operator MatrixRow<const ConceptMatrix>() const
    { return *(MatrixRow<const ConceptMatrix> *)this; };

	// Convenience
	size_t max() const
	{
		size_t row, column;
		float_type max;

		matrix_max(*this, row, column, max);

		return column;
	}

	size_t min() const
	{
		size_t row, column;
		float_type min;

		matrix_min(*this, row, column, min);

		return column;
	}
};

template<class ConceptMatrix>
class MatrixRow<const ConceptMatrix> : public MatrixRowBase<const ConceptMatrix> {
    public:
    typedef MatrixRow<const ConceptMatrix> this_t;
    typedef MatrixRowBase<const ConceptMatrix> parent_t;
    typedef const ConceptMatrix matrix_t;
	typedef MatrixIterator<const this_t> const_iterator;

    MatrixRow(matrix_t *__matrix, size_t __row)
    : parent_t(__matrix,__row)
    { };
    
	// concept: MatrixConstRow
    float_ptype operator[](size_t column) const
    { return (*parent_t::_matrix)(parent_t::_row, column); };

    // concept: ConstMatrix
    float_ptype operator()(size_t row_index, size_t column_index) const
    { return (*parent_t::_matrix)(parent_t::_row + row_index, column_index); };
    
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

		return column;
	}

	size_t min() const
	{
		size_t row, column;
		float_type min;

		matrix_min(*this, row, column, min);

		return column;
	}
};
