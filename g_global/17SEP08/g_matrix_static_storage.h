#ifndef __G_MATRIX_STATIC_STORAGE_H
#define __G_MATRIX_STATIC_STORAGE_H

namespace g_global {

template<unsigned long ROWS, unsigned long COLUMNS>
class MatrixStaticStorage {
    public:
    typedef MatrixStaticStorage<ROWS,COLUMNS> this_t;
    
    private:
    float_type m[ROWS][COLUMNS];
    
    public:
    // Constructors
    MatrixStaticStorage() { };
    
    // Accessors
    size_t max_rows() const { return ROWS; };    
    size_t max_columns() const { return COLUMNS; };
    
    // concept: MatrixStorage
    void reserve(size_t rows, size_t columns)
    {
        if(rows > ROWS || columns > COLUMNS)
            throw MatrixReserveFail();
    }
    
    // concept: Matrix
    size_t rows() const { return ROWS; };
    size_t columns() const { return COLUMNS; };
    
    float_ptype operator()(size_t row_zero_based_index, size_t column_zero_based_index) const
    {
        check_for_out_of_bounds(row_zero_based_index, column_zero_based_index);
        
        return m[row_zero_based_index][column_zero_based_index]; 
    };
   
    float_type &operator()(size_t row_zero_based_index, size_t column_zero_based_index)
    { 
        check_for_out_of_bounds(row_zero_based_index, column_zero_based_index);
        
        return m[row_zero_based_index][column_zero_based_index]; 
    };
    
    private:
    void check_for_out_of_bounds(size_t row_zero_based_index, size_t column_zero_based_index) const
    {
        if(row_zero_based_index >= rows() || column_zero_based_index >= columns())
            throw MatrixOutOfBounds();
    }
};

} // namespace g_global

#endif
