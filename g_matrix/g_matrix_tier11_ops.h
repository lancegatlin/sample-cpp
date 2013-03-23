/*
    File: g_matrix_tier11_ops.h
    Author: lance.gatlin@yahoo.com
    Date: 19 Sep 2008
    Version: 1

    Overview: 
	1) Declares and implements |, +,  -, *, / for MatrixRow, MatrixColumn, AnyMatrix and matrix arrays
*/

/*
Removed due to ambiguity errors with:
AnyMatrix<S> + Row

Ambiguity between operator +(AnyMatrix, ConceptMatrix) and operator +(Row, ConceptMatrix)

Downside:
If ConceptMatrix is not a Column, Row or AnyMatrix then:
ConceptMatrix + Row has to be written Row + ConceptMatrix


// ConceptMatrix + Row
template<class ConceptMatrix1, class ConceptMatrix2>
DynamicMatrix operator +(const ConceptMatrix1 &lhs, g_matrix::MatrixRow<ConceptMatrix2> rhs)
{
    g_matrix::DynamicMatrix retv(   std::max(lhs.rows(),rhs.rows())
                                    ,std::max(lhs.columns(),rhs.columns())
                                    );
    
    matrix_add(lhs,rhs,retv);
        
    return retv;
}
*/



/********************************* Row Ops ************************************/
// Row op-equal functions are pass "by value" since a Row is really an alias(pointer) for a ConceptMatrix

// Row | ConceptMatrix
template<class ConceptMatrix1, class ConceptMatrix2>
inline g_matrix::DynamicMatrix operator |(g_matrix::MatrixRow<ConceptMatrix1> lhs, const ConceptMatrix2 &rhs)
{ return g_matrix::matrix_column_merge(lhs, rhs); }

// Row + ConceptMatrix
template<class ConceptMatrix1, class ConceptMatrix2>
inline g_matrix::DynamicMatrix operator +(g_matrix::MatrixRow<ConceptMatrix1> lhs, const ConceptMatrix2 &rhs)
{ return g_matrix::matrix_add(lhs, rhs); }

// Row - ConceptMatrix
template<class ConceptMatrix1, class ConceptMatrix2>
inline g_matrix::DynamicMatrix operator -(g_matrix::MatrixRow<ConceptMatrix1> lhs, const ConceptMatrix2 &rhs)
{ return g_matrix::matrix_subtract(lhs, rhs); }

// Row *= ConceptMatrix
template<class ConceptMatrix1, class ConceptMatrix2>
inline g_matrix::MatrixRow<ConceptMatrix1> operator *=(g_matrix::MatrixRow<ConceptMatrix1> lhs, const ConceptMatrix2 &rhs)
{ g_matrix::matrix_multiply_equal(lhs, rhs); return lhs; }

// Row * ConceptMatrix
template<class ConceptMatrix1, class ConceptMatrix2>
inline g_matrix::DynamicMatrix operator *(g_matrix::MatrixRow<ConceptMatrix1> lhs, const ConceptMatrix2 &rhs)
{ return g_matrix::matrix_multiply(lhs, rhs); }

// Row * float_type
template<class ConceptMatrix>
inline g_matrix::DynamicMatrix operator *(g_matrix::MatrixRow<ConceptMatrix> lhs, g_matrix::float_ptype rhs)
{ return g_matrix::matrix_multiply(lhs, rhs); }

// Row / float_type
template<class ConceptMatrix>
inline g_matrix::DynamicMatrix operator /(g_matrix::MatrixRow<ConceptMatrix> lhs, g_matrix::float_ptype rhs)
{ return g_matrix::matrix_divide(lhs,rhs); };

template<class ConceptMatrix>
struct string_convert<g_matrix::MatrixRow<ConceptMatrix> > 
//    : public std_string_convert<g_matrix::MatrixRow<ConceptMatrix> > 
{
    typedef g_matrix::MatrixRow<ConceptMatrix> value_type;
    
	static void convert(const std::string &lhs, value_type &rhs)
	{ g_matrix::matrix_convert(lhs, rhs); }
	static void convert(const value_type &lhs, std::string &rhs)
	{ g_matrix::matrix_convert(lhs, rhs); }
    static bool canConvert(const std::string &src)
    { g_matrix::matrix_can_extract(src); };
};


/********************************* Column Ops ************************************/
// Column op-equal functions are pass "by value" since a Column is really an alias(pointer) for a ConceptMatrix

// Column | ConceptMatrix
template<class ConceptMatrix1, class ConceptMatrix2>
inline g_matrix::DynamicMatrix operator |(g_matrix::MatrixColumn<ConceptMatrix1> lhs, const ConceptMatrix2 &rhs)
{ return g_matrix::matrix_column_merge(lhs, rhs); }

// Column + ConceptMatrix
template<class ConceptMatrix1, class ConceptMatrix2>
inline g_matrix::DynamicMatrix operator +(g_matrix::MatrixColumn<ConceptMatrix1> lhs, const ConceptMatrix2 &rhs)
{ return g_matrix::matrix_add(lhs, rhs); }

// Column - ConceptMatrix
template<class ConceptMatrix1, class ConceptMatrix2>
inline g_matrix::DynamicMatrix operator -(g_matrix::MatrixColumn<ConceptMatrix1> lhs, const ConceptMatrix2 &rhs)
{ return g_matrix::matrix_subtract(lhs, rhs); }

// Column *= ConceptMatrix
template<class ConceptMatrix1, class ConceptMatrix2>
inline g_matrix::MatrixColumn<ConceptMatrix1> operator *=(g_matrix::MatrixColumn<ConceptMatrix1> lhs, const ConceptMatrix2 &rhs)
{ g_matrix::matrix_multiply_equal(lhs, rhs); return lhs; }

// Column * ConceptMatrix
template<class ConceptMatrix1, class ConceptMatrix2>
inline g_matrix::DynamicMatrix operator *(g_matrix::MatrixColumn<ConceptMatrix1> lhs, const ConceptMatrix2 &rhs)
{ return g_matrix::matrix_multiply(lhs, rhs); }

// Column * float_type
template<class ConceptMatrix>
inline g_matrix::DynamicMatrix operator *(g_matrix::MatrixColumn<ConceptMatrix> lhs, g_matrix::float_ptype rhs)
{ return g_matrix::matrix_multiply(lhs, rhs); }

// Column / float_type
template<class ConceptMatrix>
inline g_matrix::DynamicMatrix operator /(g_matrix::MatrixColumn<ConceptMatrix> lhs, g_matrix::float_ptype rhs)
{ return g_matrix::matrix_divide(lhs,rhs); };

template<class ConceptMatrix>
struct string_convert<g_matrix::MatrixColumn<ConceptMatrix> > 
//    : public std_string_convert<g_matrix::MatrixColumn<ConceptMatrix> > 
{
    typedef g_matrix::MatrixColumn<ConceptMatrix> value_type;
    
	static void convert(const std::string &lhs, value_type &rhs)
	{ g_matrix::matrix_convert(lhs, rhs); }
	static void convert(const value_type &lhs, std::string &rhs)
	{ g_matrix::matrix_convert(lhs, rhs); }
    static bool canConvert(const std::string &src)
    { g_matrix::matrix_can_extract(src); };
};

/********************************* Slice Ops ************************************/
// Slice op-equal functions are pass "by value" since a Slice is really an alias(pointer) for a ConceptMatrix

// Slice | ConceptMatrix
template<class ConceptMatrix1, class ConceptMatrix2>
inline g_matrix::DynamicMatrix operator |(g_matrix::MatrixSlice<ConceptMatrix1> lhs, const ConceptMatrix2 &rhs)
{ return g_matrix::matrix_column_merge(lhs, rhs); }

// Slice + ConceptMatrix
template<class ConceptMatrix1, class ConceptMatrix2>
inline g_matrix::DynamicMatrix operator +(g_matrix::MatrixSlice<ConceptMatrix1> lhs, const ConceptMatrix2 &rhs)
{ return g_matrix::matrix_add(lhs, rhs); }

// Slice - ConceptMatrix
template<class ConceptMatrix1, class ConceptMatrix2>
inline g_matrix::DynamicMatrix operator -(g_matrix::MatrixSlice<ConceptMatrix1> lhs, const ConceptMatrix2 &rhs)
{ return g_matrix::matrix_subtract(lhs, rhs); }

// Slice *= ConceptMatrix
template<class ConceptMatrix1, class ConceptMatrix2>
inline g_matrix::MatrixSlice<ConceptMatrix1> operator *=(g_matrix::MatrixSlice<ConceptMatrix1> lhs, const ConceptMatrix2 &rhs)
{ g_matrix::matrix_multiply_equal(lhs, rhs); return lhs; }

// Slice * ConceptMatrix
template<class ConceptMatrix1, class ConceptMatrix2>
inline g_matrix::DynamicMatrix operator *(g_matrix::MatrixSlice<ConceptMatrix1> lhs, const ConceptMatrix2 &rhs)
{ return g_matrix::matrix_multiply(lhs, rhs); }

// Slice * float_type
template<class ConceptMatrix>
inline g_matrix::DynamicMatrix operator *(g_matrix::MatrixSlice<ConceptMatrix> lhs, g_matrix::float_ptype rhs)
{ return g_matrix::matrix_multiply(lhs, rhs); }

// Slice / float_type
template<class ConceptMatrix>
inline g_matrix::DynamicMatrix operator /(g_matrix::MatrixSlice<ConceptMatrix> lhs, g_matrix::float_ptype rhs)
{ return g_matrix::matrix_divide(lhs,rhs); };

template<class ConceptMatrix>
struct string_convert<g_matrix::MatrixSlice<ConceptMatrix> > 
//    : public std_string_convert<g_matrix::MatrixSlice<ConceptMatrix> > 
{
    typedef g_matrix::MatrixSlice<ConceptMatrix> value_type;
    
	static void convert(const std::string &lhs, value_type &rhs)
	{ g_matrix::matrix_convert(lhs, rhs); }
	static void convert(const value_type &lhs, std::string &rhs)
	{ g_matrix::matrix_convert(lhs, rhs); }
    static bool canConvert(const std::string &src)
    { g_matrix::matrix_can_extract(src); };
};

/********************************* AnyMatrix Ops *********************************/

// AnyMatrix op-equal functions are pass "by reference" since an AnyMatrix is not an alias(pointer)

// AnyMatrix | ConceptMatrix
template<class ConceptMatrixStorage1, class ConceptMatrix2>
inline g_matrix::DynamicMatrix operator |(const g_matrix::AnyMatrix<ConceptMatrixStorage1> &lhs, const ConceptMatrix2 &rhs)
{ return g_matrix::matrix_column_merge(lhs, rhs); }

// AnyMatrix + ConceptMatrix
template<class ConceptMatrixStorage1, class ConceptMatrix2>
inline g_matrix::DynamicMatrix operator +(const g_matrix::AnyMatrix<ConceptMatrixStorage1> &lhs, const ConceptMatrix2 &rhs)
{ return g_matrix::matrix_add(lhs, rhs); }

// AnyMatrix - ConceptMatrix
template<class ConceptMatrixStorage1, class ConceptMatrix2>
inline g_matrix::DynamicMatrix operator -(const g_matrix::AnyMatrix<ConceptMatrixStorage1> &lhs, const ConceptMatrix2 &rhs)
{ return g_matrix::matrix_subtract(lhs, rhs); }

// AnyMatrix * ConceptMatrix
template<class ConceptMatrixStorage1, class ConceptMatrix2>
inline g_matrix::DynamicMatrix operator *(const g_matrix::AnyMatrix<ConceptMatrixStorage1> &lhs, const ConceptMatrix2 &rhs)
{ return g_matrix::matrix_multiply(lhs, rhs); }

// AnyMatrix * float_type
template<class ConceptMatrixStorage>
inline g_matrix::DynamicMatrix operator *(const g_matrix::AnyMatrix<ConceptMatrixStorage> &lhs, g_matrix::float_ptype rhs)
{ return g_matrix::matrix_multiply(lhs, rhs); }

// AnyMatrix / float_type
template<class ConceptMatrixStorage>
inline g_matrix::DynamicMatrix operator /(const g_matrix::AnyMatrix<ConceptMatrixStorage> &lhs, g_matrix::float_ptype rhs)
{ return g_matrix::matrix_divide(lhs,rhs); };

template<class ConceptMatrix>
struct string_convert<g_matrix::AnyMatrix<ConceptMatrix> > 
//    : public std_string_convert<g_matrix::AnyMatrix<ConceptMatrix> >
{
    typedef g_matrix::AnyMatrix<ConceptMatrix> value_type;
    
	static void convert(const std::string &lhs, value_type &rhs)
	{ g_matrix::matrix_convert(lhs, rhs); }
	static void convert(const value_type &lhs, std::string &rhs)
	{ g_matrix::matrix_convert(lhs, rhs); }
    static bool canConvert(const std::string &src)
    { g_matrix::matrix_can_extract(src); };
};

template<>
struct string_convert<g_matrix::DynamicMatrix > 
//    : public std_string_convert<g_matrix::DynamicMatrix >     
{
    typedef g_matrix::DynamicMatrix value_type;
    
	static void convert(const std::string &lhs, value_type &rhs)
	{ g_matrix::matrix_convert(lhs, rhs); }
	static void convert(const value_type &lhs, std::string &rhs)
	{ g_matrix::matrix_convert(lhs, rhs); }
    static bool canConvert(const std::string &src)
    { g_matrix::matrix_can_extract(src); };
};

template<unsigned long ROWS, unsigned long COLUMNS>
struct string_convert<g_matrix::StaticMatrix<ROWS,COLUMNS> > 
//    : public std_string_convert<g_matrix::StaticMatrix<ROWS,COLUMNS> >     
{
    typedef g_matrix::StaticMatrix<ROWS,COLUMNS> value_type;
    
	static void convert(const std::string &lhs, value_type &rhs)
	{ g_matrix::matrix_convert(lhs, rhs); }
	static void convert(const value_type &lhs, std::string &rhs)
	{ g_matrix::matrix_convert(lhs, rhs); }
    static bool canConvert(const std::string &src)
    { g_matrix::matrix_can_extract(src); };
};

/********************************* MatrixArray Ops *********************************/

// MatrixArray | ConceptMatrix
template<unsigned long ROWS, unsigned long COLUMNS, class ConceptMatrix2>
inline g_matrix::DynamicMatrix operator |(const g_matrix::float_type (&lhs)[ROWS][COLUMNS], const ConceptMatrix2 &rhs)
{ return g_matrix::matrix_column_merge(lhs, rhs); }

// MatrixArray + ConceptMatrix
template<unsigned long ROWS, unsigned long COLUMNS, class ConceptMatrix2>
inline g_matrix::DynamicMatrix operator +(g_matrix::float_type (&lhs)[ROWS][COLUMNS], const ConceptMatrix2 &rhs)
{ return g_matrix::matrix_add(lhs, rhs); }

// MatrixArray - ConceptMatrix
template<unsigned long ROWS, unsigned long COLUMNS, class ConceptMatrix2>
inline g_matrix::DynamicMatrix operator -(const g_matrix::float_type (&lhs)[ROWS][COLUMNS], const ConceptMatrix2 &rhs)
{ return g_matrix::matrix_subtract(lhs, rhs); }

// AnyMatrix *= ConceptMatrix
template<class ConceptMatrixStorage1, class ConceptMatrix2>
inline g_matrix::AnyMatrix<ConceptMatrixStorage1> &operator *=(g_matrix::AnyMatrix<ConceptMatrixStorage1> &lhs, const ConceptMatrix2 &rhs)
{ g_matrix::matrix_multiply_equal(lhs, rhs); return lhs; }

// MatrixArray * ConceptMatrix
template<unsigned long ROWS, unsigned long COLUMNS, class ConceptMatrix2>
inline g_matrix::DynamicMatrix operator *(const g_matrix::float_type (&lhs)[ROWS][COLUMNS], const ConceptMatrix2 &rhs)
{ return g_matrix::matrix_multiply(lhs, rhs); }

template<unsigned long ROWS, unsigned long COLUMNS>
struct string_convert<g_matrix::float_type[ROWS][COLUMNS] > 
//    : public std_string_convert<g_matrix::float_type[ROWS][COLUMNS]> 
{
    typedef g_matrix::float_type (value_type)[ROWS][COLUMNS];
    
	static void convert(const std::string &lhs, value_type &rhs)
	{ g_matrix::matrix_convert(lhs, rhs); }
	static void convert(const value_type &lhs, std::string &rhs)
	{ g_matrix::matrix_convert(lhs, rhs); }
    static bool canConvert(const std::string &src)
    { g_matrix::matrix_can_extract(src); };
};

/*

Compiler doesn't like these

    //    `g_matrix::DynamicMatrix operator*(const g_matrix::float_type (&)[ROWS][COLUMNS], const double&)' 
    // must have an argument of class or enumerated type 

// MatrixArray * float_type
template<unsigned long ROWS, unsigned long COLUMNS, class ConceptMatrix2>
inline g_matrix::DynamicMatrix operator *(const g_matrix::float_type (&lhs)[ROWS][COLUMNS], g_matrix::float_ptype rhs)
{ return g_matrix::matrix_multiply(lhs, rhs); }

// MatrixArray *= float_type
template<unsigned long ROWS, unsigned long COLUMNS, class ConceptMatrix2>
inline typename g_matrix::matrix_array<ROWS,COLUMNS>::reference operator *=(g_matrix::float_type (&lhs)[ROWS][COLUMNS], g_matrix::float_ptype rhs)
{ g_matrix::matrix_multiply(lhs, rhs, lhs); return lhs; }

// MatrixArray / float_type
template<unsigned long ROWS, unsigned long COLUMNS, class ConceptMatrix2>
inline g_matrix::DynamicMatrix operator /(const g_matrix::float_type (&lhs)[ROWS][COLUMNS], g_matrix::float_ptype rhs)
{ return g_matrix::matrix_divide(lhs,rhs); };

// MatrixArray /= float_type
template<unsigned long ROWS, unsigned long COLUMNS, class ConceptMatrix2>
inline typename g_matrix::matrix_array<ROWS,COLUMNS>::reference operator /=(g_matrix::float_type (&lhs)[ROWS][COLUMNS], g_matrix::float_ptype rhs)
{ g_matrix::matrix_divide(lhs,rhs); return lhs; }
*/
