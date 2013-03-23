#ifndef __G2D_SCALAR_VECTOR_H
#define __G2D_SCALAR_VECTOR_H

#include "g2d_vector.h"

namespace g2d {
    
class ScalarVector : public Vector {
    float_type _k;
    
    public:
    ScalarVector() { };
    ScalarVector(DoesNotExist dne) 
    : Point(DoesNotExist) { _k = dne; };
    ScalarVector(float_ptype __k, const Vector &v)
    : Vector(v), _k(__k) { };
    
    float_ptype k() const { return _k; };
    void k(float_type f) { return _k = f; };
}

} // namespace g2d

#endif
