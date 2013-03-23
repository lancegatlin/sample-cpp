#ifndef __G_MATRIX_ALGORITHM_H
#define __G_MATRIX_ALOGRITHM_H

/*
    Most generic form but not the most convenient
*/

namespace g_global {

template<class Matrix>
inline void matrix_fill(Matrix &m, float_ptype value)
{
    size_t i_stop = m.rows(),
            j_stop = m.columns();
            
    for(size_t i=0;i<i_stop;i++)
        for(size_t j=0;j<j_stop;j++)
            m[i][j] = value;
}

template<class Matrix>
inline void matrix_set_identity(Matrix &m)
{
    size_t i_stop = m.rows(),
            j_stop = m.columns();
            
    for(size_t i=0;i<i_stop;i++)
        for(size_t j=0;j<j_stop;j++)
            m[i][j] = (i == j ? 1 : 0);
}

template<class Matrix1, class Matrix2>
inline void matrix_copy(const Matrix1 &src, const Matrix2 &dest)
{
    size_t i_stop = src.rows() < dest.rows() ? src.rows() : dest.rows(),
            j_stop = src.columns() < dest.columns() ? src.columns() : dest.columns();
    
    for(size_t i=0;i<i_stop;i++)
        for(size_t j=0;j<j_stop;j++)
            dest[i][j] = src[i][j];
}

template<class Matrix1, class Matrix2>
inline bool matrix_equal(const Matrix1 &lhs, const Matrix2 &rhs)
{
    if(lhs.rows() != rhs.rows() || lhs.columns() != rhs.columns())
        return false;
        
//    int i_stop = lhs.rows() < rhs.rows() ? lhs.rows() : rhs.rows(),
//        j_stop = lhs.columns() < rhs.columns() ? lhs.columns() : rhs.columns();
    int i_stop = lhs.rows()
        ,j_stop = lhs.columns();
              
    for(size_t i=0;i<i_stop;i++)
        for(size_t j=0;j<j_stop;j++)
            if(lhs[i][j] != rhs[i][j])
                return false;
    return true;
}
/*
template<class Matrix1, class Matrix2>
inline void matrix_submatrix(Matrix1 &src, int xi, int xj, Matrix2 &dest)
{
    size_t i_stop = src.rows(),
            j_stop = src.columns();
            
    int ri=0,rj=0;
    for(int i=0;i<i_stop;i++)
    {
        if(i == xi)
            continue;
        
        for(int j=0;j<j_stop;j++)
        {
            if(j == xj)
                continue;
            dest[ri][rj] = src[i][j];
            rj++;
        }
        rj = 0;
        ri++;
    }
}
*/
template<class Matrix>
inline float_type matrix_determinant_1x1(const Matrix &m)
{
    return m[0][0];
}

template<class Matrix>
inline float_type matrix_determinant_2x2(const Matrix &m)
{
    return m[0][0] * m[1][1] - m[0][1] * m[1][0];
}

template<class Matrix>
inline float_type matrix_determinant_3x3(const Matrix &m)
{
    return  m[0][0] * (m[1][1]*m[2][2] - m[1][2] * m[2][1])
            + m[0][1] * (m[1][0]*m[2][2] - m[1][2] * m[2][0])
            + m[0][2] * (m[1][0]*m[2][1] - m[1][1]*m[2][0]);
}

template<class Matrix>
inline float_type matrix_determinant(const Matrix &m)
{
    // assumed rows == columns
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
            for(int i=0;i<m.rows();i++)
                retv += m[0][i] * matrix_determinant_(m.getSubMatrix(0,i));
    }    
}

// Matrix + Matrix
template<class Matrix1, class Matrix2, class Matrix3>
inline void matrix_add(const Matrix1 &lhs,const Matrix2 &rhs, Matrix3 &dest)
{
    int i_stop = lhs.rows() < rhs.rows() ? lhs.rows() : rhs.rows(),
        j_stop = lhs.columns() < lhs.columns() ? lhs.columns() : rhs.columns();
        
    for(size_t i=0;i<i_stop;i++)
        for(size_t j=0;j<j_stop;j++)
            dest[i][j] = lhs[i][j] + rhs[i][j];
}

// Matrix * float_type
template<class Matrix1, class Matrix2>
inline void matrix_multiply(const Matrix1 &lhs, float_ptype rhs, Matrix2 &dest)
{
    int i_stop = lhs.rows(), j_stop = lhs.columns();
    for(size_t i=0;i<i_stop;i++)
        for(size_t j=0;j<j_stop;j++)
            dest[i][j] = lhs[i][j] * rhs;
}

// Matrix * Matrix
template<class Matrix1, class Matrix2, class Matrix3>
inline void matrix_multiply(const Matrix1 &lhs,const Matrix2 &rhs, Matrix3 &dest)
{
    int i_stop = lhs.rows() < rhs.rows() ? lhs.rows() : rhs.rows()
        ,j_stop = lhs.columns() < lhs.columns() ? lhs.columns() : rhs.columns()
        ,k_stop = i_stop < j_stop ? i_stop : j_stop;

    for(size_t i=0;i<i_stop;i++)
        for(size_t j=0;j<j_stop;j++)
        {
            for(size_t k=0;k<k_stop;k++)
                dest[i][j] += lhs[i][k] * rhs[k][j];
        }
}

// output text dump of matrix content
template<class Matrix>
inline void matrix_dump(std::ostream &out, const Matrix &m)
{
    for(size_t c=0;c<m.columns();c++)
    {
        out << m[0][c];
        for(size_t r=1;r<m.rows();r++)
            out << ',' << m[r][c];
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
            dest[di][dj] = src[i][j];
}

template<class Matrix1, class Matrix2>
inline void matrix_copy(Matrix1 &src, size_t row_begin, size_t row_end, size_t column_begin, size_t column_end, Matrix2 &dest, size_t dest_row = 0, size_t dest_column = 0)
{
    matrix_slice(src, row_begin, row_end, column_begin, column_end, dest);
}

template<class Matrix1, class Matrix2>
inline void matrix_copy(Matrix1 &src, Matrix2 &dest, size_t dest_row, size_t dest_column)
{
    matrix_slice(src, 0, src.rows(), 0, src.columns(), dest, dest_row, dest_column);
}

template<class Matrix>
inline void matrix_swap_rows(Matrix &m, size_t row1, size_t row2)
{
    // save the number of columns
    size_t col_end = m.columns();
    
    // copy row1 off the matrix into a temp variable
    Matrix temp(m, row1, row1+1, 0, col_end);
    
    // copy row2 in the matrix to row1
    matrix_copy(m, row2, row2+1, 0, col_end, m, row1, 0);
    
    // copy temp to row2
    matrix_copy(temp, m, row2, 0); 
}

template<class Matrix>
inline void matrix_multiply_row(Matrix &m, size_t row, float_ptype alpha)
{
    size_t j_stop = m.columns();
    
    for(size_t j=0;j<j_stop;j++)
        m[row][j] *= alpha;
}


template<class Matrix1, class Matrix2, class Matrix3>
inline void matrix_add_rows(Matrix1 &lhs, size_t lhs_row, Matrix2 &rhs, size_t rhs_row, Matrix3 &dest, size_t dest_row)
{
    size_t j_stop = lhs.columns() < rhs.columns() ? lhs.columns() : rhs.columns();
    j_stop = j_stop < dest.columns() ? j_stop : dest.columns();
    
    for(size_t j=0;j<j_stop;j++)
        dest[dest_row][j] = lhs[dest_row][j] + rhs[dest_row][j];
}

/*
template<class Matrix>
inline void matrix_add_alpha_times_row_to_row(Matrix &m, size_t src_row, size_t dest_row, float_ptype alpha)
{
    Matrix temp(m, src_row, src_row+1, 0, m.columns);
    
    temp *= alpha;
    
    matrix_add_rows(temp, 0, m, dest_row, m, dest_row);
}
*/

} // namespace g_global

#endif
