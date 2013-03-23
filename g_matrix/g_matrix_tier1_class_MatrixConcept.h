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

concept MatrixStorage : Matrix {
	this_t(const this_t &);
	this_t &operator =(const this_t &);
	void swap(this_t &m)	
	~this_t();

	void reserve(size_t rows, size_t columns);
}

// ************************ Tier 4 ************************ 

// Row of a matrix
concept MatrixConstRow : ConstMatrix2 {
	this_t(const this_t &);
	this_t &operator =(const this_t &);
	void swap(this_t &m)	
	~this_t();

	float_ptype operator[](size_t index) const; // get a copy of an element within this row
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
}

concept MatrixColumn : MatrixConstColumn {  
	this_t(const this_t &);
	this_t &operator =(const this_t &);
	void swap(this_t &m)	
	~this_t();

	float_type &operator[](size_t index) const; // get a reference to an element within this column
}

// ************************ Tier 5 ************************ 

concept ConstMatrix3 : ConstMatrix2 {
	MatrixConstRow operator[](size_t) const;

	MatrixConstRow row(size_t) const;
	MatrixConstColumn row(size_t) const;
}

concept Matrix3 : ConstMatrix3, Matrix2 {
	MatrixRow operator[](size_t);

	MatrixRow row(size_t);
	MatrixColumn column(size_t);
}

// ************************ Tier 6 ************************ 

concept MatrixConstSlice : ConstMatrix3 {
	this_t(const this_t &);
	this_t &operator =(const this_t &);
	void swap(this_t &m)	
	~this_t();
}

concept MatrixSlice: Matrix3 {  
	this_t(const this_t &);
	this_t &operator =(const this_t &);
	void swap(this_t &m)	
	~this_t();
}


// ************************ Tier 7 ************************ 

concept ConstMatrix4 : ConstMatrix3 {
	MatrixConstSlice slice(size_t row, size_t column) const;
	MatrixConstSlice slice(size_t row_begin, size_t column_begin, size_t row_end, size_t column_end) const;
}

concept Matrix4 : ConstMatrix4, Matrix3 {
	MatrixSlice slice(size_t row, size_t column);
	MatrixSlice slice(size_t row_begin, size_t column_begin, size_t row_end, size_t column_end);
}

// ************************ Tier 7 ************************ 

concept AnyMatrix : Matrix4, MatrixStorage {  
	this_t(const this_t &);
	this_t &operator =(const this_t &);
	void swap(this_t &m)	
	~this_t();
}

*/

template<typename T>
class MatrixConcept {
    T *_m;
    
    public:
	typedef T value_type;
	typedef value_type &reference;
	typedef const value_type &const_reference;
	typedef value_type *pointer;
	typedef const value_type *const_pointer;

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
	typedef T value_type;
	typedef value_type &reference;
	typedef const value_type &const_reference;
	typedef value_type *pointer;
	typedef const value_type *const_pointer;

	MatrixConcept(const T &__m) : _m(&__m) { };
    
    size_t rows() const { return _m->rows(); };
    size_t columns() const { return _m->columns(); };
    
    float_ptype operator()(size_t row, size_t column) const
    { return (*_m)(row,column); };
};

template<unsigned long ROWS, unsigned long COLUMNS>
struct MatrixConcept<float_type[ROWS][COLUMNS]> {
	public:
    typedef float_type value_type[ROWS][COLUMNS];
	typedef value_type &reference;
	typedef const value_type &const_reference;
	typedef value_type *pointer;
	typedef const value_type *const_pointer;
    
	private:
    pointer _m;
    
    public:
    MatrixConcept(reference __m) : _m(&__m) { };
    
    size_t rows() const { return ROWS; };
    size_t columns() const { return COLUMNS; };
    
    float_type &operator()(size_t row, size_t column)
    { return (*_m)[row][column]; };
};

template<unsigned long ROWS, unsigned long COLUMNS>
struct MatrixConcept<const float_type[ROWS][COLUMNS]> {
	public:
    typedef const float_type value_type[ROWS][COLUMNS];
	typedef value_type &reference;
	typedef const value_type &const_reference;
	typedef value_type *pointer;
	typedef const value_type *const_pointer;
    
	private:
    pointer _m;
    
    public:
    MatrixConcept(reference __m) : _m(&__m) { };
    
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
