#ifndef __STRING_CONVERT_H
#define __STRING_CONVERT_H

#include <string>
#include <sstream>

/*
template<typename T>
inline bool convert(const std::string &src, T &dest)
{
    std::istringstream in(src);
    in >> dest;
    return in.good();
}

template<typename T>
inline bool convert(const T &src, std::string &dest)
{
    std::ostringstream out;
    out << src;
    dest = out.str();
    return out.good();
}

inline bool canConvertToSigned(const std::string &s)
{
    signed long temp;
    std::istringstream in(s);
    in >> temp;
    return in.good();
}

inline bool canConvertToUnsigned(const std::string &s)
{
    unsigned long temp;
    std::istringstream in(s);
    in >> temp;
    return in.good();
}

inline bool canConvertToFloat(const std::string &s)
{
    long double temp;
    std::istringstream in(s);
    in >> temp;
    return in.good();
}


template<typename T>
inline bool canConvert(const std::string &s)
{ return false; };

template<>
inline bool canConvert<char>(const std::string &s)
{ return s.length() == 1; };

template<>
inline bool canConvert<unsigned char>(const std::string &s)
{ return canConvertToUnsigned(s); }

template<>
inline bool canConvert<signed char>(const std::string &s)
{ return canConvertToSigned(s); }

template<>
inline bool canConvert<unsigned int>(const std::string &s)
{ return canConvertToUnsigned(s); }

template<>
inline bool canConvert<signed int>(const std::string &s)
{ return canConvertToSigned(s); }

template<>
inline bool canConvert<unsigned long>(const std::string &s)
{ return canConvertToUnsigned(s); }

template<>
inline bool canConvert<signed long>(const std::string &s)
{ return canConvertToSigned(s); }

template<>
bool canConvert<float >(const std::string &s)
{ return canConvertToFloat(s); };

template<>
bool canConvert<double>(const std::string &s)
{ return canConvertToFloat(s); };

template<>
bool canConvert<long double>(const std::string &s)
{ return canConvertToFloat(s); };


template<typename T>
inline std::string toString(const T &src)
{
    std::string retv;
    convert(src, retv);
    return retv;
}

template<typename T>
inline T fromString(const std::string &src)
{
    T retv;
    return convert(src, retv);
}
*/

template<class T>
struct std_string_convert {
    static void convert(const std::string &src, T &dest) 
//        throw(std::ios::failure)
    {
        std::istringstream in(src);
        in.exceptions(std::ios::failbit | std::ios::badbit);
//        in.exceptions(std::ios::failbit | std::ios::eofbit | std::ios::badbit);
        
        in >> dest;
    }
    
    static void convert(const T &src, std::string &dest)
    {
        std::ostringstream out;
        out << src;
        dest = out.str();
    }        
    
    static bool canConvert(const std::string &src)
    {
        std::istringstream in(src);
        T temp;
        
        in >> temp;
        
        return !in.fail();
    }
};

template<class T>
struct string_convert;

template<>
struct string_convert<char> : public std_string_convert<char> { };
template<>
struct string_convert<unsigned char> : public std_string_convert<unsigned char> { };
template<>
struct string_convert<signed char> : public std_string_convert<signed char> { };
template<>
struct string_convert<unsigned int> : public std_string_convert<unsigned int> { };
template<>
struct string_convert<signed int> : public std_string_convert<signed int> { };
template<>
struct string_convert<unsigned long> : public std_string_convert<unsigned long> { };
template<>
struct string_convert<signed long> : public std_string_convert<signed long> { };
template<>
struct string_convert<float> : public std_string_convert<float> { };
template<>
struct string_convert<double> : public std_string_convert<double> { };
template<>
struct string_convert<long double> : public std_string_convert<long double> { };


template<class T>
void convert(const std::string &src, T &dest) 
{ string_convert<T>::convert(src,dest); }
    
template<class T>
void convert(const T &src, std::string &dest)
{ string_convert<T>::convert(src,dest); }
    
template<class T>
bool canConvert(const std::string &s)
{ return string_convert<T>::canConvert(s); }

template<class T>
std::string toString(const T &src)
{
    std::string retv;
    convert(src, retv);
    return retv;
}


#endif
