/*
    File: g_matrix_tier5_class_MatrixAdaptor.h
    Author: lance.gatlin@yahoo.com
    Date: 19 Sep 2008
    Version: 1

    Overview: 
        1) Declares and implements the MatrixAdaptor
*/

template<class ConceptMatrix>
class MatrixAdaptor : public AnyMatrix<MatrixAdaptorStorage<ConceptMatrix> > {
    public:
    typedef MatrixAdaptor<ConceptMatrix> this_t;
    typedef AnyMatrix<MatrixAdaptorStorage<ConceptMatrix> > parent_t;
    
    MatrixAdaptor() { };
    
    MatrixAdaptor(ConceptMatrix m)
    {
        matrix(m);
    }
    
    MatrixAdaptor(const this_t &copy_me)
    : parent_t((const parent_t &)copy_me)
    { }
    
	// default destructor

    this_t &operator =(ConceptMatrix assign_me)
    { matrix(assign_me); };

    template<class OtherConceptMatrix>
    this_t &operator =(const OtherConceptMatrix &assign_me)
	{ parent_t::operator =(assign_me); return *this; };

    this_t &operator =(const this_t &assign_me)
	{ parent_t::operator =((const parent_t &)assign_me); return *this; };
};
