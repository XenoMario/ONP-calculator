#pragma once 

#include <iostream>

template<typename T>
class Stack
{
    int size = 0;

    struct Element
    {
        T value;
        Element* next = nullptr;
        Element* prior = nullptr;
    };

    Element* top = nullptr;

public:

    void push(const T&);
    T pop();
    T Top() const { return top->value; }

    Stack& operator=(const Stack&);

    bool isempty() const { return size == 0 ? 1 : 0; }

    void Show() const;
    void Adresses() const;

    ~Stack();
};


