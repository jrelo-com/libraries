#pragma once
#include <Arduino.h>

template <typename Generic> class Node {

    public:
        Node *previous = NULL;
        Generic *generic = NULL;

        Node();
        ~Node();
};

#include <Node.tpp>
