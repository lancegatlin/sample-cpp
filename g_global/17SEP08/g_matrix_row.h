#ifndef __G_MATRIX_ROW_H
#define __G_MATRIX_ROW_H

namespace g_global {
    
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

    MatrixRow(matrix_t *__matrix, size_t __row)
    : parent_t(__matrix,__row)
    { };
    
    float_type &operator[](size_t column) const
    { return (*parent_t::_matrix)(parent_t::_row, column); };
    
    // concept: Matrix
    float_type &operator()(size_t row_index, size_t column_index) const
    { return (*parent_t::_matrix)(parent_t::_row + row_index, column_index); };
    
    template<class ConceptMatrix1>
    this_t &operator =(const ConceptMatrix1 &assign_me)
    { matrix_copy(assign_me, *this); return *this; }
    
    template<class ConceptMatrix1>
    bool operator ==(const ConceptMatrix1 &rhs)
    { matrix_equal(*this, rhs); };
    
    template<class OtherConceptMatrix>
    void swap(OtherConceptMatrix &m)
    { matrix_swap(*this, m); };

    // allow pass by for temporary variables
    void swap(this_t m)
    { matrix_swap(*this, m); };
    
    operator MatrixRow<const ConceptMatrix>() const
    { return *(MatrixRow<const ConceptMatrix> *)this; };
};

// concept: MatrixConstRow
template<class ConceptMatrix>
class MatrixRow<const ConceptMatrix> : public MatrixRowBase<const ConceptMatrix> {
    public:
    typedef MatrixRow<const ConceptMatrix> this_t;
    typedef MatrixRowBase<const ConceptMatrix> parent_t;
    typedef const ConceptMatrix matrix_t;

    MatrixRow(matrix_t *__matrix, size_t __row)
    : parent_t(__matrix,__row)
    { };
    
    float_ptype operator[](size_t column) const
    { return (*parent_t::_matrix)(parent_t::_row, column); };

    // concept: ConstMatrix
    float_ptype operator()(size_t row_index, size_t column_index) const
    { return (*parent_t::_matrix)(parent_t::_row + row_index, column_index); };
    
    template<class ConceptMatrix1>
    bool operator ==(const ConceptMatrix1 &rhs)
    { matrix_equal(*this, rhs); };
};

} // namespace g_global

#endif
