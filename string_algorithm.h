#ifndef __STRINGUTIL_H
#define __STRINGUTIL_H

#include <string>

inline std::string right(const std::string &s, size_t n)
{
	return s.substr(s.length() -  n, n);
}

inline std::string left(const std::string &s, size_t n)
{
	return s.substr(0, n);
}

template<class tokenList>
inline void parse(const std::string &input, tokenList &tokens, const std::string &delim = std::string(" \t\n"))
{
    tokens.clear();
    
    std::string::size_type 
        token_start = input.find_first_not_of(delim, 0);
    
    std::string::size_type
        token_end = input.find_first_of(delim, token_start);
    
    while(token_start != std::string::npos)
    {
        if(token_end == std::string::npos)
        {
            tokens.push_back(input.substr(token_start, input.length() - token_start));
            break;
        }
        else tokens.push_back(input.substr(token_start, token_end - token_start));
        
        token_start = input.find_first_not_of(delim, token_end);
        token_end = input.find_first_of(delim, token_start);
    }
    
}

inline std::string trim(const std::string &s, const std::string &whitespace = std::string(" \t\n"))
{
    std::string::size_type first_non_whitespace 
        = s.find_first_not_of(whitespace);
    
    std::string::size_type last_non_whitespace
        = s.find_last_not_of(whitespace);
    
    if(first_non_whitespace == std::string::npos)
        return std::string();

    return s.substr(first_non_whitespace, last_non_whitespace - first_non_whitespace + 1);
}


#endif
