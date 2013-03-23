#ifndef __G_MATRIX_CLASS_MATRIXSTATICSTORAGE_H
#define __G_MATRIX_CLASS_MATRIXSTATICSTORAGE_H

/*
    File: g_matrix_tier3_class_MatrixStaticStorage.h
    Author: lance.gatlin@yahoo.com
    Date: 19 Sep 2008
    Version: 1

    Overview: 
	1) Declares and implements MatrixStaticStorage
*/

namespace g_matrix {

template<unsigned long ROWS, unsigned long COLUMNS>
class MatrixStaticStorage {
    public:
    typedef MatrixStaticStorage<ROWS,COLUMNS> this_t;
    
    private:
    float_type m[ROWS][COLUMNS];
    
    public:
    // Constructors
    MatrixStaticStorage() { };
    
	// default destructor

	MatrixStaticStorage(const this_t &copy_me)
	{ matrix_copy(copy_me, *this); }

	this_t &operator =(const this_t &assign_me)
	{ matrix_copy(assign_me, *this); return *this; }

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

} // namespace g_matrix

#endif
