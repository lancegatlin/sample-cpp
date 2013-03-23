#ifndef __G2D_VECTOR_LINE_H
#define __G2D_VECTOR_LINE_H

#include "g2d_scalar_vector.h"

namespace g2d {
    
class VectorLine {
    Point _base;
    ScalarVector _direction;
    
    public:
    VectorLine(const Point &__base, const ScalarVector &__direction)
    : _base(__base), _direction(__direction) { };
    
    Point base() const { return _origin; };
    void base(const Point &p) { };
    ScalarVector direction() const { return _v; };
    void direction(ScalarVector __direction) { _direction = __direction; };
}

} // namespace g2d

#endif
