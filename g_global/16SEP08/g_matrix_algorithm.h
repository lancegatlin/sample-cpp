#ifndef __G_MATRIX_ALGORITHM_H
#define __G_MATRIX_ALOGRITHM_H

/*
    Most generic form but not the most convenient
*/

#include <g_global/g_global.h>

namespace g_global {

template<class ConceptMatrix>
inline void matrix_fill(ConceptMatrix &m, float_ptype value)
{
    size_t i_stop = m.rows(),
            j_stop = m.columns();
            
    for(size_t i=0;i<i_stop;i++)
        for(size_t j=0;j<j_stop;j++)
            m(i,j) = value;
}

template<class ConceptMatrix>
inline void matrix_set_identity(ConceptMatrix &m)
{
    size_t i_stop = m.rows(),
            j_stop = m.columns();
            
    for(size_t i=0;i<i_stop;i++)
        for(size_t j=0;j<j_stop;j++)
            m(i,j) = (i == j ? 1 : 0);
}

template<class ConceptMatrix1, class ConceptMatrix2>
inline void matrix_column_merge(const ConceptMatrix1 &src, ConceptMatrix2 &dest)
{
    size_t i_stop = src.rows() < dest.rows() ? src.rows() : dest.rows()
            ,j_stop = src.columns();
    
    size_t j_dest_start = dest.columns();
    
    for(size_t i=0;i<i_stop;i++)
    {
        size_t j_dest=j_dest_start;
        for(size_t j=0;j<j_stop;j++, j_dest++)
            dest(i,j_dest) = src(i, j);
    } 
}

template<class ConceptMatrix1, class ConceptMatrix2>
inline void matrix_copy(const ConceptMatrix1 &src, ConceptMatrix2 &dest)
{
    size_t i_stop = src.rows() < dest.rows() ? src.rows() : dest.rows(),
            j_stop = src.columns() < dest.columns() ? src.columns() : dest.columns();
    
    for(size_t i=0;i<i_stop;i++)
        for(size_t j=0;j<j_stop;j++)
            dest(i,j) = src(i,j);
}

template<class ConceptMatrix1, class ConceptMatrix2>
inline bool matrix_equal(const ConceptMatrix1 &lhs, const ConceptMatrix2 &rhs)
{
    if(lhs.rows() != rhs.rows() || lhs.columns() != rhs.columns())
        return false;
        
    int i_stop = lhs.rows()
        ,j_stop = lhs.columns();
              
    for(size_t i=0;i<i_stop;i++)
        for(size_t j=0;j<j_stop;j++)
            if(lhs(i,j) != rhs(i,j))
                return false;
    return true;
}

template<class ConceptMatrix>
inline float_type matrix_determinant_1x1(const ConceptMatrix &m)
{
    return m(0,0);
}

template<class ConceptMatrix>
inline float_type matrix_determinant_2x2(const ConceptMatrix &m)
{
    return m(0,0) * m(1,1) - m(0,1) * m(1,0);
}

template<class ConceptMatrix>
inline float_type matrix_determinant_3x3(const ConceptMatrix &m)
{
    return  m(0,0) * (m(1,1)*m(2,2) - m(1,2) * m(2,1))
            + m(0,1) * (m(1,0)*m(2,2) - m(1,2) * m(2,0))
            + m(0,2) * (m(1,0)*m(2,1) - m(1,1)* m(2,0));
}

// concept: ConstMatrix
template<class ConceptMatrix>
class MatrixExcludeIterator {
    const ConceptMatrix *_m;
    size_t _row, _column;
    public:
    MatrixExcludeIterator(ConceptMatrix &__m, size_t __row, size_t __column)
    : _m(__m), _row(__row), _column(__column)
    { };
    
    size_t rows() const { return _m->rows() - 1; };
    size_t columns() const { return _m->columns() - 1; };
    
    float_ptype operator()(size_t row_index, size_t column_index) const
    {
        if(row_index >= _row)
            row_index++;
        if(column_index >= _column)
            column_index++; 
        return (*_m)(row_index, column_index); 
    };
};

template<class ConceptMatrix>
inline float_type matrix_determinant(const ConceptMatrix &m)
{
    // assumed rows == columns
    size_t i_stop = m.rows() < m.columns() ? m.rows() : m.columns();
    
    float_type retv;
    switch(m.rows())
    {
        case 1 :
            return matrix_determinant_1x1(m);            
        case 2 :
            return matrix_determinant_2x2(m);            
        case 3 :
            return matrix_determinant_3x3(m);            
        default:
            for(int i=0;i<i_stop;i++)
                retv += m(0,i) * matrix_determinant_(MatrixExcludeIterator<ConceptMatrix>(m, 0, i));
    }    
}

// Matrix + Matrix
template<class ConceptMatrix1, class ConceptMatrix2, class ConceptMatrix3>
inline void matrix_add(const ConceptMatrix1 &lhs,const ConceptMatrix2 &rhs, ConceptMatrix3 &dest)
{
    int i_stop = lhs.rows() < rhs.rows() ? lhs.rows() : rhs.rows(),
        j_stop = lhs.columns() < lhs.columns() ? lhs.columns() : rhs.columns();
        
    for(size_t i=0;i<i_stop;i++)
        for(size_t j=0;j<j_stop;j++)
            dest(i,j) = lhs(i,j) + rhs(i,j);
}

// Matrix - Matrix
template<class ConceptMatrix1, class ConceptMatrix2, class ConceptMatrix3>
inline void matrix_subtract(const ConceptMatrix1 &lhs,const ConceptMatrix2 &rhs, ConceptMatrix3 &dest)
{
    int i_stop = lhs.rows() < rhs.rows() ? lhs.rows() : rhs.rows(),
        j_stop = lhs.columns() < lhs.columns() ? lhs.columns() : rhs.columns();
        
    for(size_t i=0;i<i_stop;i++)
        for(size_t j=0;j<j_stop;j++)
            dest(i,j) = lhs(i,j) - rhs(i,j);
}

// Matrix * float_type
template<class ConceptMatrix1, class ConceptMatrix2>
inline void matrix_multiply(const ConceptMatrix1 &lhs, float_ptype rhs, ConceptMatrix2 &dest)
{
    int i_stop = lhs.rows(), j_stop = lhs.columns();
    for(size_t i=0;i<i_stop;i++)
        for(size_t j=0;j<j_stop;j++)
            dest(i,j) = lhs(i,j) * rhs;
}

// Matrix * Matrix
template<class ConceptMatrix1, class ConceptMatrix2, class ConceptMatrix3>
inline void matrix_multiply(const ConceptMatrix1 &lhs,const ConceptMatrix2 &rhs, ConceptMatrix3 &dest)
{
    size_t i_stop = lhs.rows()
            ,j_stop = rhs.columns()
                ,k_stop = lhs.columns() < rhs.rows() ? lhs.columns() : rhs.rows();
    
    if(!k_stop)
        return;
                        
    for(size_t i=0;i<i_stop;i++)
        for(size_t j=0;j<j_stop;j++)
    {
        dest(i,j) = lhs(i,0) * rhs(0,j);
        
        for(size_t k=1;k<k_stop;k++)
            dest(i,j) += lhs(i,k) * rhs(k,j);
    }
}

// output text dump of matrix content
template<class ConceptMatrix>
inline void matrix_dump(std::ostream &out, const ConceptMatrix &m)
{
    size_t i_stop = m.rows(), j_stop = m.columns();
    
    for(size_t i=0;i<i_stop;i++)
    {
        out << m(i,0);
        for(size_t j=1;j<j_stop;j++)
            out << '\t' << m(i,j);
        out << std::endl;
    }    
}

template<class Matrix1, class Matrix2>
inline void matrix_slice(Matrix1 &src, size_t row_begin, size_t row_end, size_t column_begin, size_t column_end, Matrix2 &dest, size_t dest_row = 0, size_t dest_column = 0)
{
    int i_stop = row_end < row_begin + dest.rows() ? row_end : row_begin + dest.rows() 
        ,j_stop = column_end < column_begin + dest.columns() ? column_end : column_begin + dest.columns();
    
    for(size_t i=row_begin,di=dest_row;i < i_stop;i++,di++)
        for(size_t j=column_begin,dj=dest_column;j < j_stop;j++,dj++)
            dest(di,dj) = src(i,j);
}

template<class Matrix1, class Matrix2>
inline void matrix_copy(Matrix1 &src, size_t row_begin, size_t row_end, size_t column_begin, size_t column_end, Matrix2 &dest, size_t dest_row = 0, size_t dest_column = 0)
{
    matrix_slice(src, row_begin, row_end, column_begin, column_end, dest, dest_row, dest_column);
}

template<class Matrix1, class Matrix2>
inline void matrix_copy(Matrix1 &src, Matrix2 &dest, size_t dest_row, size_t dest_column)
{
    matrix_slice(src, 0, src.rows(), 0, src.columns(), dest, dest_row, dest_column);
}

template<class ConceptMatrix1, class ConceptMatrix2>
inline void matrix_swap(ConceptMatrix1 &lhs, ConceptMatrix2 &rhs)
{
    float_type temp;
    
    int i_stop = lhs.rows() < rhs.rows() ? lhs.rows() : rhs.rows(),
        j_stop = lhs.columns() < lhs.columns() ? lhs.columns() : rhs.columns();
        
    if(&lhs(0,0) == &rhs(0,0))
        return;
    
    for(size_t i=0;i<i_stop;i++)
        for(size_t j=0;j<j_stop;j++)
        {
            temp = lhs(i,j);
            lhs(i,j) = rhs(i,j);
            rhs(i,j) = temp;
        }
        
}

} // namespace g_global

#endif
