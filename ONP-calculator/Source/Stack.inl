#include "Stack.h"

using std::cout;
using std::endl;

template<typename T>
void Stack<T>::push(const T& v)
{
    if (top == nullptr)
    {
        top = new Element;
        top->value = v;
    }
    else
    {
        Element* new_one = new Element;
        new_one->value = v;

        top->next = new_one;
        new_one->prior = top;

        top = new_one;
    }

    size++;
}

template<typename T>
T Stack<T>::pop()
{
    T val = top->value;

    Element* destroy = top;
    top = top->prior;
    if (top != nullptr)
        top->next = nullptr;

    delete destroy;

    size--;

    return val;
}

template<typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& st)
{
    if (this == &st) return *this;

    Element* temp;
    while (this->top != nullptr)
    {
        temp = this->top;
        this->top = this->top->prior;
        delete temp;
    }

    this->top = new Element;
    //this->top->next = nullptr;
    //this->top->prior = nullptr;
    //this->top->value = st.top->value;

    this->size = 1;

    for (size_t i = 1; i < st.size; i++)
    {
        Element* add = new Element;
        add->prior = this->top;
        this->top->next = add;
        this->top = add;
        this->size++;
    }

    Element* from = st.top;
    Element* to = this->top;

    while (from != nullptr)
    {
        to->value = from->value;
        from = from->prior;
        to = to->prior;
    }
}

template<typename T>
void Stack<T>::Show() const
{
    cout << "Stack content:" << endl;
    for (Stack<T> temp = *this; !temp.isempty(); temp.pop())
        std::cout << "value: " << temp.top->value << endl;

    cout << endl;
}

template<typename T>
void Stack<T>::Adresses() const
{
    Element* temp = top;

    while (temp != nullptr)
    {
        cout << temp << " ";
        temp = temp->prior;
    }
}

template<typename T>
Stack<T>::~Stack<T>()
{
    Element* temp;
    while (top != nullptr)
    {
        temp = top;
        top = top->prior;
        delete temp;
    }
}


