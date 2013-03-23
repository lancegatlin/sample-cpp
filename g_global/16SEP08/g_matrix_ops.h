#ifndef __G_MATRIX_OPS_H
#define __G_MATRIX_OPS_H

#include <g_global/g_matrix.h>

// namespace g_global {
    
/********************************* Row Ops ************************************/

// Row | ConceptMatrix
template<class ConceptMatrix1, class ConceptMatrix2>
DynamicMatrix operator |(const g_global::MatrixRow<ConceptMatrix1> lhs, const ConceptMatrix2 &rhs)
{
    g_global::DynamicMatrix retv(lhs);
    
    matrix_column_merge(rhs, retv);
        
    return retv;
}

// Row |= ConceptMatrix
template<class ConceptMatrix1, class ConceptMatrix2>
DynamicMatrix operator |=(g_global::MatrixRow<ConceptMatrix1> lhs, const ConceptMatrix2 &rhs)
{
    matrix_column_merge(rhs, lhs);
        
    return lhs;
}

// Row + ConceptMatrix
template<class ConceptMatrix1, class ConceptMatrix2>
DynamicMatrix operator +(g_global::MatrixRow<ConceptMatrix1> lhs, const ConceptMatrix2 &rhs)
{
    g_global::DynamicMatrix retv(   std::max(lhs.rows(),rhs.rows())
                                    ,std::max(lhs.columns(),rhs.columns())
                                    );
    
    matrix_add(lhs,rhs,retv);
        
    return retv;
}

/*
// ConceptMatrix + Row
template<class ConceptMatrix1, class ConceptMatrix2>
DynamicMatrix operator +(const ConceptMatrix1 &lhs, g_global::MatrixRow<ConceptMatrix2> rhs)
{
    g_global::DynamicMatrix retv(   std::max(lhs.rows(),rhs.rows())
                                    ,std::max(lhs.columns(),rhs.columns())
                                    );
    
    matrix_add(lhs,rhs,retv);
        
    return retv;
}
*/
// Row - ConceptMatrix
template<class ConceptMatrix1, class ConceptMatrix2>
DynamicMatrix operator -(g_global::MatrixRow<ConceptMatrix1> lhs, const ConceptMatrix2 &rhs)
{
    g_global::DynamicMatrix retv(   std::max(lhs.rows(),rhs.rows())
                                    ,std::max(lhs.columns(),rhs.columns())
                                    );
    
    matrix_subtract(lhs,rhs,retv);
        
    return retv;
}
/*
// ConceptMatrix - Row
template<class ConceptMatrix1, class ConceptMatrix2>
DynamicMatrix operator -(const ConceptMatrix1 &lhs, g_global::MatrixRow<ConceptMatrix2> rhs)
{
    g_global::DynamicMatrix retv(   std::max(lhs.rows(),rhs.rows())
                                    ,std::max(lhs.columns(),rhs.columns())
                                    );
    
    matrix_subtract(lhs,rhs,retv);
        
    return retv;
}
*/

// Row += ConceptMatrix
template<class ConceptMatrix1, class ConceptMatrix2>
g_global::MatrixRow<ConceptMatrix1> operator +=(g_global::MatrixRow<ConceptMatrix1> lhs, const ConceptMatrix2 &rhs)
{
    matrix_add(lhs,rhs,lhs);

    return lhs;
}

// Row * float_type
template<class ConceptMatrix>
g_global::DynamicMatrix operator *(g_global::MatrixRow<ConceptMatrix> lhs, float_ptype rhs)
{
    g_global::DynamicMatrix retv(lhs.rows(), lhs.columns());
    
    matrix_multiply(lhs,rhs,retv);
    
    return retv;
}

// Row / float_type
template<class ConceptMatrix>
g_global::DynamicMatrix operator /(g_global::MatrixRow<ConceptMatrix> lhs, float_ptype rhs)
{
    g_global::DynamicMatrix retv(lhs.rows(), lhs.columns());
    
    matrix_multiply(lhs,(1/rhs),retv);
    
    return retv;
}

// Row *= float_type
template<class ConceptMatrix>
g_global::MatrixRow<ConceptMatrix> operator *=(g_global::MatrixRow<ConceptMatrix> lhs, float_ptype rhs)
{
    matrix_multiply(lhs,rhs,lhs);
    
    return lhs;
}

// Row /= float_type
template<class ConceptMatrix>
g_global::MatrixRow<ConceptMatrix> operator /=(g_global::MatrixRow<ConceptMatrix> lhs, float_ptype rhs)
{
    matrix_multiply(lhs,(1/rhs),lhs);
    
    return lhs;
}

// Row * ConceptMatrix
template<class ConceptMatrix1, class ConceptMatrix2>
g_global::DynamicMatrix operator *(g_global::MatrixRow<ConceptMatrix1> lhs, const ConceptMatrix2 &rhs)
{
    g_global::DynamicMatrix retv(rhs.rows(),lhs.columns());
    
    matrix_multiply(lhs,rhs,retv);
    
    return retv;
}
/*
// ConceptMatrix * Row
template<class ConceptMatrix1, class ConceptMatrix2>
g_global::DynamicMatrix operator *(const ConceptMatrix1 &lhs, g_global::MatrixRow<ConceptMatrix2> rhs)
{
    g_global::DynamicMatrix retv(rhs.rows(),lhs.columns());
    
    matrix_multiply(lhs,rhs,retv);
    
    return retv;
}
*/
// Row *= ConceptMatrix
template<class ConceptMatrix1, class ConceptMatrix2>
g_global::MatrixRow<ConceptMatrix1> operator *=(g_global::MatrixRow<ConceptMatrix1> lhs, const ConceptMatrix2 &rhs)
{
    g_global::DynamicMatrix result(lhs.rows(), rhs.columns());
    
    matrix_multiply(lhs,rhs,result);
    
    lhs = result;
    
    return lhs;
}

// output text dump of matrix content
template<class ConceptMatrix>
std::ostream &operator <<(std::ostream &out, g_global::MatrixRow<ConceptMatrix> m)
{
    matrix_dump(out, m);
    return out;
}


/********************************* Column Ops ************************************/


// Column | ConceptMatrix
template<class ConceptMatrix1, class ConceptMatrix2>
DynamicMatrix operator |(const g_global::MatrixColumn<ConceptMatrix1> lhs, const ConceptMatrix2 &rhs)
{
    g_global::DynamicMatrix retv(lhs);
    
    matrix_column_merge(rhs, retv);
        
    return retv;
}

// Column |= ConceptMatrix
template<class ConceptMatrix1, class ConceptMatrix2>
DynamicMatrix operator |=(g_global::MatrixColumn<ConceptMatrix1> lhs, const ConceptMatrix2 &rhs)
{
    matrix_column_merge(rhs, lhs);
        
    return lhs;
}

// Column + ConceptMatrix
template<class ConceptMatrix1, class ConceptMatrix2>
DynamicMatrix operator +(g_global::MatrixColumn<ConceptMatrix1> lhs, const ConceptMatrix2 &rhs)
{
    g_global::DynamicMatrix retv(   std::max(lhs.rows(),rhs.rows())
                                    ,std::max(lhs.columns(),rhs.columns())
                                    );
    
    matrix_add(lhs,rhs,retv);
        
    return retv;
}
/*
// ConceptMatrix + Column
template<class ConceptMatrix1, class ConceptMatrix2>
DynamicMatrix operator +(const ConceptMatrix1 &lhs, g_global::MatrixColumn<ConceptMatrix2> rhs)
{
    g_global::DynamicMatrix retv(   std::max(lhs.rows(),rhs.rows())
                                    ,std::max(lhs.columns(),rhs.columns())
                                    );
    
    matrix_add(lhs,rhs,retv);
        
    return retv;
}
*/
// Column - ConceptMatrix
template<class ConceptMatrix1, class ConceptMatrix2>
DynamicMatrix operator -(g_global::MatrixColumn<ConceptMatrix1> lhs, const ConceptMatrix2 &rhs)
{
    g_global::DynamicMatrix retv(   std::max(lhs.rows(),rhs.rows())
                                    ,std::max(lhs.columns(),rhs.columns())
                                    );
    
    matrix_subtract(lhs,rhs,retv);
        
    return retv;
}
/*
// ConceptMatrix - Column
template<class ConceptMatrix1, class ConceptMatrix2>
DynamicMatrix operator -(const ConceptMatrix1 &lhs, g_global::MatrixColumn<ConceptMatrix2> rhs)
{
    g_global::DynamicMatrix retv(   std::max(lhs.rows(),rhs.rows())
                                    ,std::max(lhs.columns(),rhs.columns())
                                    );
    
    matrix_subtract(lhs,rhs,retv);
        
    return retv;
}
*/

// Column += ConceptMatrix
template<class ConceptMatrix1, class ConceptMatrix2>
g_global::MatrixColumn<ConceptMatrix1> operator +=(g_global::MatrixColumn<ConceptMatrix1> lhs, const ConceptMatrix2 &rhs)
{
    matrix_add(lhs,rhs,lhs);

    return lhs;
}

// Column * float_type
template<class ConceptMatrix>
g_global::DynamicMatrix operator *(g_global::MatrixColumn<ConceptMatrix> lhs, float_ptype rhs)
{
    g_global::DynamicMatrix retv(lhs.rows(), lhs.columns());
    
    matrix_multiply(lhs,rhs,retv);
    
    return retv;
}

// Column / float_type
template<class ConceptMatrix>
g_global::DynamicMatrix operator /(g_global::MatrixColumn<ConceptMatrix> lhs, float_ptype rhs)
{
    g_global::DynamicMatrix retv(lhs.rows(), lhs.columns());
    
    matrix_multiply(lhs,(1/rhs),retv);
    
    return retv;
}

// Column *= float_type
template<class ConceptMatrix>
g_global::MatrixColumn<ConceptMatrix> operator *=(g_global::MatrixColumn<ConceptMatrix> lhs, float_ptype rhs)
{
    matrix_multiply(lhs,rhs,lhs);
    
    return lhs;
}

// Column /= float_type
template<class ConceptMatrix>
g_global::MatrixColumn<ConceptMatrix> operator /=(g_global::MatrixColumn<ConceptMatrix> lhs, float_ptype rhs)
{
    matrix_multiply(lhs,(1/rhs),lhs);
    
    return lhs;
}

// Column * ConceptMatrix
template<class ConceptMatrix1, class ConceptMatrix2>
g_global::DynamicMatrix operator *(g_global::MatrixColumn<ConceptMatrix1> lhs, const ConceptMatrix2 &rhs)
{
    g_global::DynamicMatrix retv(lhs.rows(),rhs.columns());
    
    matrix_multiply(lhs,rhs,retv);
    
    return retv;
}
/*
// ConceptMatrix * Column
template<class ConceptMatrix1, class ConceptMatrix2>
g_global::DynamicMatrix operator *(const ConceptMatrix1 &lhs, g_global::MatrixColumn<ConceptMatrix2> rhs)
{
    g_global::DynamicMatrix retv(lhs.rows(),rhs.columns());
    
    matrix_multiply(lhs,rhs,retv);
    
    return retv;
}
*/
// Column *= ConceptMatrix
template<class ConceptMatrix1, class ConceptMatrix2>
g_global::MatrixColumn<ConceptMatrix1> operator *=(g_global::MatrixColumn<ConceptMatrix1> lhs, const ConceptMatrix2 &rhs)
{
    g_global::DynamicMatrix result(lhs.rows(),rhs.columns());
    
    matrix_multiply(lhs,rhs,result);
    
    lhs = result;
    
    return lhs;
}

// output text dump of matrix content
template<class ConceptMatrix>
std::ostream &operator <<(std::ostream &out, g_global::MatrixColumn<ConceptMatrix> m)
{
    matrix_dump(out, m);
    return out;
}


/********************************* AnyMatrix Ops *********************************/

// AnyMatrix | ConceptMatrix
template<class ConceptMatrixStorage, class ConceptMatrix2>
DynamicMatrix operator |(const g_global::AnyMatrix<ConceptMatrixStorage> lhs, const ConceptMatrix2 &rhs)
{
    g_global::DynamicMatrix retv(lhs);
    
    matrix_column_merge(rhs, retv);
        
    return retv;
}

// AnyMatrix |= ConceptMatrix
template<class ConceptMatrixStorage, class ConceptMatrix2>
DynamicMatrix operator |=(g_global::AnyMatrix<ConceptMatrixStorage> lhs, const ConceptMatrix2 &rhs)
{
    matrix_column_merge(rhs, lhs);
        
    return lhs;
}

// AnyMatrix + ConceptMatrix
template<class ConceptMatrixStorage1, class ConceptMatrix2>
g_global::DynamicMatrix operator +(const g_global::AnyMatrix<ConceptMatrixStorage1> &lhs,const ConceptMatrix2 &rhs)
{
    g_global::DynamicMatrix retv(   std::max(lhs.rows(),rhs.rows())
                                    ,std::max(lhs.columns(),rhs.columns())
                                    );
    
    matrix_add(lhs,rhs,retv);
        
    return retv;
}
/*
// ConceptMatrix + AnyMatrix
template<class ConceptMatrix1, class ConceptMatrixStorage2>
g_global::DynamicMatrix operator +(const ConceptMatrix1 &lhs, const g_global::AnyMatrix<ConceptMatrixStorage2> &rhs)
{
    g_global::DynamicMatrix retv(   std::max(lhs.rows(),rhs.rows())
                                    ,std::max(lhs.columns(),rhs.columns())
                                    );
    
    matrix_add(lhs,rhs,retv);
        
    return retv;
}
*/
// AnyMatrix - ConceptMatrix
template<class ConceptMatrixStorage1, class ConceptMatrix2>
g_global::DynamicMatrix operator -(const g_global::AnyMatrix<ConceptMatrixStorage1> &lhs,const ConceptMatrix2 &rhs)
{
    g_global::DynamicMatrix retv(   std::max(lhs.rows(),rhs.rows())
                                    ,std::max(lhs.columns(),rhs.columns())
                                    );
    
    matrix_subtract(lhs,rhs,retv);
        
    return retv;
}
/*
// ConceptMatrix + AnyMatrix
template<class ConceptMatrix1, class ConceptMatrixStorage2>
g_global::DynamicMatrix operator -(const ConceptMatrix1 &lhs, const g_global::AnyMatrix<ConceptMatrixStorage2> &rhs)
{
    g_global::DynamicMatrix retv(   std::max(lhs.rows(),rhs.rows())
                                    ,std::max(lhs.columns(),rhs.columns())
                                    );
    
    matrix_subtract(lhs,rhs,retv);
        
    return retv;
}
*/
// AnyMatrix += ConceptMatrix
template<class ConceptMatrixStorage1, class ConceptMatrix2>
g_global::AnyMatrix<ConceptMatrixStorage1> &operator +=(g_global::AnyMatrix<ConceptMatrixStorage1> &lhs,const ConceptMatrix2 &rhs)
{
    matrix_add(lhs,rhs,lhs);

    return lhs;
}

// AnyMatrix * float_type
template<class ConceptMatrixStorage>
g_global::DynamicMatrix operator *(const g_global::AnyMatrix<ConceptMatrixStorage> &lhs, float_ptype rhs)
{
    g_global::DynamicMatrix retv(lhs.rows(), lhs.columnns());
    
    matrix_multiply(lhs,rhs,retv);
    
    return retv;
}

// AnyMatrix / float_type
template<class ConceptMatrixStorage>
g_global::DynamicMatrix operator /(const g_global::AnyMatrix<ConceptMatrixStorage> &lhs, float_ptype rhs)
{
    g_global::DynamicMatrix retv(lhs.rows(), lhs.columns());
    
    matrix_multiply(lhs,(1/rhs),retv);
    
    return retv;
}

// AnyMatrix *= float_type
template<class ConceptMatrixStorage>
g_global::AnyMatrix<ConceptMatrixStorage> &operator *=(g_global::AnyMatrix<ConceptMatrixStorage> &lhs,float_ptype rhs)
{
    matrix_multiply(lhs,rhs,lhs);
    
    return lhs;
}

// AnyMatrix /= float_type
template<class ConceptMatrixStorage>
g_global::AnyMatrix<ConceptMatrixStorage> &operator /=(g_global::AnyMatrix<ConceptMatrixStorage> &lhs,float_ptype rhs)
{
    matrix_multiply(lhs,(1/rhs),lhs);
    
    return lhs;
}

// AnyMatrix * ConceptMatrix
template<class ConceptMatrixStorage1, class ConceptMatrix2>
g_global::DynamicMatrix operator *(const g_global::AnyMatrix<ConceptMatrixStorage1> &lhs,const ConceptMatrix2 &rhs)
{
    g_global::DynamicMatrix retv(lhs.rows(),rhs.columns());
    
    matrix_multiply(lhs,rhs,retv);
    
    return retv;
}
/*
// ConceptMatrix * AnyMatrix
template<class ConceptMatrix1, class ConceptMatrixStorage2>
g_global::DynamicMatrix operator *(const ConceptMatrix1 &lhs, const g_global::AnyMatrix<ConceptMatrixStorage2> &rhs)
{
    g_global::DynamicMatrix retv(lhs.rows(), rhs.columns());
    
    matrix_multiply(lhs,rhs,retv);
    
    return retv;
}
*/
// AnyMatrix *= ConceptMatrix
template<class ConceptMatrixStorage1, class ConceptMatrix2>
g_global::AnyMatrix<ConceptMatrixStorage1> &operator *=(g_global::AnyMatrix<ConceptMatrixStorage1> &lhs,const ConceptMatrix2 &rhs)
{
    g_global::DynamicMatrix result(lhs.rows(), rhs.columns());
    
    matrix_multiply(lhs,rhs,result);
    
    lhs = result;
    
    return lhs;
}

// output text dump of matrix content
template<class ConceptMatrixStorage>
std::ostream &operator <<(std::ostream &out, const g_global::AnyMatrix<ConceptMatrixStorage> &m)
{
    matrix_dump(out, m);
    return out;
}

// } // namespace g_global

#endif
