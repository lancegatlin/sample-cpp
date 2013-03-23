#ifndef __G2D_POLYGON_H
#define __G2D_POLYGON_H

#include <vector>
#include <algorithm>
#include <g2d/g2d_line.h>

namespace g2d {
    
class Polygon : public vector<Point> {
    typedef vector<Point>::iterator iterator;
    
    public:
    Polygon() { };
    // Points will be forced to anti-clockwise
    Polygon(iterator begin, iterator end)
    : vector<Point>(begin,end) 
    { 
        if(size() < 3)
            return;
        
        Line l((*this)[0], (*this)[1]);
        
        if(l(*this[2]) < 0)
            // Clockwise rotation so reverse the order
            // To make it anti-clockwise
            reverse(begin(), end());
    };
    
    bool contains(const Point &p) const
    {
        int end = count();
        
        if(end < 3)
            return false;
            
        for(int i=0;i<end;i++)
        {
            Line l((*this)[i], (*this)[i+1]);
            
            if(fless(l(p),0.0))
                return false;
        }
        return true;
    }
    
    Polygon intersects(const Polygon &p) const { return getIntersectionWith(p); };
    Polygon getIntersectionWith(const Polygon &p) const
    {
        
    }
    
}

} // namespace g2d

#endif
