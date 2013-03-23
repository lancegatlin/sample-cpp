#ifndef __G_MATRIX_COLUMN_H
#define __G_MATRIX_COLUMN_H

namespace g_global {
    
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
    
    size_t column() { return _column; };
    matrix_t *matrix() { return _matrix; };

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

    MatrixColumn(matrix_t *__matrix, size_t __column)
    : parent_t(__matrix,__column)
    { };
    
    float_type &operator[](size_t row) const
    { return (*parent_t::_matrix)(row, parent_t::_column); };

    // concept: Matrix
    float_type &operator()(size_t row_index, size_t column_index) const
    { return (*parent_t::_matrix)(row_index, parent_t::_column + column_index); };
    
    template<class ConceptMatrix1>
    this_t &operator =(const ConceptMatrix1 &assign_me)
    { matrix_copy(assign_me, *this); return *this; }
    
    template<class ConceptMatrix1>
    bool operator ==(const ConceptMatrix1 &rhs)
    { matrix_equal(*this, rhs); };

    template<class OtherConceptMatrix>
    void swap(OtherConceptMatrix &m)
    { matrix_swap(*this, m); };

    void swap(this_t m)
    { matrix_swap(*this, m); };
    
    operator MatrixColumn<const ConceptMatrix>() const
    { return *(MatrixColumn<const ConceptMatrix> *)this; };
};

// concept: MatrixConstColumn
template<class ConceptMatrix>
class MatrixColumn<const ConceptMatrix> : public MatrixColumnBase<const ConceptMatrix> {
    public:
    typedef MatrixColumn<ConceptMatrix> this_t;
    typedef const ConceptMatrix matrix_t;
    typedef MatrixColumnBase<matrix_t> parent_t;

    MatrixColumn(matrix_t *__matrix, size_t __column)
    : parent_t(__matrix,__column)
    { };
    
    float_ptype operator[](size_t row) const
    { return (*parent_t::_matrix)(row, parent_t::_column); };

    // concept: ConstMatrix
    float_ptype operator()(size_t row_index, size_t column_index) const
    { return (*parent_t::_matrix)(row_index, parent_t::_column + column_index); };
    
    template<class ConceptMatrix1>
    bool operator ==(const ConceptMatrix1 &rhs)
    { matrix_equal(*this, rhs); };
};

} // namespace g_global

#endif
