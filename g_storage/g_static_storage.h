#ifndef __G_STORAGE_STATIC_H
#define __G_STORAGE_STATIC_H

namespace g_global {
    
template<typename T, typename pT = const T & >
class StaticSingleStorage 
{
    public:
    typedef T value_type;
    typedef T &reference;
    typedef pT pass_t;
 
    StaticSingleStorage() { };
       
    pass_t operator *() const { return object; };
    reference operator *() { return object; };

    private:
    value_type object;
}

template<typename T, typename pT = const T & >
class StaticMultiStorage 
{
    public:
    typedef T value_type;
    typedef T *pointer;
    typedef T &reference;
    typedef pT pass_t;
    
    StaticMultiStorage() { };
    
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

} // namespace g_global

#endif
