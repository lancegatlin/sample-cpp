#ifndef __G_MATRIX_SUBMATRIX_STORAGE_H
#define __G_MATRIX_SUBMATRIX_STORAGE_H

#include <g_global/g_global.h>

namespace g_global {
    
template<class Matrix>
class MatrixSubMatrixStorage {
    protected:
    typedef MatrixSubMatrixStorage<Matrix> this_t;
    
    const Matrix *m;
    size_t xi, xj;
    
    struct construct_parameters_t { 
        const Matrix &m;
        size_t xi, xj;
        construct_parameters_t(const Matrix &_m, size_t _xi, size_t _xj)
        : m(_m), xi(_xi), xj(_xj) { };
    };
    static construct_parameters_t construct(const Matrix &m, size_t xi, size_t xj)
    { return construct_parmeters_t(m,xi,xj); };
    
    // Constructors
    MatrixSubMatrixStorage() : m(0) { };
    MatrixSubMatrixStorage(construct_parameters_t p)
    : m(&p.m), xi(p.xi), xj(p.xj) 
    { };
    
    // Accessors
    size_t rows() const { return m ? m->rows()-1 : 0; };
    size_t columns() const { return m ? m->columns()-1 : 0; };
    
    size_t max_rows() const { return rows(); };
    size_t max_columns() const { return columns(); };

    // no bounds checking, pointed to matrix should check bounds
    float_ptype at(size_t row_zero_based_index, size_t column_zero_based_index) const
    { 
        if(!m)
            return 0;
        
        // adjust the indexing so that if it refers to anything 
        // past the submatrix selection then increase the index
        // Ex Matrix:
        // * * * * *
        // * 1 2 3 *
        // * 4 5 6 *
        // * 7 8 9 *
        // * * * * *
        // xi=1,xj=1
        // Submatrix indexes:
        // (0,0) = 1 
        // (0,1) = 3 (refers to 2, but this is past col selection so use (0,2) )
        // (1,0) = 7 
        // (1,1) = 9 (refers to 5 but this is past row & col selection so use (2,2) )
        // xi=0,xj=1
        // Submatrix indexes:
        // (0,0) = 4 (refers to 1, but this is past row selection so use (1,0) )
        // (0,1) = 6 (refers to 2, but this is past row & col selection so use (1,2) )
        // (1,0) = 7 (refers to 4, but this is past row selection so use (2,0)
        // (1,1) = 9 (refers to 5, but this is past row & col selection so use (2,2) )
        
        if(row_zero_based_index >= xi)
            row_zero_based_index++;
            
        if(column_zero_based_index >= xi)
            column_zero_based_index++;
        
        return m->at(row_zero_based_index, column_zero_based_index);
    };
   
    // Access to writing to the matrix marked private to generate compile
    // time errors
    private:
    float_type &at(size_t row_zero_based_index, size_t column_zero_based_index);
};

} // namespace g_global

#endif
