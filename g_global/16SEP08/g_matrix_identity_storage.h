#ifndef __G_MATRIX_IDENTITY_STORAGE_H
#define __G_MATRIX_IDENTITY_STORAGE_H

namespace g_global {

class MatrixIdentityStorage {
    public:
    typedef MatrixIdentityStorage this_t;
    typedef MatrixIdentityStorage submatrix_t;
    
    struct construct_parameters_t { };
        
    // Constructors
    MatrixIdentityStorage() { };

    // Accessors
    size_t rows() const { return max_rows(); };
    size_t columns() const { return max_columns(); };
    
    size_t max_rows() const { return std::numeric_limits<size_t>::max(); };    
    size_t max_columns() const { return std::numeric_limits<size_t>::max(); };

    float_ptype at(size_t row_zero_based_index, size_t column_zero_based_index) const
    {
        static float_type one = 1.0, zero = 0.0;
        
        if(row_zero_based_index == column_zero_based_index)
            return one;
        return zero;
    };

};

} // namespace g_global

#endif
