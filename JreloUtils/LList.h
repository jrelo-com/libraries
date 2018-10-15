#pragma once
#include <Arduino.h>
#include <Node.h>



template <typename Generic> class LList {

    private:

        Node<Generic> *last = NULL;
        int _size = 0;

    public:

        LList();
        ~LList();
        void add(Generic *generic);
        Generic* get(int index) ;
        int size();
        void removeAll() ;

};


#include "LList.tpp"