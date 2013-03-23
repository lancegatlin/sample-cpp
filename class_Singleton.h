#ifndef __CLASS_SINGLETON_H
#define __CLASS_SINGLETON_H

/*
    Author: lance.gatlin@yahoo.com
    Date: 01 Aug 2008
*/

template<class Derived>
class Singleton {
    protected:
    Singleton() { };
    
    static Derived *singleton;
    
    public:
    static Derived &getSingleton()
    {
		static Derived singleton;
        return singleton;
    }
};

#endif
