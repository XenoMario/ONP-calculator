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

class List
{
    struct Node
    {
        double number;
        char sign;
        bool nors;

        Node* next = nullptr;
        Node* prior = nullptr;
    };

    Node* front = nullptr;
    Node* rear = nullptr;

public:

    template<typename T>
    void push_back(const T& x);
    template<typename T>
    T pop_front();

    List& operator=(const List& l);

    bool isempty() const { return front == nullptr ? 1 : 0; }
    bool first_is_number() const;
    bool isnumber(const Node* temp) const;
    void Show() const;

    ~List();
};


