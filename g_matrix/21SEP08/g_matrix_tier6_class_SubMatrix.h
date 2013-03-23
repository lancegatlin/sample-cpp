/*
    File: g_matrix_tier6_class_SubMatrix.h
    Author: lance.gatlin@yahoo.com
    Date: 19 Sep 2008
    Version: 1

    Overview: 
	1) Declares and implements class SubMatrix
*/

template<class ConceptMatrix>
class SubMatrix : public MatrixAdaptor<MatrixSlice<ConceptMatrix> > {
    public:
    typedef SubMatrix<ConceptMatrix> this_t;
    typedef MatrixAdaptor<MatrixSlice<ConceptMatrix> > parent_t;
    typedef MatrixSlice<ConceptMatrix> slice_t;
    
    SubMatrix(ConceptMatrix &m, size_t row_begin, size_t column_begin)
    : parent_t(slice_t(m, row_begin, column_begin, m.rows(), m.columns()))
    { }

    SubMatrix(ConceptMatrix &m, size_t row_begin, size_t row_end, size_t column_begin, size_t column_end)
    : parent_t(slice_t(m, row_begin, row_end, column_begin, column_end))
    { }
    
    SubMatrix(slice_t copy_me)
    : parent_t(copy_me)
    { };
    
    SubMatrix(const this_t &copy_me)
    : parent_t((const parent_t &)copy_me)
    { };
    
    // default destructor
    
    template<class OtherConceptMatrix>
    this_t &operator =(const OtherConceptMatrix &assign_me)
    { assign(assign_me); return *this; };
    
    this_t &operator =(const this_t &assign_me)
    { parent_t::operator =((const parent_t &)assign_me); return *this; };
};

template<class ConceptMatrix>
class SubMatrix<const ConceptMatrix> : public MatrixAdaptor<MatrixSlice<const ConceptMatrix> > {
    public:
    typedef SubMatrix<const ConceptMatrix> this_t;
    typedef MatrixAdaptor<MatrixSlice<const ConceptMatrix> > parent_t;
    typedef MatrixSlice<const ConceptMatrix> slice_t;
    
    SubMatrix(const ConceptMatrix &m, size_t row_begin, size_t column_begin)
    : parent_t(slice_t(m, row_begin, m.rows(), column_begin, m.columns()))
    { }

    SubMatrix(const ConceptMatrix &m, size_t row_begin, size_t row_end, size_t column_begin, size_t column_end)
    : parent_t(slice_t(m, row_begin, row_end, column_begin, column_end))
    { }

    SubMatrix(const this_t &copy_me)
    : parent_t((const parent_t &)copy_me)
    { };

    this_t &operator =(const this_t &assign_me)
    { parent_t::operator =((const parent_t &)assign_me); return *this; };
};

