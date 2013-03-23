/*
    File: g_matrix_tier6_class_MatrixSlice.h
    Author: lance.gatlin@yahoo.com
    Date: 19 Sep 2008
    Version: 1

    Overview: 
	1) Declares and implements MatrixSlice
*/

template<class ConceptMatrix>
class MatrixSliceBase {
    protected:
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
                    ,size_t __column_begin)
	: _matrix(&__matrix)
	, _row_begin(__row_begin)
    , _column_begin(__column_begin)
    {
		MatrixConcept<ConceptMatrix> m(__matrix);
		_row_end = m.rows();
		_column_end = m.columns();
	}; 

    MatrixSliceBase(matrix_t &__matrix
                    ,size_t __row_begin
                    ,size_t __column_begin
                    ,size_t __row_end
                    ,size_t __column_end)
	: _matrix(&__matrix)
	, _row_begin(__row_begin)
    , _row_end(__row_end)
	, _column_begin(__column_begin)
    , _column_end(__column_end) 
    { }; 

	// default copy constructor
	// default assignment to self
	// default destructor

	// Accessors
	matrix_t *matrix() const { return _matrix; };
    size_t row_begin() const { return _row_begin; };
    size_t row_end() const { return _row_end; };
    size_t column_begin() const { return _column_begin; };
    size_t column_end() const { return _column_end; };
    
    // concept Matrix
    size_t rows() const { return _row_end - _row_begin; };
    size_t columns() const { return _column_end - _column_begin; };

    protected:
	void checkOutOfBounds(size_t row, size_t column) const
	{
		if(row >= rows()|| column >= columns())
			throw MatrixOutOfBounds();
	}
};

template<class ConceptMatrix>
class MatrixSlice : public MatrixSliceBase<ConceptMatrix> {
    public:
    typedef MatrixSlice<ConceptMatrix> this_t;
    typedef MatrixSliceBase<ConceptMatrix> parent_t;
    typedef ConceptMatrix matrix_t;
	typedef MatrixRow<this_t> row_t;
	typedef MatrixRow<const this_t> const_row_t;
	typedef MatrixColumn<this_t> column_t;
	typedef MatrixColumn<const this_t> const_column_t;
	typedef MatrixIterator<this_t> iterator;
	typedef MatrixIterator<const this_t> const_iterator;

    MatrixSlice(matrix_t *__matrix = NULL
                    ,size_t __row_begin = 0
                    ,size_t __col_begin = 0
                    ,size_t __row_end = 0
                    ,size_t __col_end = 0)
    : parent_t(__matrix, __row_begin, __col_begin, __row_end, __col_end) 
    { }; 

    MatrixSlice(matrix_t &__matrix
                    ,size_t __row_begin
                    ,size_t __col_begin)
    : parent_t(__matrix, __row_begin, __col_begin)
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
    
    // concept Matrix
    float_ptype operator()(size_t row_index, size_t column_index) const
    { 
		parent_t::checkOutOfBounds(row_index, column_index);
	
		return (*parent_t::_matrix)(parent_t::_row_begin + row_index, parent_t::_column_begin + column_index); 
	};

    float_type &operator()(size_t row_index, size_t column_index)
    {
		parent_t::checkOutOfBounds(row_index, column_index);
		
		return (*parent_t::_matrix)(parent_t::_row_begin + row_index, parent_t::_column_begin + column_index); 
	};
    
	// concept: Matrix2
	iterator begin() { return iterator(this); };
	iterator end() { return iterator(); };
	const_iterator begin() const { return const_iterator(this); };
	const_iterator end() const { return const_iterator(); };

    template<class ConceptMatrix1>
    bool operator ==(const ConceptMatrix1 &rhs) const
    { matrix_equal(*this, rhs); };
    
	template<class ConceptMatrix1>
    this_t &operator =(const ConceptMatrix1 &assign_me)
    { matrix_copy(assign_me, *this); return *this; }
    
    template<class ConceptMatrix1>
    void swap(ConceptMatrix1 &m)
    { matrix_swap(*this, m); };

	// Pass by value for temporaries
    void swap(this_t m)
    { matrix_swap(*this, m); };

	// concept: Matrix3
	row_t operator[](size_t r)  { return row(r); };
	row_t row(size_t r) { return row_t(this, r); };
	column_t column(size_t c) { return column_t(this, c); };

	const_row_t operator[](size_t r) const { return row(r); };
	const_row_t row(size_t r) const { return row_t(this, r); };
	const_column_t column(size_t c) const { return column_t(this, c); };

	// Convert to const slice if needed
    operator MatrixSlice<const ConceptMatrix>() const
    { return *(MatrixSlice<const ConceptMatrix>)this; };    
};

template<class ConceptMatrix>
class MatrixSlice<const ConceptMatrix> : public MatrixSliceBase<ConceptMatrix> {
    public:
    typedef MatrixSlice<const ConceptMatrix> this_t;
    typedef MatrixSliceBase<const ConceptMatrix> parent_t;
    typedef const ConceptMatrix matrix_t;
	typedef MatrixIterator<const this_t> const_iterator;
	typedef MatrixRow<const this_t> const_row_t;
	typedef MatrixColumn<const this_t> const_column_t;
    
    MatrixSlice(matrix_t *__matrix = NULL
                    ,size_t __row_begin = 0
                    ,size_t __col_begin = 0
                    ,size_t __row_end = 0
                    ,size_t __col_end = 0)
    : parent_t(__matrix, __row_begin, __col_begin, __row_end, __col_end) 
    { }; 

    MatrixSlice(matrix_t &__matrix
                    ,size_t __row_begin
                    ,size_t __col_begin)
    : parent_t(__matrix, __row_begin, __col_begin)
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

    // concept ConstMatrix2
	const_iterator begin() const { return const_iterator(this); };
	const_iterator end() const { return const_iterator(); };

    template<class ConceptMatrix1>
    bool operator ==(const ConceptMatrix1 &rhs) const
    { matrix_equal(*this, rhs); };
    
	// concept ConstMatrix3
	const_row_t operator[](size_t r) const { return row(r); };
	const_row_t row(size_t r) const { return row_t(this, r); };
	const_column_t column(size_t c) const { return column_t(this, c); };
};
