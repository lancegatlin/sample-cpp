/*
    File: g_matrix_tier3_class_MatrixAdaptorStorage.h
    Author: lance.gatlin@yahoo.com
    Date: 19 Sep 2008
    Version: 1

    Overview: 
	1) Declares and implements class MatrixAdaptorStorage
*/

template<class ConceptMatrix>    
class MatrixAdaptorStorage {
    public:
    typedef MatrixAdaptorStorage<ConceptMatrix> this_t;
    
    private:
    ConceptMatrix m;
    
    public:
    // Constructors
    MatrixAdaptorStorage() { };

    // default copy constructor
	// default assignment
	// default destructor

    // Accessors
    size_t max_rows() const { return m.rows(); };    
    size_t max_columns() const { return m.columns(); };
    ConceptMatrix matrix() const { return m; };
    
    // assignment
    void matrix(ConceptMatrix _m) { m = _m; };
    
    // concept: MatrixStorage
    void reserve(size_t _rows, size_t _columns)
    {
        if(_rows > rows() || _columns > columns())
            throw MatrixReserveFail();
    }
    
    // concept: Matrix
    size_t rows() const { return m.rows(); };
    size_t columns() const { return m.columns(); };
    
    float_ptype operator()(size_t row_zero_based_index, size_t column_zero_based_index) const
    {
        check_for_out_of_bounds(row_zero_based_index, column_zero_based_index);
        
        return m(row_zero_based_index,column_zero_based_index); 
    };
   
    float_type &operator()(size_t row_zero_based_index, size_t column_zero_based_index)
    { 
        check_for_out_of_bounds(row_zero_based_index, column_zero_based_index);
        
        return m(row_zero_based_index,column_zero_based_index); 
    };
    
    private:
    void check_for_out_of_bounds(size_t row_zero_based_index, size_t column_zero_based_index) const
    {
        if(row_zero_based_index >= rows() || column_zero_based_index >= columns())
            throw MatrixOutOfBounds();
    }
};
