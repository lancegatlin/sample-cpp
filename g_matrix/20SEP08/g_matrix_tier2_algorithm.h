#ifndef __G_MATRIX_TIER1_ALGORITHM_H
#define __G_MATRIX_TIER1_ALGORITHM_H

/*
    File: g_matrix_tier2_algorithm.h
    Author: lance.gatlin@yahoo.com
    Date: 19 Sep 2008
    Version: 1

    Overview: 
	1) Declares and implements the following matrix functions:
		matrix_fill
		matrix_set_identity
		matrix_column_merge
		matrix_copy
		matrix_equal
		matrix_add
		matrix_subtract
		matrix_multiply
		matrix_dump
		matrix_swap
		matrix_max
		matrix_min
        
*/

namespace g_matrix {

/*
	Fills a matrix with a float_type
*/
template<typename T>
inline void matrix_fill(T &_m, float_ptype value)
{
    MatrixConcept<T> m(_m);
    
    size_t i_stop = m.rows(),
            j_stop = m.columns();
            
    for(size_t i=0;i<i_stop;i++)
        for(size_t j=0;j<j_stop;j++)
            m(i,j) = value;
}

/*
	Sets a matrix to the identity matrix
*/
template<typename T>
inline void matrix_set_identity(T &_m)
{
    MatrixConcept<T> m(_m);

    size_t i_stop = m.rows(),
            j_stop = m.columns();
            
    for(size_t i=0;i<i_stop;i++)
        for(size_t j=0;j<j_stop;j++)
            m(i,j) = (i == j ? 1 : 0);
}

/*
	Merges two matrixes SRC and DEST such that [DEST|SRC]
*/
template<typename T1, class T2>
inline void matrix_column_merge(const T1 &_src, T2 &_dest)
{
    MatrixConcept<const T1> src(_src);
    MatrixConcept<T2> dest(_dest);

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

/*
	Sets matrix dest = src
*/
template<typename T1, class T2>
inline void matrix_copy(const T1 &_src, T2 &_dest)
{
    MatrixConcept<const T1> src(_src);
    MatrixConcept<T2> dest(_dest);

    size_t i_stop = src.rows() < dest.rows() ? src.rows() : dest.rows(),
            j_stop = src.columns() < dest.columns() ? src.columns() : dest.columns();
    
    for(size_t i=0;i<i_stop;i++)
        for(size_t j=0;j<j_stop;j++)
            dest(i,j) = src(i,j);
}

/*
	Return true if matrix lhs == rhs
*/
template<typename T1, class T2>
inline bool matrix_equal(const T1 &_lhs, const T2 &_rhs)
{
    MatrixConcept<const T1> lhs(_lhs);
    MatrixConcept<const T2> rhs(_rhs);

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

/*
	Adds matrix lhs and rhs and places the result in dest
*/
// Matrix + Matrix
template<typename T1, class T2, class T3>
inline void matrix_add(const T1 &_lhs,const T2 &_rhs, T3 &_dest)
{
    MatrixConcept<const T1> lhs(_lhs);
    MatrixConcept<const T2> rhs(_rhs);
    MatrixConcept<T3> dest(_dest);

    int i_stop = lhs.rows() < rhs.rows() ? lhs.rows() : rhs.rows(),
        j_stop = lhs.columns() < lhs.columns() ? lhs.columns() : rhs.columns();
        
    for(size_t i=0;i<i_stop;i++)
        for(size_t j=0;j<j_stop;j++)
            dest(i,j) = lhs(i,j) + rhs(i,j);
}

/*
	Subtracts matrix rhs from lhs and places the result in dest
*/
// Matrix - Matrix
template<typename T1, class T2, class T3>
inline void matrix_subtract(const T1 &_lhs,const T2 &_rhs, T3 &_dest)
{
    MatrixConcept<const T1> lhs(_lhs);
    MatrixConcept<const T2> rhs(_rhs);
    MatrixConcept<T3> dest(_dest);

    int i_stop = lhs.rows() < rhs.rows() ? lhs.rows() : rhs.rows(),
        j_stop = lhs.columns() < lhs.columns() ? lhs.columns() : rhs.columns();
        
    for(size_t i=0;i<i_stop;i++)
        for(size_t j=0;j<j_stop;j++)
            dest(i,j) = lhs(i,j) - rhs(i,j);
}

/*
	Multiplies matrix lhs by a scalar float_type and places the result in dest
*/
// Matrix * float_type
template<typename T1, class T2>
inline void matrix_multiply(const T1 &_lhs, float_ptype rhs, T2 &_dest)
{
    MatrixConcept<const T1> lhs(_lhs);
    MatrixConcept<T2> dest(_dest);

    int i_stop = lhs.rows(), j_stop = lhs.columns();
    for(size_t i=0;i<i_stop;i++)
        for(size_t j=0;j<j_stop;j++)
            dest(i,j) = lhs(i,j) * rhs;
}

/*
	Multiplies matrix lhs by matrix rhs and places the result in dest
	
	assumed &dest != &lhs OR &dest != &rhs
*/
// Matrix * Matrix
template<typename T1, class T2, class T3>
inline void matrix_multiply(const T1 &_lhs,const T2 &_rhs, T3 &_dest)
{
    MatrixConcept<const T1> lhs(_lhs);
    MatrixConcept<const T2> rhs(_rhs);
    MatrixConcept<T3> dest(_dest);

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

/*
	Displays a tab separated matrix to stream
*/
// output text dump of matrix content
template<typename T>
inline std::ostream & matrix_dump(std::ostream &out, const T &_m)
{
    MatrixConcept<const T> m(_m);

    size_t i_stop = m.rows(), j_stop = m.columns();
    
    for(size_t i=0;i<i_stop;i++)
    {
        out << m(i,0);
        for(size_t j=1;j<j_stop;j++)
            out << '\t' << m(i,j);
        out << std::endl;
    }    
    return out;
}

/*
	Take a section of a matrix specified by two points and copy it into a dest matrix 
*/
/*
template<typename T1, class T2>
inline void matrix_slice(const T1 &_src, size_t row_begin, size_t column_begin, size_t row_end, size_t column_end, T2 &_dest, size_t dest_row = 0, size_t dest_column = 0)
{
    MatrixConcept<const T1> src(_src);
    MatrixConcept<T2> dest(_dest);

    int i_stop = row_end < row_begin + dest.rows() ? row_end : row_begin + dest.rows() 
        ,j_stop = column_end < column_begin + dest.columns() ? column_end : column_begin + dest.columns();
    
    for(size_t i=row_begin,di=dest_row;i < i_stop;i++,di++)
        for(size_t j=column_begin,dj=dest_column;j < j_stop;j++,dj++)
            dest(di,dj) = src(i,j);
}


template<typename T1, class T2>
inline void matrix_copy(const T1 &_src, size_t row_begin, size_t row_end, size_t column_begin, size_t column_end, T2 &_dest, size_t dest_row = 0, size_t dest_column = 0)
{
    MatrixConcept<const T1> src(_src);
    MatrixConcept<T2> dest(_dest);

    matrix_slice(src, row_begin, row_end, column_begin, column_end, dest, dest_row, dest_column);
}

template<typename T1, class T2>
inline void matrix_copy(const T1 &_src, T2 &_dest, size_t dest_row, size_t dest_column)
{
    MatrixConcept<const T1> src(_src);
    MatrixConcept<T2> dest(_dest);

    matrix_slice(src, 0, src.rows(), 0, src.columns(), dest, dest_row, dest_column);
}
*/

/*
	Swaps the values of lhs and rhs
*/
template<typename T1, class T2>
inline void matrix_swap(T1 &_lhs, T2 &_rhs)
{
    MatrixConcept<T1> lhs(_lhs);
    MatrixConcept<T2> rhs(_rhs);

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

/*
	Finds the maximum value in a matrix and returns the row,column location and the value
*/
template<typename T>
inline void matrix_max(const T &_m, size_t &row, size_t &column, float_type &max)
{
    MatrixConcept<const T> m(_m);
    
    int i_stop = m.rows()
        ,j_stop = m.columns();
        
	row = column = 0;
	max = m(0,0);

    for(size_t i=0;i<i_stop;i++)
        for(size_t j=0;j<j_stop;j++)
            if(max < m(i,j))
			{
				row = i;
				column = j;
				max = m(i,j);
			}
}

/*
	Finds the minimum value in a matrix and returns the row,column location and the value
*/
template<typename T>
inline void matrix_min(const T &_m, size_t &row, size_t &column, float_type &min)
{
    MatrixConcept<const T> m(_m);
    
    int i_stop = m.rows()
        ,j_stop = m.columns();
        
	row = column = 0;
	min = m(0,0);

    for(size_t i=0;i<i_stop;i++)
        for(size_t j=0;j<j_stop;j++)
            if(m(i,j) < min)
			{
				row = i;
				column = j;
				min = m(i,j);
			}
}


} // namespace g_matrix

#endif
