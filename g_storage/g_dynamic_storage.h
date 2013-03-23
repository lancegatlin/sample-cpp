#ifndef __G_DYNAMIC_STORAGE_H
#define __G_DYNAMIC_STORAGE_H

template<typename T, typename pT = const T & >
class DynamicMultiStorage 
{
    public:
    typedef T value_type;
    typedef T *pointer;
    typedef T &reference;
    typedef pT pass_t;
    
    DynamicMultiStorage() { };
    
    pass_t operator [](size_t i) const 
    { 
    reference operator [](size_t i);
    
    void reserve(size_t size)
    {
        if(
        if(!objects)
    }
    
    size_t size() const { return objects ? objects->size : 0; };
    size_t capacity() const { return objects ? objects->capacity : 0; };
    
    private:
    void boundsCheck(size_t i)
    {
        if(i >=
    }
        
    struct storage_t {
        size_t size, capacity;
        value_type objects[];
    }
    
    storage_t objects;
}

#endif
