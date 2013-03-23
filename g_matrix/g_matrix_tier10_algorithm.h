/*
    File: g_matrix_tier10_algorithm.h
    Author: lance.gatlin@yahoo.com
    Date: 19 Sep 2008
    Version: 1

    Overview: 
        1) Declares and implements the following matrix functions:
		matrix_column_merge
		matrix_add
		matrix_subtract
		matrix_multiply
		matrix_multiply_equal
		matrix_divide
	2) Functions return a DynamicMatrix as temporary
*/

// ConceptMatrix | ConceptMatrix
template<class ConceptMatrix1, class ConceptMatrix2>
inline DynamicMatrix matrix_column_merge(const ConceptMatrix1 &lhs, const ConceptMatrix2 &rhs)
{
    DynamicMatrix retv(lhs);
    
    matrix_column_merge(rhs, retv);
        
    return retv;
}

// ConceptMatrix + ConceptMatrix
template<class ConceptMatrix1, class ConceptMatrix2>
inline DynamicMatrix matrix_add(const ConceptMatrix1 &_lhs, const ConceptMatrix2 &_rhs)
{
    MatrixConcept<const ConceptMatrix1> lhs(_lhs);
    MatrixConcept<const ConceptMatrix2> rhs(_rhs);
    
    DynamicMatrix retv(   std::max(lhs.rows(),rhs.rows())
                                    ,std::max(lhs.columns(),rhs.columns())
                                    );
    
    matrix_add(_lhs,_rhs,retv);
        
    return retv;
}

// ConceptMatrix - ConceptMatrix
template<class ConceptMatrix1, class ConceptMatrix2>
inline DynamicMatrix matrix_subtract(const ConceptMatrix1 &_lhs, const ConceptMatrix2 &_rhs)
{
    MatrixConcept<const ConceptMatrix1> lhs(_lhs);
    MatrixConcept<const ConceptMatrix2> rhs(_rhs);
    
    DynamicMatrix retv(   std::max(lhs.rows(),rhs.rows())
                                    ,std::max(lhs.columns(),rhs.columns())
                                    );
    
    matrix_subtract(_lhs,_rhs,retv);
        
    return retv;
}

// ConceptMatrix * ConceptMatrix
template<class ConceptMatrix1, class ConceptMatrix2>
inline DynamicMatrix matrix_multiply(const ConceptMatrix1 &_lhs, const ConceptMatrix2 &_rhs)
{
    MatrixConcept<const ConceptMatrix1> lhs(_lhs);
    MatrixConcept<const ConceptMatrix2> rhs(_rhs);
    
    DynamicMatrix retv(lhs.rows(),rhs.columns());
    
    matrix_multiply(_lhs,_rhs,retv);
    
    return retv;
}

// ConceptMatrix *= ConceptMatrix
template<class ConceptMatrix1, class ConceptMatrix2>
inline void matrix_multiply_equal(ConceptMatrix1 &_lhs, const ConceptMatrix2 &_rhs)
{
    MatrixConcept<const ConceptMatrix1> lhs(_lhs);
    MatrixConcept<const ConceptMatrix2> rhs(_rhs);
    
    DynamicMatrix temp(rhs.rows(),lhs.columns());
    
    matrix_multiply(_lhs,_rhs,temp);
    
    matrix_copy(temp, _lhs);
}

// ConceptMatrix * float_type
template<class ConceptMatrix>
inline DynamicMatrix matrix_multiply(const ConceptMatrix &_lhs, float_ptype rhs)
{
    MatrixConcept<const ConceptMatrix> lhs(_lhs);

    DynamicMatrix retv(lhs.rows(), lhs.columns());
    
    matrix_multiply(_lhs,rhs,retv);
    
    return retv;
}

// ConceptMatrix / float_type
template<class ConceptMatrix>
inline DynamicMatrix matrix_divide(const ConceptMatrix &_lhs, float_ptype rhs)
{
    MatrixConcept<const ConceptMatrix> lhs(_lhs);

    DynamicMatrix retv(lhs.rows(), lhs.columns());
    
    matrix_multiply(_lhs,(1/rhs),retv);
    
    return retv;
}
