#ifndef __G_MATRIX_TIER1_MATRIXCONCEPT_H
#define __G_MATRIX_TIER1_MATRIXCONCEPT_H

/*

// ************************ Tier 1 ************************ 

// Minimum interface required to be considered a matrix
concept ConstMatrix {
	size_t rows() const; // return the row size of the matrix
	size_t columns() const; // return the columnn size of the matrix

	float_ptype operator()(size_t row, size_t column) const; // get a copy of an element with the matrix    
}

concept Matrix : ConstMatrix {
	float_type &operator()(size_t row, size_t column); // get a reference to an element with the matrix
}

// ************************ Tier 2 ************************ 

concept MatrixIterator : Matrix, forward_iterator {
}

concept MatrixConstIterator : ConstMatrix, forward_iterator {
}

// ************************ Tier 3 ************************ 

// Matrix objects that utilize algorithm tier 2
concept ConstMatrix2 : ConstMatrix {
	MatrixConstIterator begin() const;
	MatrixConstIterator end() const;
	MatrixIterator begin();
	MatrixIterator end();

	template<typename T>
	bool operator ==(const T &rhs) const;
}

concept Matrix2 : ConstMatrix2, Matrix {
	template<typename T>
	this_t &operator =(const T &); // assign to this row a matrix

	template<typename T>
	void swap(T &m)  // swap a this row with a matrix
}

// Row of a matrix
concept MatrixConstRow : ConstMatrix2 {
	this_t(const this_t &);
	this_t &operator =(const this_t &);
	void swap(this_t &m)	
	~this_t();

	float_ptype operator[](size_t index) const; // get a copy of an element within this row
	
	size_t max() const;
	size_t min() const;
}

concept MatrixRow : MatrixConstRow, Matrix {
	this_t(const this_t &);
	this_t &operator =(const this_t &);
	void swap(this_t &m)
	~this_t();
	
	float_type &operator[](size_t index) const; // get a reference to an element within this row
}

concept MatrixConstColumn {
	this_t(const this_t &);
	this_t &operator =(const this_t &);
	void swap(this_t &m)	
	~this_t();

	float_ptype operator[](size_t index) const; // get a copy of an element within this column

	size_t max() const;
	size_t min() const;
}

concept MatrixColumn : MatrixConstColumn {  
	this_t(const this_t &);
	this_t &operator =(const this_t &);
	void swap(this_t &m)	
	~this_t();

	float_type &operator[](size_t index) const; // get a reference to an element within this column
}

concept MatrixConstSlice {
	this_t(const this_t &);
	this_t &operator =(const this_t &);
	void swap(this_t &m)	
	~this_t();

	float_ptype operator[](size_t index) const; // get a copy of an element within this column

	size_t max() const;
	size_t min() const;
}

concept MatrixSlice: MatrixConstslice {  
	this_t(const this_t &);
	this_t &operator =(const this_t &);
	void swap(this_t &m)	
	~this_t();
}


concept MatrixStorage : Matrix {
	this_t(const this_t &);
	this_t &operator =(const this_t &);
	void swap(this_t &m)	
	~this_t();

	void reserve(size_t rows, size_t columns);
}

// ************************ Tier 4 ************************ 

concept MatrixEx : Matrix {  
	this_t(const this_t &);
	this_t &operator =(const this_t &);
	void swap(this_t &m)	
	~this_t();

	// Row/Column accessors
	MatrixConstRow operator[](size_t row_zero_based_index) const;
	MatrixRow operator[](size_t row_zero_based_index);

	MatrixConstRow row(size_t row_zero_based_index) const;
	MatrixRow row(size_t row_zero_based_index);
	MatrixConstColumn column(size_t column_zero_based_index) const;
	MatrixColumn column(size_t column_zero_based_index);
	MatrixConstSlice slice(size_t row_begin, size_t column_begin, size_t row_end, size_t column_end) const;
	MatrixSlice slice(size_t row_begin, size_t column_begin, size_t row_end, size_t column_end);
}

Concept Map
Tier 1	ConstMatrix->Matrix
							
Tier 2	ConstMatrix2->Matrix2	algorithm2
							
Tier 3 	MatrixConstRow->MatrixRow	MatrixConstColumn->MatrixColumn	MatrixConstSlice->MatrixSlice

Tier 4	MatrixEx

Tier 5	algorithm5



Tier 4	MatrixEx
*/

namespace g_matrix {
    
template<typename T>
class MatrixConcept {
    T *_m;
    
    public:
    MatrixConcept(T &__m) : _m(&__m) { };
    
    T *matrix() const { return _m; };
    
    size_t rows() const { return _m->rows(); };
    size_t columns() const { return _m->columns(); };
    
    float_type &operator()(size_t row, size_t column)
    { return (*_m)(row,column); };
};

template<typename T>
class MatrixConcept<const T> {
    const T *_m;
    
    public:
    MatrixConcept(const T &__m) : _m(&__m) { };
    
    size_t rows() const { return _m->rows(); };
    size_t columns() const { return _m->columns(); };
    
    float_ptype operator()(size_t row, size_t column)
    { return (*_m)(row,column); };
};

template<unsigned long ROWS, unsigned long COLUMNS>
struct MatrixConcept<float_type[ROWS][COLUMNS]> {
    typedef float_type array_t[ROWS][COLUMNS];
    
    array_t *_m;
    
    public:
    MatrixConcept(array_t &__m) : _m(&__m) { };
    
    size_t rows() const { return ROWS; };
    size_t columns() const { return COLUMNS; };
    
    float_type &operator()(size_t row, size_t column)
    { return (*_m)[row][column]; };
};

template<unsigned long ROWS, unsigned long COLUMNS>
struct MatrixConcept<const float_type[ROWS][COLUMNS]> {
    typedef const float_type array_t[ROWS][COLUMNS];
    
    array_t *_m;
    
    public:
    MatrixConcept(array_t &__m) : _m(&__m) { };
    
    size_t rows() const { return ROWS; };
    size_t columns() const { return COLUMNS; };
    
    float_ptype operator()(size_t row, size_t column)
    { return (*_m)[row][column]; };
};
/*
template<typename T>
struct MatrixConcept<MatrixConcept<T> > 
    : public MatrixConcept<T> 
{
    MatrixConcept(const MatrixConcept<T> &adaptor) 
    : MatrixConcept<T>(adaptor.matrix()) 
    { };
}

template<typename T>
struct MatrixConcept<MatrixConcept<const T> > 
    : public MatrixConcept<const T> 
{
    MatrixConcept(const MatrixConcept<const T> &adaptor) 
    : MatrixConcept<const T>(adaptor.matrix()) 
    { };
}
*/
} // namespace g_matrix

#endif
