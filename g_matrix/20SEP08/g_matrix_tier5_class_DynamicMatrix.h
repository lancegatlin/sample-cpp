#ifndef __G_MATRIX_TIER5_CLASS_DYNAMICMATRIX_H
#define __G_MATRIX_TIER5_CLASS_DYNAMICMATRIX_H

/*
    File: g_matrix_tier5_class_DynamicMatrix.h
    Author: lance.gatlin@yahoo.com
    Date: 19 Sep 2008
    Version: 1

    Overview: 
	1) Declares and implements DynamicMatrix 
*/

namespace g_matrix {

class DynamicMatrix : public AnyMatrix<MatrixDynamicStorage> {
    public:
    typedef AnyMatrix<MatrixDynamicStorage> parent_t;
    typedef DynamicMatrix this_t;
    
    DynamicMatrix() { };
    
    DynamicMatrix(size_t rows, size_t columns)
    {
        reserve(rows, columns); 
    };
    
    template<class ConceptMatrix>
    DynamicMatrix(const ConceptMatrix &_copy_me)
    {
        MatrixConcept<const ConceptMatrix> copy_me(_copy_me);
        
        reserve(copy_me.rows(), copy_me.columns());
        assign(_copy_me);
    };

    template<class Matrix>
    DynamicMatrix(  const Matrix &slice_me
                ,size_t row_begin
                ,size_t column_begin
                ,size_t row_end
                ,size_t column_end
            )
    {
        reserve(row_end - row_begin, column_end - column_begin);
        matrix_slice(slice_me, row_begin, column_begin, row_end, column_end, *this);
    };

	DynamicMatrix(const this_t &copy_me)
    : parent_t((const parent_t &)copy_me)
    { };

	// default destructor

    template<class ConceptMatrix>
    this_t &operator =(const ConceptMatrix &assign_me)
	{ parent_t::operator =(assign_me); return *this; };

    this_t &operator =(const this_t &assign_me)
	{ parent_t::operator =((const parent_t &)assign_me); return *this; };
};

} // namespace g_matrix

#endif
