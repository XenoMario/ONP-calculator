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
    Queue() = default;

    void push_back(const T& x);
    T pop_front();

    Queue& operator=(const Queue& l);
 
    bool isempty() const { return front == nullptr ? 1 : 0; }
    void Show() const;

    ~Queue();
};

template<typename T>
Queue<T>::Queue(const Queue<T>& l)
{
    if (l.front != nullptr)
    {
        this->front = new Node;
        rear = front;

        Node* temp;
        temp = l.front;

        while (true)
        {
            this->rear->value = temp->value;

            if (temp->prior != nullptr)
            {
                Node* new_one = new Node;
                new_one->next = this->rear;
                this->rear->prior = new_one;
                rear = new_one;
            }
            else
                break;

            temp = temp->prior;
        }
    }
    else return;
}


template<typename T>
void Queue<T>::push_back(const T& x)
{
    if (front == nullptr)
    {
        front = new Node;
        rear = front;
        front->value = x;
    }
    else
    {
        Node* new_one = new Node;
        new_one->next = rear;
        rear->prior = new_one;
        rear = new_one;

        new_one->value = x;
    }
}

template<typename T>
T Queue<T>::pop_front()
{
    Node* temp;
    temp = front;

    front = front->prior;

    T val;
    val = temp->value;

    delete temp;
    return val;
}


template<typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& l)
{
    if (this == &l)
        return *this;
    else if (l.front != nullptr)
    {
        Node* temp;
        while (front != nullptr)
        {
            temp = this->front;
            this->front = this->front->prior;
            delete temp;
        }

        this->front = new Node;
        rear = front;
        temp = l.front;

        while (true)
        {
            this->rear->value = temp->value;

            if (temp->prior != nullptr)
            {
                Node* new_one = new Node;
                new_one->next = this->rear;
                this->rear->prior = new_one;
                rear = new_one;
            }
            else
                break;

            temp = temp->prior;
        }

        return *this;
    }
    else 
        return *this;
}

template<typename T>
void Queue<T>::Show() const
{
    Node* temp = front;

    while (temp != nullptr)
    {
        cout << temp->value << " ";
        temp = temp->prior;
    }
    cout << endl;
}

template<typename T>
Queue<T>::~Queue()
{
    Node* temp;
    while (front != nullptr)
    {
        temp = front;
        front = front->prior;
        delete temp;
    }
}