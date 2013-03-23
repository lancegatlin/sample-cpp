#ifndef __G_MATRIX_STATIC_STORAGE_H
#define __G_MATRIX_STATIC_STORAGE_H

namespace g_global {

template<unsigned long ROWS, unsigned long COLUMNS>
class MatrixStaticStorage {
    public:
    typedef MatrixStaticStorage<ROWS,COLUMNS> this_t;
    typedef MatrixStaticStorage<ROWS-1,COLUMNS-1> submatrix_t;
    
    class construct_parameters_t { };
    
    private:
    float_type m[ROWS][COLUMNS];
    
    public:
    // Constructors
    MatrixStaticStorage() { };
    MatrixStaticStorage(construct_parameters_t) { };

    template<class AnyMatrix>
    MatrixStaticStorage(const AnyMatrix &m)
    { assign(m); }
    
    // Accessors
    size_t rows() const { return ROWS; };
    size_t columns() const { return COLUMNS; };
    
    size_t max_rows() const { return ROWS; };    
    size_t max_columns() const { return COLUMNS; };

    float_ptype at(size_t row_zero_based_index, size_t column_zero_based_index) const
    {
        check_for_out_of_bounds(row_zero_based_index, column_zero_based_index);
        
        return m[row_zero_based_index][column_zero_based_index]; 
    };
   
    float_type &at(size_t row_zero_based_index, size_t column_zero_based_index)
    { 
        check_for_out_of_bounds(row_zero_based_index, column_zero_based_index);
        
        return m[row_zero_based_index][column_zero_based_index]; 
    };
    
    template<class AnyMatrix>
    this_t &operator =(const AnyMatrix &assign_me)
    { assign(assign_me); return *this; };
    
    template<class AnyMatrix>
    void assign(const AnyMatrix &assign_me)
    {
        matrix_copy(assign_me, *this);
    }
    
    private:
    void check_for_out_of_bounds(size_t row_zero_based_index, size_t column_zero_based_index) const
    {
        if(row_zero_based_index >= rows() || column_zero_based_index >= columns())
            throw MatrixOutOfBounds();
    }
};

} // namespace g_global

#endif
