#ifndef __G_MATRIX_H
#define __G_MATRIX_H

#include <algorithm>
#include <iostream>
#include <g_global/g_global.h>
#include <g_global/g_column_vector.h>

/*
    File: g_matrix.h
    Author: lance.gatlin@yahoo.com
    Date: 01 Aug 2008
    Version: 1

    Overview: 
        1) Declares and implements template class AnyMatrix. AnyMatrix 
        encapsulates a matrix of float_types. Provides:
            a) Default and copy constructors
            b) Access to internal matrix array by way of operator []
            c) Functions for filling or setting the values of the 
            matrix
            d) Assignment (assign, operator =)
            e) Equality (equal, operator ==)
            f) Function getDeterminant
        2) Declares math operators for Matrix<->Matrix[+,*], 
        Matrix<->float_type[*], AnyColumnVector<->Matrix[*]
        3) Declares AnyIdentityMatrix that is derived from AnyMatrix. On 
        construction automatically sets matrix to identity
        
*/

namespace g_global {

template<int ROWS, int COLUMNS>
class AnyMatrix {
    protected:
//    AnyColumnVector<COLUMNS> m[ROWS];
    float_type m[ROWS][COLUMNS];
    
    public:
    typedef AnyMatrix<ROWS,COLUMNS> this_t;
    typedef AnyMatrix<ROWS-1,COLUMNS-1> submatrix_t;

    AnyMatrix() { zero(); };
    
    template<int R,int C>
    AnyMatrix(const AnyMatrix<R,C> &copy_me)
    { *this = copy_me; };
    
    // No bounds checking
    const float_type *operator [](int zero_based_index) const
    { return at(zero_based_index); };
    float_type *operator [](int zero_based_index)
    { return at(zero_based_index); };
    const float_type *at(int zero_based_index) const
    { return m[zero_based_index]; };
    float_type *at(int zero_based_index)
    { return m[zero_based_index]; };
/*    const AnyColumnVector<COLUMNS> &operator [](int zero_based_index) const
    { return m[zero_based_index]; };
    AnyColumnVector<COLUMNS> &operator [](int zero_based_index)
    { return m[zero_based_index]; };*/
    
    void zero() { fill(0.0); };
    void fill(float_ptype value) 
    {
        for(int i=0;i<ROWS;i++)
            for(int j=0;j<COLUMNS;j++)
                m[i][j] = value;
    };
    
    void setIdentity()
    {
        fill(0);
        int k_stop = std::min(ROWS,COLUMNS);
        for(int k=0;k<k_stop;k++)
            m[k][k] = 1.0;
    }
    
    template<int R, int C>
    this_t &operator =(const AnyMatrix<R,C> &copy_me)
    { assign(copy_me); return *this; };
    
    template<int R, int C>
    void assign(const AnyMatrix<R,C> &copy_me) const
    {
        int i_stop = std::min(ROWS,R), j_stop = std::min(COLUMNS,C);
        for(int i=0;i<i_stop;i++)
            for(int j=0;j<j_stop;j++)
                m[i][j] = copy_me.m[i][j];
    }
    
    
    template<int R, int C>
    bool operator ==(const AnyMatrix<R,C> &rhs) const
    { return equal(rhs); };
    template<int R, int C>
    bool equal(const AnyMatrix<R,C> &rhs) const
    {
        int i_stop = std::min(ROWS,R), j_stop = std::min(COLUMNS,C);
        for(int i=0;i<i_stop;i++)
            for(int j=0;j<j_stop;j++)
                if(m[i][j] != rhs.m[i][j])
                    return false;
        return true;
    }
        
    submatrix_t getSubMatrix(int xi,int xj) const
    {
        submatrix_t retv;
        int ri=0,rj=0;
        for(int i=0;i<ROWS;i++)
        {
            if(i == xi)
                continue;
            
            for(int j=0;j<COLUMNS;j++)
            {
                if(j == xj)
                    continue;
                retv[ri][rj] = m[i][j];
                rj++;
            }
            rj = 0;
            ri++;
        }
    }
    
    float_type getDeterminant() const;
};

inline float_type _getDeterminant(const AnyMatrix<1,1> &m)
{
    return m[0][0];
}

inline float_type _getDeterminant(const AnyMatrix<2,2> &m)
{
    return m[0][0] * m[1][1] - m[0][1] * m[1][0];
}

inline float_type _getDeterminant(const AnyMatrix<3,3> &m)
{
    return  m[0][0] * (m[1][1]*m[2][2] - m[1][2] * m[2][1])
            + m[0][1] * (m[1][0]*m[2][2] - m[1][2] * m[2][0])
            + m[0][2] * (m[1][0]*m[2][1] - m[1][1]*m[2][0]);
}

template<int S>
inline float_type _getDeterminant(const AnyMatrix<S,S> &m)
{
    float_type retv;
    for(int i=0;i<S;i++)
        retv += m[0][i] * getDeterminant(m.getSubMatrix(0,i));
}

template<int R,int C>
inline float_type AnyMatrix<R,C>::getDeterminant() const
{ return _getDeterminant(*this); };

// Matrix + Matrix
template<int R1,int C1, int R2, int C2>
AnyMatrix<R1,C1> operator +(const AnyMatrix<R1,C1> &lhs,const AnyMatrix<R2,C2> &rhs)
{
    AnyMatrix<R1,C1> retv;
    int i_stop = std::min(R1,R2), j_stop = std::min(C1,C2);
    for(int i=0;i<i_stop;i++)
        for(int j=0;j<j_stop;j++)
            retv[i][j] = lhs[i][j] + rhs[i][j];
    
    return retv;
}

// Matrix += Matrix
template<int R1,int C1, int R2, int C2>
AnyMatrix<R1,C1> &operator +=(AnyMatrix<R1,C1> &lhs,const AnyMatrix<R2,C2> &rhs)
{
    lhs = lhs + rhs;
    return lhs;
}

// Matrix * float_type
template<int R1,int C1>
AnyMatrix<R1,C1> operator *(const AnyMatrix<R1,C1> &lhs,float_ptype rhs)
{
    AnyMatrix<R1,C1> retv;
    int i_stop = R1, j_stop = C1;
    for(int i=0;i<i_stop;i++)
        for(int j=0;j<j_stop;j++)
            retv[i][j] = lhs[i][j] * rhs;
    return retv;
}

// Matrix *= float_type
template<int R1,int C1>
AnyMatrix<R1,C1> &operator *=(AnyMatrix<R1,C1> &lhs,float_ptype rhs)
{
    lhs = lhs * rhs;
    return lhs;
}

// Matrix * Matrix
template<int R1,int C1, int R2, int C2>
AnyMatrix<R1,C1> operator *(const AnyMatrix<R1,C1> &lhs,const AnyMatrix<R2,C2> &rhs)
{
    AnyMatrix<R1,C1> retv;
    int i_stop = std::min(R1,R2), j_stop = std::min(C1,C2), k_stop = std::min(i_stop,j_stop);
    for(int i=0;i<i_stop;i++)
        for(int j=0;j<j_stop;j++)
        {
            for(int k=0;k<k_stop;k++)
                retv[i][j] += lhs[i][k] * rhs[k][j];
        }
    return retv;
}

// Matrix *= Matrix
template<int R1,int C1, int R2, int C2>
AnyMatrix<R1,C1> &operator *=(const AnyMatrix<R1,C1> &lhs,const AnyMatrix<R2,C2> &rhs)
{
    lhs = lhs * rhs;
    return lhs;
}

// ColumnVector * Matrix
// Multiply column vector times a matrix
template<int C1, int R1,int C2>
AnyColumnVector<C1> operator *(const AnyColumnVector<C1> &lhs, const AnyMatrix<R1,C2> &rhs)
{
    AnyColumnVector<C1> retv;
    int i_stop = R1, j_stop = std::min(C1,C2);
    for(int i=0;i<i_stop;i++)
        for(int j=0;j<j_stop;j++)
                retv[i] += lhs[j] * rhs[i][j];
    return retv;
}
// ColumnVector *= Matrix
// Multiply column vector times a matrix
template<int C1, int R1,int C2>
AnyColumnVector<C1> &operator *=(AnyColumnVector<C1> &lhs, const AnyMatrix<R1,C2> &rhs)
{
    lhs = lhs * rhs;
    return lhs;
}

// Identity Matrix
template<int R,int C>
class AnyIdentityMatrix : public AnyMatrix<R,C> {
    typedef AnyMatrix<R,C> parent_t;
    public:
    AnyIdentityMatrix() { parent_t::setIdentity(); };
};

// output text dump of matrix content
template<int R, int C>
std::ostream &operator <<(std::ostream &out, const AnyMatrix<R,C> &m)
{
    for(int c=0;c<C;c++)
    {
        out << m[0][c];
        for(int r=1;r<R;r++)
            out << ',' << m[r][c];
        out << std::endl;
    }    
    return out;
}

} // namespace g_global

#endif
