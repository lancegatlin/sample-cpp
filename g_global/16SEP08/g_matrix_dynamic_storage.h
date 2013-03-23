#ifndef __G_MATRIX_DYNAMIC_STORAGE_H
#define __G_MATRIX_DYNAMIC_STORAGE_H

#include <cstring>
#include <limits>
#include <g_global/g_matrix_exception.h>

namespace g_global {
    
class MatrixDynamicStorage {
    public:
    typedef MatrixDynamicStorage this_t;
    
    private:
    float_type *m;
    size_t _rows, _columns;
    
    public:
    // Construct
    MatrixDynamicStorage() : m(NULL), _rows(0), _columns(0) { };
    
    ~MatrixDynamicStorage() { delete m; };

    // Accessors    
    size_t max_rows() const { return std::numeric_limits<size_t>::max(); };    
    size_t max_columns() const { return std::numeric_limits<size_t>::max(); };
    
    // concept: MatrixStorage
    void reserve(size_t rows, size_t columns)
    {
        if(!m)
            alloc(rows, columns);
        else realloc(rows, columns);
    }

    // concept : Matrix
    size_t rows() const { return _rows; };
    size_t columns() const { return _columns; };
    
        
    float_ptype operator()(size_t row_zero_based_index, size_t column_zero_based_index) const
    { 
        check_for_out_of_bounds(row_zero_based_index, column_zero_based_index);

        return m[columns() * row_zero_based_index + column_zero_based_index]; 
    };
    
    float_type &operator()(size_t row_zero_based_index, size_t column_zero_based_index)
    { 
        check_for_out_of_bounds(row_zero_based_index, column_zero_based_index);
        
        return m[columns() * row_zero_based_index + column_zero_based_index]; 
    };
    
    private:
    // Helpers
    void alloc(size_t rows, size_t columns)
    {
        _rows = rows;
        _columns = columns;
        
        m = new float_type[_rows * _columns];
    }
    
    void realloc(size_t rows, size_t columns)
    {
        if(_rows != rows || _columns != columns)
        {
            delete m;
            
            alloc(rows,columns);            
        }        
    }
    
    template<class ConceptMatrix>
    void copy(const ConceptMatrix &copy_me)
    { matrix_copy(copy_me,*this); }
    
    void check_for_out_of_bounds(size_t row_zero_based_index, size_t column_zero_based_index) const
    {
        if(row_zero_based_index >= rows() || column_zero_based_index >= columns())
            throw MatrixOutOfBounds();
    }
    
    void check_for_out_of_bounds(size_t row_zero_based_index, size_t column_zero_based_index)
    {
        if(row_zero_based_index >= rows() || column_zero_based_index >= columns())
        {
            grow(
                std::max(row_zero_based_index+1,rows())
                ,std::max(column_zero_based_index+1,columns())
            );  
        }
    }
    
    void grow(size_t rows, size_t columns)
    {
        // assumed: there is actually growing to be done, ergo: 
        // rows > _rows and columns > _columns
        
        this_t temp;
        
        temp.alloc(rows, columns);
        
        temp.copy(*this);
        
        temp.swap(*this);
    }
    
    void swap(this_t &t)
    {
        float_type *temp_m = m;
        size_t temp_rows = _rows, temp_columns = _columns;
        
        m = t.m;
        _rows = t._rows;
        _columns = t._columns;
        
        t.m = temp_m;
        t._rows = temp_rows;
        t._columns = temp_columns;
    }
    
};

} // namespace g_global

#endif
