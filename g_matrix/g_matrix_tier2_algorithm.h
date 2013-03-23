/*
    File: g_matrix_tier2_algorithm.h
    Author: lance.gatlin@yahoo.com
    Date: 19 Sep 2008
    Version: 1

    Overview: 
	1) Declares and implements the following matrix functions:
		matrix_fill
		matrix_set_identity
		matrix_column_merge
		matrix_copy
		matrix_equal
		matrix_add
		matrix_subtract
		matrix_multiply
		matrix_dump
		matrix_swap
		matrix_max
		matrix_min
        
*/

#include <sstream>
#include <iostream>
#include <string_convert.h>

/*
	Fills a matrix with a float_type
*/
template<typename T>
inline void matrix_fill(T &_m, float_ptype value)
{
	GMATRIX_FUNC;

    MatrixConcept<T> m(_m);
    
    size_t i_stop = m.rows(),
            j_stop = m.columns();
            
    for(size_t i=0;i<i_stop;i++)
	{
        for(size_t j=0;j<j_stop;j++)
		{
            m(i,j) = value;
			GMATRIX_STATS(assigns,1);
			GMATRIX_STATS(loops,1);
		}
		GMATRIX_STATS(loops,1);
	}
}

/*
	Sets a matrix to the identity matrix
*/
template<typename T>
inline void matrix_set_identity(T &_m)
{
	GMATRIX_FUNC;

    MatrixConcept<T> m(_m);

    size_t i_stop = m.rows(),
            j_stop = m.columns();
            
    for(size_t i=0;i<i_stop;i++)
	{
        for(size_t j=0;j<j_stop;j++)
		{
            m(i,j) = (i == j ? 1 : 0);
			GMATRIX_STATS(compares,1);
			GMATRIX_STATS(assigns,1);
			GMATRIX_STATS(loops,1);
		}
		GMATRIX_STATS(loops,1);
	}
}

/*
	Merges two matrixes SRC and DEST such that [DEST|SRC]
*/
template<typename T1, class T2>
inline void matrix_column_merge(const T1 &_src, T2 &_dest)
{
	GMATRIX_FUNC;

    MatrixConcept<const T1> src(_src);
    MatrixConcept<T2> dest(_dest);

    size_t i_stop = src.rows() < dest.rows() ? src.rows() : dest.rows()
            ,j_stop = src.columns();
    
    size_t j_dest_start = dest.columns();
    
    for(size_t i=0;i<i_stop;i++)
    {
        size_t j_dest=j_dest_start;
        for(size_t j=0;j<j_stop;j++, j_dest++)
		{
            dest(i,j_dest) = src(i, j);
			GMATRIX_STATS(assigns,1);
			GMATRIX_STATS(loops,1);
		}
		GMATRIX_STATS(loops,1);
    } 
}

/*
	Sets matrix dest = src
*/
template<typename T1, class T2>
inline void matrix_copy(const T1 &_src, T2 &_dest)
{
	GMATRIX_FUNC;

    MatrixConcept<const T1> src(_src);
    MatrixConcept<T2> dest(_dest);

    size_t i_stop = src.rows() < dest.rows() ? src.rows() : dest.rows(),
            j_stop = src.columns() < dest.columns() ? src.columns() : dest.columns();
    
    for(size_t i=0;i<i_stop;i++)
	{
        for(size_t j=0;j<j_stop;j++)
		{
            dest(i,j) = src(i,j);
			GMATRIX_STATS(assigns,1);
			GMATRIX_STATS(loops,1);
		}
		GMATRIX_STATS(loops,1);
	}
}

/*
	Return true if matrix lhs == rhs
*/
template<typename T1, class T2>
inline bool matrix_equal(const T1 &_lhs, const T2 &_rhs)
{
	GMATRIX_FUNC;

    MatrixConcept<const T1> lhs(_lhs);
    MatrixConcept<const T2> rhs(_rhs);

    if(lhs.rows() != rhs.rows() || lhs.columns() != rhs.columns())
        return false;
        
    int i_stop = lhs.rows()
        ,j_stop = lhs.columns();
              
    for(size_t i=0;i<i_stop;i++)
	{
        for(size_t j=0;j<j_stop;j++)
		{
            if(lhs(i,j) != rhs(i,j))
                return false;
			GMATRIX_STATS(compares,1);
			GMATRIX_STATS(loops,1);
		}
		GMATRIX_STATS(loops,1);
	}
    return true;
}

/*
	Adds matrix lhs and rhs and places the result in dest
*/
// Matrix + Matrix
template<typename T1, class T2, class T3>
inline void matrix_add(const T1 &_lhs,const T2 &_rhs, T3 &_dest)
{
	GMATRIX_FUNC;

    MatrixConcept<const T1> lhs(_lhs);
    MatrixConcept<const T2> rhs(_rhs);
    MatrixConcept<T3> dest(_dest);

    int i_stop = lhs.rows() < rhs.rows() ? lhs.rows() : rhs.rows(),
        j_stop = lhs.columns() < lhs.columns() ? lhs.columns() : rhs.columns();
        
    for(size_t i=0;i<i_stop;i++)
	{
        for(size_t j=0;j<j_stop;j++)
		{
            dest(i,j) = lhs(i,j) + rhs(i,j);
			GMATRIX_STATS(adds,1);
			GMATRIX_STATS(assigns,1);
			GMATRIX_STATS(loops,1);
		}
		GMATRIX_STATS(loops,1);
	}
}

/*
	Subtracts matrix rhs from lhs and places the result in dest
*/
// Matrix - Matrix
template<typename T1, class T2, class T3>
inline void matrix_subtract(const T1 &_lhs,const T2 &_rhs, T3 &_dest)
{
	GMATRIX_FUNC;

    MatrixConcept<const T1> lhs(_lhs);
    MatrixConcept<const T2> rhs(_rhs);
    MatrixConcept<T3> dest(_dest);

    int i_stop = lhs.rows() < rhs.rows() ? lhs.rows() : rhs.rows(),
        j_stop = lhs.columns() < lhs.columns() ? lhs.columns() : rhs.columns();
        
    for(size_t i=0;i<i_stop;i++)
	{
        for(size_t j=0;j<j_stop;j++)
		{
            dest(i,j) = lhs(i,j) - rhs(i,j);
			GMATRIX_STATS(subtracts,1);
			GMATRIX_STATS(assigns,1);
			GMATRIX_STATS(loops,1);
		}
		GMATRIX_STATS(loops,1);
	}
}

/*
	Multiplies matrix lhs by a scalar float_type and places the result in dest
*/
// Matrix * float_type
template<typename T1, class T2>
inline void matrix_multiply(const T1 &_lhs, float_ptype rhs, T2 &_dest)
{
	GMATRIX_FUNC;

    MatrixConcept<const T1> lhs(_lhs);
    MatrixConcept<T2> dest(_dest);

    int i_stop = lhs.rows(), j_stop = lhs.columns();
    for(size_t i=0;i<i_stop;i++)
	{
        for(size_t j=0;j<j_stop;j++)
		{
            dest(i,j) = lhs(i,j) * rhs;
			GMATRIX_STATS(multiplies,1);
			GMATRIX_STATS(assigns,1);
			GMATRIX_STATS(loops,1);
		}
		GMATRIX_STATS(loops,1);
	}
}

/*
	Multiplies matrix lhs by matrix rhs and places the result in dest
	
	assumed &dest != &lhs OR &dest != &rhs
*/
// Matrix * Matrix
template<typename T1, class T2, class T3>
inline void matrix_multiply(const T1 &_lhs,const T2 &_rhs, T3 &_dest)
{
	GMATRIX_FUNC;

    MatrixConcept<const T1> lhs(_lhs);
    MatrixConcept<const T2> rhs(_rhs);
    MatrixConcept<T3> dest(_dest);

    size_t i_stop = lhs.rows()
            ,j_stop = rhs.columns()
                ,k_stop = lhs.columns() < rhs.rows() ? lhs.columns() : rhs.rows();
    
    if(!k_stop)
        return;
                        
    for(size_t i=0;i<i_stop;i++)
	{
        for(size_t j=0;j<j_stop;j++)
		{
			dest(i,j) = lhs(i,0) * rhs(0,j);
			GMATRIX_STATS(assigns,1);
			GMATRIX_STATS(multiplies,1);
	        
			for(size_t k=1;k<k_stop;k++)
			{
				dest(i,j) += lhs(i,k) * rhs(k,j);
				GMATRIX_STATS(assigns,1);
				GMATRIX_STATS(adds,1);
				GMATRIX_STATS(multiplies,1);
				GMATRIX_STATS(loops,1);
			}
			GMATRIX_STATS(loops,1);
		}
		GMATRIX_STATS(loops,1);
	}
}

/*
	Take a section of a matrix specified by two points and copy it into a dest matrix 
*/
/*
template<typename T1, class T2>
inline void matrix_slice(const T1 &_src, size_t row_begin, size_t column_begin, size_t row_end, size_t column_end, T2 &_dest, size_t dest_row = 0, size_t dest_column = 0)
{
    MatrixConcept<const T1> src(_src);
    MatrixConcept<T2> dest(_dest);

    int i_stop = row_end < row_begin + dest.rows() ? row_end : row_begin + dest.rows() 
        ,j_stop = column_end < column_begin + dest.columns() ? column_end : column_begin + dest.columns();
    
    for(size_t i=row_begin,di=dest_row;i < i_stop;i++,di++)
        for(size_t j=column_begin,dj=dest_column;j < j_stop;j++,dj++)
            dest(di,dj) = src(i,j);
}


template<typename T1, class T2>
inline void matrix_copy(const T1 &_src, size_t row_begin, size_t row_end, size_t column_begin, size_t column_end, T2 &_dest, size_t dest_row = 0, size_t dest_column = 0)
{
    MatrixConcept<const T1> src(_src);
    MatrixConcept<T2> dest(_dest);

    matrix_slice(src, row_begin, row_end, column_begin, column_end, dest, dest_row, dest_column);
}

template<typename T1, class T2>
inline void matrix_copy(const T1 &_src, T2 &_dest, size_t dest_row, size_t dest_column)
{
    MatrixConcept<const T1> src(_src);
    MatrixConcept<T2> dest(_dest);

    matrix_slice(src, 0, src.rows(), 0, src.columns(), dest, dest_row, dest_column);
}
*/

/*
	Swaps the values of lhs and rhs
*/
template<typename T1, class T2>
inline void matrix_swap(T1 &_lhs, T2 &_rhs)
{
	GMATRIX_FUNC;

    MatrixConcept<T1> lhs(_lhs);
    MatrixConcept<T2> rhs(_rhs);

    float_type temp;
    
    int i_stop = lhs.rows() < rhs.rows() ? lhs.rows() : rhs.rows(),
        j_stop = lhs.columns() < lhs.columns() ? lhs.columns() : rhs.columns();
        
    if(&lhs(0,0) == &rhs(0,0))
        return;
    
    for(size_t i=0;i<i_stop;i++)
	{
        for(size_t j=0;j<j_stop;j++)
        {
            temp = lhs(i,j);
            lhs(i,j) = rhs(i,j);
            rhs(i,j) = temp;
			GMATRIX_STATS(assigns,3);
			GMATRIX_STATS(loops,1);
        }
		GMATRIX_STATS(loops,1);
	}
        
}

/*
	Finds the maximum value in a matrix and returns the row,column location and the value
*/
template<typename T>
inline void matrix_max(const T &_m, size_t &row, size_t &column, float_type &max)
{
	GMATRIX_FUNC;

    MatrixConcept<const T> m(_m);
    
    int i_stop = m.rows()
        ,j_stop = m.columns();
        
	row = column = 0;
	max = m(0,0);

    for(size_t i=0;i<i_stop;i++)
	{
        for(size_t j=0;j<j_stop;j++)
		{
            if(max < m(i,j))
			{
				row = i;
				column = j;
				max = m(i,j);
			}
			GMATRIX_STATS(compares,1);
			GMATRIX_STATS(loops,1);
		}
		GMATRIX_STATS(loops,1);
	}
}

/*
	Finds the minimum value in a matrix and returns the row,column location and the value
*/
template<typename T>
inline void matrix_min(const T &_m, size_t &row, size_t &column, float_type &min)
{
	GMATRIX_FUNC;

    MatrixConcept<const T> m(_m);
    
    int i_stop = m.rows()
        ,j_stop = m.columns();
        
	row = column = 0;
	min = m(0,0);

    for(size_t i=0;i<i_stop;i++)
	{
        for(size_t j=0;j<j_stop;j++)
		{
            if(m(i,j) < min)
			{
				row = i;
				column = j;
				min = m(i,j);
			}
			GMATRIX_STATS(compares,1);
			GMATRIX_STATS(loops,1);
		}
		GMATRIX_STATS(loops,1);
	}
}

/*
	Insert a streamable matrix to a string stream
*/
template<class ConceptMatrix>
inline std::ostringstream &matrix_insert(std::ostringstream &out, const ConceptMatrix &_m)
{
	MatrixConcept<const ConceptMatrix> m(_m);

	out << '[';

	size_t i_stop = m.rows()
			,j_stop = m.columns();

	for(size_t i=0;i<i_stop;i++)
	{
		for(size_t j=0;j<j_stop;j++)
		{
			out  << ' ' << m(i,j);
		}
		out << ';';
	}

	out << " ]";
	
	return out;
}
template<class ConceptMatrix>
inline void matrix_convert(const ConceptMatrix &m, std::string &dest)
{
	std::ostringstream out;
	matrix_insert(out, m);
	dest = out.str();
}

inline bool matrix_extract_read_control_char(std::istringstream &in, char c)
{
	char ch;
	in >> ch;
	if(c != ch)
	{
		in.clear(std::ios::failbit);
		return false;
	}
	return true;
}

/*
	Extract a streamable matrix from a string stream
*/
template<class ConceptMatrix>
inline std::istringstream &matrix_extract(std::istringstream &in, ConceptMatrix &_m)
{
    std::ios::iostate saved = in.exceptions();
    
	MatrixConcept<ConceptMatrix> m(_m);
	
	//out << "[ ";
	if(!matrix_extract_read_control_char(in, '['))
		return in;
    
    char ch;
    
	size_t i = 0, j = 0;
    float_type temp;
    
	do 
	{
        in.exceptions(std::ios::eofbit);
    	in >> temp;
	
        while(in.good())
        {
            m(i,j++) = temp;
			in >> temp;
        }
        
		in.clear();
        in.exceptions(saved);

		in >> ch;

		i++;
		j=0;
	}
	while(in.good() && ch == ';');
    
    in.exceptions(saved);
	
	if(ch != ']')
	{
		in.clear(std::ios::failbit);
		return in;
	}

//	if(!matrix_extract_read_control_char(in, ';'))
//		return in;
		
	return in;
}
template<class ConceptMatrix>
inline void matrix_convert(const std::string &src, ConceptMatrix &m)
{
	std::istringstream in(src);
	in.exceptions(std::ios::failbit | std::ios::badbit);
	matrix_extract(in, m);
}

/*
	Test if it is possible to extract a streamable matrix from a string stream
*/
struct MatrixExtractionTester {
	float_type temp;

    size_t rows() const { return 0; };
    size_t columns() const { return 0; };

	float_type &operator()(size_t i, size_t j) 
	{ return temp; };
	float_ptype operator()(size_t i, size_t j)  const
	{ return temp; };
};

inline bool matrix_can_extract(const std::string &s)
{
	std::istringstream in(s);
	MatrixExtractionTester m;
	matrix_extract(in, m);
	return in.good();
}

/*
	Displays a tab separated matrix to stream
*/
// output text dump of matrix content
template<typename T>
inline std::ostream & matrix_dump(std::ostream &out, const T &_m)
{
    MatrixConcept<const T> m(_m);

    size_t i_stop = m.rows(), j_stop = m.columns();
    
    for(size_t i=0;i<i_stop;i++)
    {
        out << m(i,0);
        for(size_t j=1;j<j_stop;j++)
            out << '\t' << m(i,j);
        out << std::endl;
    }    
    return out;
}

