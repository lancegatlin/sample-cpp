#ifndef __G_STORAGE_H
#define __G_STORAGE_H

/*

    template<typename T, typename pT = const T & >
    concept SingleStorage 
    {
        typedef T value_type;
        typedef T &reference;
        typedef pT pass_t;
        
        pass_t operator *() const;
        reference operator *();
    }
    
    template<typename T, typename pT = const T & >
    concept MultiStorage 
    {
        typedef T value_type;
        typedef T &reference;
        typedef pT pass_t;
        
        pass_t operator [](size_t) const;
        reference operator [](size_t);
        
        void reserve(size_t size);
    }
    
*/

#endif
