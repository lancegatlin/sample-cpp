#ifndef __G_MATRIX_DYNAMIC_STORAGE_H
#define __G_MATRIX_DYNAMIC_STORAGE_H

#include <cstring>
#include <limits>
#include <g_global/g_matrix_exception.h>

namespace g_global {
    
class MatrixDynamicStorage {
    public:
    typedef MatrixDynamicStorage this_t;
    typedef MatrixDynamicStorage submatrix_t;
    
    struct construct_parameters_t { 
        size_t rows, columns; 
        
        construct_parameters_t(size_t _rows, size_t _columns)
        : rows(_rows), columns(_columns) { };
    };
    
    static construct_parameters_t construct(size_t rows, size_t columns)
    { return construct_parameters_t(rows,columns); };
        
    private:
    float_type *m;
    size_t _rows, _columns;
    
    public:
    // Construct
    MatrixDynamicStorage() : m(NULL), _rows(0), _columns(0) { };
    
    MatrixDynamicStorage(construct_parameters_t p)
    : m(NULL), _rows(0), _columns(0)
    { 
        alloc(p.rows, p.columns);
    };

    template<class AnyMatrix>
    MatrixDynamicStorage(const AnyMatrix &copy_me)
    : m(NULL), _rows(0), _columns(0)
    {
        alloc(copy_me.rows(), copy_me.columns());
        copy_same_size(copy_me);
    }
    
    ~MatrixDynamicStorage() { delete m; };

    // Accessors    
    size_t rows() const { return _rows; };
    size_t columns() const { return _columns; };
    
    size_t max_rows() const { return std::numeric_limits<size_t>::max(); };    
    size_t max_columns() const { return std::numeric_limits<size_t>::max(); };
    
    // no bounds checking    
    // Todo: Add auto reallocation if bounds exceeded
    float_ptype at(size_t row_zero_based_index, size_t column_zero_based_index) const
    { 
        check_for_out_of_bounds(row_zero_based_index, column_zero_based_index);

        return m[row_zero_based_index + rows() * column_zero_based_index]; 
    };
    
    float_type &at(size_t row_zero_based_index, size_t column_zero_based_index)
    { 
        check_for_out_of_bounds(row_zero_based_index, column_zero_based_index);
        
        return m[row_zero_based_index + rows() * column_zero_based_index]; 
    };
    
    // assignment
    // note: this does not actually copy the elements, only reserves space for them
    template<class AnyMatrix>
    this_t & operator =(const AnyMatrix &assign_me)
    { assign(assign_me); return *this; }
    
    template<class AnyMatrix>
    void assign(const AnyMatrix &assign_me)
    {
        if(this == &assign_me)
            return *this;
        
        realloc(assign_me.rows(), assign_me.columns());
        copy_same_size(assign_me);
        
        return *this;
    }
    
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
    
    template<class AnyMatrix &m>
    void copy(const AnyMatrix &copy_me)
    { matrix_copy(copy_me,*this); }
    
    void copy(const this_t &copy_me)
    {
        // assumed: enough room in this for copy_me
        memcpy(m, copy_me.m, rows() * columns() * sizeof(float_type));
    }

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
                std::max(row_zero_based_index,rows())
                ,std::max(column_zero_based_index,columns())
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
