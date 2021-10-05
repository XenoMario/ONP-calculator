#pragma once

#include <iostream>

using std::cout;
using std::endl;

template<typename T>
class Queue
{
    struct Node
    {
        T value;
        Node* next = nullptr;
        Node* prior = nullptr;
    };

    Node* front = nullptr;
    Node* rear = nullptr;

public:

    Queue(const Queue<T>& l);
    Queue(Queue&&);
    Queue() = default;

    void push_back(const T& x);
    T pop_front();

    Queue& operator=(const Queue& l);
    Queue& operator=(Queue&&);
 
    bool isempty() const { return front == nullptr ? 1 : 0; }
    void Show() const;

    ~Queue();
};

