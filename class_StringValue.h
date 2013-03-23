#ifndef __STRINGVALUE_H
#define __STRINGVALUE_H

#include <string>
#include <sstream>

/*
    Author: lance.gatlin@yahoo.com
    Date: 01 Aug 2008
*/

/*
    Used to provide a really simple "super" string storage system.
    As long as the type can be read and written to a stream then
    it can be stored in a StringValue object. All intrinsic types
    automatically qualify (float,double,unsigned long etc)
    
    Example:
    void func(float f);
    
    ....
    
    StringValue s(1.0239f); // automatic conversion from float to string
    func(s); // automatic conversion from string to float
    cout << s; // no conversion, just print the string version of the float
*/

class StringValue : public std::string {
    public:
    StringValue() { };
    
    template<class T>
    StringValue(const T &copy_me) 
    { 
        convertFrom(copy_me); 
    };
    StringValue(const StringValue &s)
    : std::string(s) { };
    StringValue(const std::string &s)
    : std::string(s) { };
    StringValue(const char *s)
    : std::string(s) { };
    
    template<class T>
    operator T() const 
    { 
        T retv;
        convertTo(retv);
        return retv;
    }
    
    template<class T>
    StringValue &operator =(const T &copy_me)
    {
        convertFrom(copy_me);
        return *this;
    }
    StringValue &operator =(const StringValue &copy_me)
    {
        assign(copy_me);
        return *this;
    }
    StringValue &operator =(const std::string &copy_me)
    {
        assign(copy_me);
        return *this;
    }
    StringValue &operator =(const char *copy_me)
    {
        assign(copy_me);
        return *this;
    }
    
    bool operator ==(const StringValue &s)
    { return (const std::string &)*this == (const std::string &)s; };
    
    template<class T>
    void convertFrom(const T &convert_me)
    {
        std::ostringstream out;
        out << convert_me;
        assign(out.str());
    }
    void convertFrom(const std::string &s)
    { *this = s; }
    void convertFrom(const StringValue &s)
    { *this = s; }
    void convertFrom(const char *s)
    { *this = std::string(s); }

    template<class T>
    void convertTo(T &assign_me) const
    {
        std::istringstream in(*this);
        in >> assign_me;
    }
    void convertTo(std::string &s) const
    { s = *this; };
    void convertTo(StringValue &s) const
    { s = *this; };
};


#endif
