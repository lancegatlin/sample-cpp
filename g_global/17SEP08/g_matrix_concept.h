#ifndef __MATRIX_CONCEPT_H
#define __MATRIX_CONCEPT_H

/*
concept MatrixRow {
    float_type &operator[](size_t index) const; // get a reference to an element within this row
}

concept MatrixConstRow {
    float_ptype operator[](size_t index) const; // get a copy of an element within this row
}

concept MatrixColumn {
    float_type &operator[](size_t index) const; // get a reference to an element within this column
}

concept MatrixConstColumn {
    float_ptype operator[](size_t index) const; // get a copy of an element within this column
}

concept ConstMatrix {
    size_t rows() const; // return the row size of the matrix
    size_t columns() const; // return the columnn size of the matrix
    
    float_ptype operator()(size_t row, size_t column) const; // get a copy of an element with the matrix    
}

concept Matrix : ConstMatrix {
    float_type &operator()(size_t row, size_t column); // get a reference to an element with the matrix
}

concept MatrixStorage : Matrix {
    MatrixStorage();
    
    void reserve(size_t rows, size_t columns);
}

*/

#endif
