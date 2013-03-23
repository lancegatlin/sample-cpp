#ifndef __G_MATRIX_TIER_4_CLASS_ANYMATRIX_H
#define __G_MATRIX_TIER_4_CLASS_ANYMATRIX_H

/*
    File: g_matrix_tier4_class_AnyMatrix.h
    Author: lance.gatlin@yahoo.com
    Date: 19 Sep 2008
    Version: 1

    Overview: 
	1) Declares and implements class AnyMatrix
*/

namespace g_matrix {

template<class MatrixStorage>
class AnyMatrix : public MatrixStorage {
    public:
    typedef MatrixStorage storage_t;
    typedef storage_t parent_t;
    typedef AnyMatrix<storage_t> this_t;
    typedef this_t matrix_t;

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

    // Iterator
    const_iterator begin() const { return const_iterator(this); };
    const_iterator end() const { return const_iterator(); };
    iterator begin() { return iterator(this); };
    iterator end() { return iterator(); };
    
    // No bounds checking
    const_row_t operator[](size_t row_zero_based_index) const
    { return const_row_t(this, row_zero_based_index); };
    
    row_t operator[](size_t row_zero_based_index)
    { return row_t(this, row_zero_based_index); };
    
    float_ptype operator()(size_t row_zero_based_index, size_t column_zero_based_index) const
    { return parent_t::operator()(row_zero_based_index, column_zero_based_index); };
   
    float_type &operator()(size_t row_zero_based_index, size_t column_zero_based_index)
    { return parent_t::operator()(row_zero_based_index, column_zero_based_index); };

    // Row/Column accessors
    row_t row(size_t row_zero_based_index)
    { return row_t(this, row_zero_based_index); };

    const_row_t row(size_t row_zero_based_index) const
    { return row_t(this, row_zero_based_index); };
    
    column_t column(size_t column_zero_based_index)
    { return column_t(this, column_zero_based_index); };

    const_column_t column(size_t column_zero_based_index) const
    { return column_t(this, column_zero_based_index); };
    
    // Mutators
    void zero() { fill(0.0); };
    void fill(float_ptype value) { matrix_fill(*this, value); };
    
    void setIdentity() { matrix_set_identity(*this); }
    
    // Assignment
    template<class ConceptMatrix>
    void assign(const ConceptMatrix &assign_me)
    { matrix_copy(assign_me, *this); };
    
    template<class ConceptMatrix>
    this_t &operator =(const ConceptMatrix &assign_me)
    { assign(assign_me); return *this; };

	this_t &operator =(const this_t &assign_me)
	{ parent_t::operator =((const parent_t &)assign_me); return *this; };

    // Equality
    template<class ConceptMatrix>
    bool equal(const ConceptMatrix &rhs) const
    { return matrix_equal(*this, rhs); }

    template<class ConceptMatrix>
    bool operator ==(const ConceptMatrix &rhs) const
    { return equal(rhs); }
    
    // Submatrix
    slice_t submatrix(size_t row_begin, size_t column_begin)
    { return slice_t(this, row_begin, column_begin, parent_t::rows(), parent_t::columns()); };
    
    const_slice_t submatrix(size_t row_begin, size_t column_begin) const
    { return const_slice_t(this, row_begin, column_begin, parent_t::rows(), parent_t::columns()); };

    slice_t submatrix(size_t row_begin, size_t column_begin, size_t row_end, size_t column_end)
    { return slice_t (this, row_begin, column_begin, row_end, column_end); };
    
    const_slice_t submatrix(size_t row_begin, size_t column_begin, size_t row_end, size_t column_end) const
    { return const_slice_t(this, row_begin, column_begin, row_end, column_end); };

    // Determinant
    float_type getDeterminant() const
    { return matrix_determinant(*this); };

    template<class ConceptMatrix>
    void swap(ConceptMatrix &m) 
    { matrix_swap(*this, m); };

    void swap(this_t &m)
    { matrix_swap(*this, m); };
};

} // namespace g_matrix

#endif
