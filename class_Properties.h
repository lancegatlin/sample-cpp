#ifndef __CLASS_PROPERTIES_H
#define __CLASS_PROPERTIES_H

#include <map>
#include <StringValue.h>

/*
    Author: lance.gatlin@yahoo.com
    Date: 01 Aug 2008
*/

typedef StringValue PropertyValue;
typedef std::string PropertyName;
typedef std::map<PropertyName, PropertyValue> PropertyMap;

// This class is a convenience class that is used to create a compile time
// property name string/type association. Use it to prevent typos in a string
// from creating wierd run-time bugs:
// ...
// Properties p;
// p["naame"]; // whoops this is going to return nothing and no error grrr
// ...
// Property<string> NAME("name"); 
// p[NAAME]; // Ah much better, compile error instead now
// p[NAME]; // also guaranteed to return a string at compile-time

template<class T>
class Property : public std::string {
    public:
    Property(const char *s)
    : std::string(s) { };
};


class Properties : public PropertyMap  {
    public:
    typedef PropertyMap parent_t;
    typedef Properties this_t;

    // Adaptor class
    // Ensures the non-const operator[](Property<T>)
    // can only be a specific type
    template<class T>
    class LValue {
        PropertyValue *p;
        public:
        LValue(PropertyValue &_p)
        : p(&_p) { };
        
        // Default copy self
        
        operator T()
        { return *p; }
        
        LValue &operator =(const T &assign_me)
        { *p = assign_me; return *this; }
        
        // Default assign to self
    };

    Properties() { };
    
    // operator[](Property<T>) functions
    // See docs above for usage
    // 
    template<class T>
    LValue<T> operator[](const Property<T> &p)
    { return parent_t::operator[](p); };
    
    template<class T>
    T operator[](const Property<T> &p) const
    { 
        // Try to find the property in the map
        const_iterator i = parent_t::find(p);
        // If it doesn't exist 
        if(i == end())
            // return the default value for the type bound to p
            return T();
            
        // If it was found return the PropertyValue 
        return i->second;
    };
    
    // Normal operator[]
    // Redeclared so that a const version could be declared without wierd
    // compiler errors
    PropertyValue &operator[](const std::string &s)
    { return parent_t::operator[](s); }
    
    // Fix small limitations with map to allow for const operator []
    const PropertyValue &operator[](const std::string &p) const
    {
        static PropertyValue empty;
        
        // Try to find the property in the map
        const_iterator i = parent_t::find(p);
        // If it doesn't exist
        if(i == end())
            // Just return an empty PropertyValue
            return empty;
            
        // property existed, so return the PropertyValue
        return i->second;
    }
};

#endif
