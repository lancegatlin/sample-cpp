#include <iostream>
#include <fstream>
#include <sstream>
#include <boost/regex.hpp>

using namespace std;

bool try_imbed_file(std::string &s)
{
    if(s[0] == '@')
    {
        string fname = s.substr(1);
        ifstream in(fname.c_str());
        
        if(!in)
        {
            cout << "Unable to open " << fname << endl;
            return false;
        }
        
        s.clear();
        string line;
        while(getline(in, line))
        {
            s += line;
            s += "\n";
        }
    }
    return true;
}

size_t tab_count = 0;

struct indent {
    size_t tab_count;
    indent(size_t _tab_count) : tab_count(_tab_count) { };
};

ostream &operator <<(ostream &out, indent ind)
{
    for(size_t i=0;i<ind.tab_count;i++)
        out << '\t';
    return out;
}

/*
struct node {
    list<node *> children;
    string s;
    boost::ssub_match sub;
    
    node() { };
    
    node(const string &_s, const boost::ssub_match &_sub) 
    : s(_s), sub(_sub) 
    { };
    
    ~node()
    {
        for(list<node *>::iterator i=children.begin();i!=children.end();i++)
            delete *i;
    }
    
    void dump(size_t n=0, size_t count=0)
    {
        cout << indent(n)
             << '[' << count << ']'
             << '(' << sub.first - s.begin() << ',' << sub.second - s.begin() << ')'
             << " = " << sub << endl;
                 
        count = 0;
        for(
                list<node *>::iterator i=children.begin()
                ;i!=children.end()
                ;++count,++i
            )
        {
            (*i)->dump(n+1, count);
        }
    }
};

struct dump_regex_recurse {
    node *n;
    
    dump_regex_recurse(node &_n) : n(&_n) { };
    // default copy
    
    
    dump_regex_recurse operator()(const string &s, size_t regex_n, size_t count, const boost::ssub_match &sub)
    {
        node *new_node = new node(s, sub);
        n->children.push_back(new_node);
        
        return dump_regex_recurse(*new_node);
    }             
};

template<class ForwardIterator, class Op>
void regex_recurse( ForwardIterator expr
                    ,ForwardIterator expr_end
                    ,const string &s
                    ,Op op
                    ,size_t recurse_n = 0)
{
    if(expr == expr_end)
        return;
        
    string s_expr(*expr++);
    
    boost::regex rx(s_expr);
    
    static const int subs[] = { 1 };
    static const int nosubs[] = { 0 };
    
    boost::sregex_token_iterator i
            (
                s.begin()
                ,s.end()
                ,rx
                ,(expr == expr_end ? nosubs : subs)
            )
        ,end;
    
    for(size_t count =0;i != end;++i,++count)
    {
        regex_recurse
                    (  
                        expr
                        ,expr_end
                        ,*i
                        ,op(s, recurse_n, count, *i)
                        ,recurse_n + 1
                    );
    }
}

template<class ForwardIterator>
void regex_recurse( ForwardIterator expr
                    ,ForwardIterator expr_end
                    ,const string &s
                    ,size_t recurse_n = 0)
{
    if(expr == expr_end)
        return;
        
    string s_expr(*expr++);
    
    boost::regex rx(s_expr);
    
    static const int subs[] = { 1 };
    static const int nosubs[] = { 0 };
    
    boost::sregex_token_iterator i
            (
                s.begin()
                ,s.end()
                ,rx
                ,(expr == expr_end ? nosubs : subs)
            )
        ,end;
    
    for(size_t count =0;i != end;++i,++count)
    {
        regex_recurse
                    (  
                        expr
                        ,expr_end
                        ,*i
                        ,op(s, recurse_n, count, *i)
                        ,recurse_n + 1
                    );
    }
}
*/

template<class ForwardIterator>
void regex_recurse( ForwardIterator expr
                    ,ForwardIterator expr_end
                    ,const string &s
                    ,size_t recurse_n = 0)
{
    if(expr == expr_end)
        return;
        
    string s_expr(*expr++);
    
    boost::regex rx(s_expr);
    
    static const int subs[] = { 1 };
    static const int nosubs[] = { 0 };
    
    boost::sregex_token_iterator i
            (
                s.begin()
                ,s.end()
                ,rx
                ,(expr == expr_end ? nosubs : subs)
            )
        ,end;
    
    for(size_t count =0;i != end;++i,++count)
    {
        cout << indent(recurse_n)
             << '[' << count << ']'
             << '(' << i->first - s.begin() << ',' << i->second - s.begin() << ')'
             << " = " << *i << endl;

        regex_recurse
                    (  
                        expr
                        ,expr_end
                        ,*i
                        ,recurse_n + 1
                    );
    }
}

int main(int argc, char **argv)
{
    try {
        
    string expressions, s;
    
    if(argc > 1)
        expressions = argv[1];
    else
    {
        cout << "Enter regex:" << endl;
        cin >> expressions;
    }
    
    if(!try_imbed_file(expressions))
        return 0;

    boost::regex rx("\\n");
    
    boost::sregex_token_iterator expr(expressions.begin(), expressions.end(), rx, -1), end;
            
        
    if(argc > 2)
        s = argv[2];
    else
    {
        cout << "Enter string:" << endl;
        cin >> s;
    }
        
    if(!try_imbed_file(s))
        return 0;
    
//    node n;
    
//    regex_recurse(expr, end, s, dump_regex_recurse(n));
    regex_recurse(expr, end, s);
    
//    n.dump();
    
    }
    catch(std::exception x)
    {
        cout << x.what() << endl;
    }
    
    system("PAUSE");
    
    return 0;
}
