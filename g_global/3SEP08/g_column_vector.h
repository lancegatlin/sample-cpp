#ifndef __G_COLUMN_VECTOR_H
#define __G_COLUMN_VECTOR_H

#include <algorithm>
#include <g_global/g_global.h>


/*
    File: g_column_vector.h
    Author: lance.gatlin@yahoo.com
    Date: 01 Aug 2008
    Version: 1
    
    Overview: 
        1) Declares template class AnyColumnVector that contains an array of
        float_types. Provides:
            a) Default and copy contructors
            b) Access to internal array provided with operator []
            c) Functions to fill or zero the array
            d) Assignment (assign, operator =)
            e) Equality (equal, operator ==)
*/

namespace g_global {

template<int ROWS>
class AnyColumnVector {
    float_type d[ROWS];
    
    typedef AnyColumnVector<ROWS> this_t;
    public:
    AnyColumnVector() { zero(); };
    
    template<int R>
    AnyColumnVector(const AnyColumnVector<R> &copy_me)
    { *this = copy_me; }
    
    float_ptype operator[](int zero_based_index) const
    { return d[zero_based_index]; };
    float_type &operator[](int zero_based_index)
    { return d[zero_based_index]; };
    
    void zero() { fill(0.0); };
    void fill(float_ptype value)
    {
        for(int i=0;i<ROWS;i++)
            d[i] = value;
    }
    
    template<int R>
    this_t &operator =(const AnyColumnVector<R> &copy_me)
    { assign(copy_me); return *this; };
    
    template<int R>
    void assign(const AnyColumnVector<R> &copy_me)
    {
        int i_stop = std::min(ROWS,R);
        for(int i=0;i<i_stop;i++)
            d[i] = copy_me.d[i];
    }
    
    template<int R>
    bool operator ==(const AnyColumnVector<R> &rhs) const
    { return equal(rhs); return *this; };
    
    template<int R>
    bool equal(const AnyColumnVector<R> &rhs) const
    {
        int i_stop = std::min(ROWS, R);
        for(int i=0;i<i_stop;i++)
            if(d[i] != rhs.d[i])
                return false;
        return true;
    }
    
};

} // namespace g_global

#endif
