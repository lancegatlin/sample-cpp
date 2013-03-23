/*
    File: g_matrix_tier8_class_AnyMatrix.h
    Author: lance.gatlin@yahoo.com
    Date: 19 Sep 2008
    Version: 1

    Overview: 
	1) Declares and implements class AnyMatrix
*/

template<class ConceptMatrix>
class AnyMatrix : public ConceptMatrix {
    public:
    typedef ConceptMatrix parent_t;
    typedef AnyMatrix<parent_t> this_t;

    typedef MatrixIterator<this_t> iterator;
    typedef MatrixIterator<const this_t> const_iterator;
    typedef MatrixSlice<this_t> slice_t;
    typedef MatrixSlice<const this_t> const_slice_t;
    
    typedef MatrixRow<this_t> row_t;
    typedef MatrixRow<const this_t> const_row_t;
    typedef MatrixColumn<this_t> column_t;
    typedef MatrixColumn<const this_t> const_column_t;
       
    AnyMatrix() { };
	
	AnyMatrix(const this_t &copy_me)
    : parent_t((const parent_t &)copy_me)
	{ };
	
	// default destructor

	// concept: Matrix
	// Inherited from parent

	// concept: Matrix2
    const_iterator begin() const { return const_iterator(this); };
    const_iterator end() const { return const_iterator(); };
    iterator begin() { return iterator(this); };
    iterator end() { return iterator(); };
    
    template<class ConceptMatrix2>
    void assign(const ConceptMatrix2 &assign_me)
    { matrix_copy(assign_me, *this); };    
    template<class ConceptMatrix2>
    this_t &operator =(const ConceptMatrix2 &assign_me)
    { assign(assign_me); return *this; };
	this_t &operator =(const this_t &assign_me)
	{ parent_t::operator =((const parent_t &)assign_me); return *this; };

    template<class ConceptMatrix2>
    void swap(ConceptMatrix2 &m) 
    { matrix_swap(*this, m); };
    void swap(this_t &m)
	{ parent_t::swap((const parent_t &)m); };

    template<class ConceptMatrix2>
    bool equal(const ConceptMatrix2 &rhs) const
    { return matrix_equal(*this, rhs); }
    template<class ConceptMatrix2>
    bool operator ==(const ConceptMatrix2 &rhs) const
    { return equal(rhs); }
    bool operator ==(const this_t &rhs) const
	{ return parent_t::operator ==((const parent_t &)rhs); }
    
	// concept: Matrix3
	const_row_t operator[](size_t r) const { return row(r); };
    row_t operator[](size_t r) { return row(r); };
    
    row_t row(size_t r) { return row_t(this, r); };
    const_row_t row(size_t r) const { return row_t(this, r); };
    column_t column(size_t c) { return column_t(this, c); };
    const_column_t column(size_t c) const { return column_t(this, c); };
    
    // concept: Matrix4
    slice_t slice(size_t row_begin, size_t column_begin)
    { return slice_t(this, row_begin, column_begin, parent_t::rows(), parent_t::columns()); };
    
    const_slice_t slice(size_t row_begin, size_t column_begin) const
    { return const_slice_t(this, row_begin, column_begin, parent_t::rows(), parent_t::columns()); };

    slice_t slice(size_t row_begin, size_t column_begin, size_t row_end, size_t column_end)
    { return slice_t (this, row_begin, column_begin, row_end, column_end); };
    
    const_slice_t slice(size_t row_begin, size_t column_begin, size_t row_end, size_t column_end) const
    { return const_slice_t(this, row_begin, column_begin, row_end, column_end); };

    // Convenience
    void zero() { fill(0.0); };
    void fill(float_ptype value) { matrix_fill(*this, value); };
    void setIdentity() { matrix_set_identity(*this); }
    float_type getDeterminant() const
    { return matrix_determinant(*this); };    
};
