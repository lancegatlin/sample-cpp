#ifndef __G_MATRIX_TIER5_CLASS_STATICMATRIX_H
#define __G_MATRIX_TIER5_CLASS_STATICMATRIX_H

/*
    File: g_matrix_tier5_class_AnyMatrix.h
    Author: lance.gatlin@yahoo.com
    Date: 19 Sep 2008
    Version: 1

    Overview: 
	1) Declares and implements class StaticMatrix
	2) Declares make_matrix function that creates a StaticMatrix out of a matrix array 
*/

namespace g_matrix {

template<unsigned long ROWS, unsigned long COLUMNS>
class StaticMatrix : public AnyMatrix<MatrixStaticStorage<ROWS,COLUMNS> > {
    public:
    typedef AnyMatrix<MatrixStaticStorage<ROWS,COLUMNS> > parent_t;
    typedef StaticMatrix<ROWS,COLUMNS> this_t;
    typedef float_type array_t[ROWS][COLUMNS];
        
    StaticMatrix() { };
    
    template<class ConceptMatrix>
    StaticMatrix(const ConceptMatrix &copy_me)
    {
        operator =(copy_me);
    };
    
	StaticMatrix(const this_t &copy_me)
    : parent_t((const parent_t &)copy_me)
    { };

	// default destructor

    template<class ConceptMatrix>
    this_t &operator =(const ConceptMatrix &assign_me)
	{ parent_t::operator =(assign_me); return *this; };

    this_t &operator =(const this_t &assign_me)
	{ parent_t::operator =((const parent_t &)assign_me); return *this; };
};

template<unsigned long ROWS, unsigned long COLUMNS>
inline StaticMatrix<ROWS, COLUMNS> make_matrix(float_type (&m)[ROWS][COLUMNS])
{ return StaticMatrix<ROWS, COLUMNS>(m); }

} // namespace g_matrix

#endif
