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

template<typename T>
void List::push_back(const T& x)
{

    if (front == nullptr)
    {
        front = new Node;
        rear = front;

        if (typeid(x) == typeid(double) || typeid(x) == typeid(int))
        {
            front->number = x;
            front->sign = '.';
            front->nors = 1;
        }
        else
        {
            cout << "hello" << endl;
            front->number = 0;
            front->sign = x;
            front->nors = 0;
        }
    }
    else
    {
        Node* new_one = new Node;
        new_one->next = rear;
        rear->prior = new_one;
        rear = new_one;

        if (typeid(x) == typeid(double) || typeid(x) == typeid(int))
        {
            new_one->number = x;
            new_one->sign = ';';
            new_one->nors = 1;
        }
        else
        {
            new_one->number = 0;
            new_one->sign = x;
            new_one->nors = 0;
        }
    }
}

template<typename T>
T List::pop_front()
{
    Node* temp;
    temp = front;

    front = front->prior;

    T val;

    if (temp->number != 0)
        val = temp->number;
    else
        val = temp->sign;

    delete temp;
    return val;
}

List& List::operator=(const List& l)
{
    if (this == &l) return *this;


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
        this->rear->number = temp->number;
        this->rear->sign = temp->sign;
        this->rear->nors = temp->nors;

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

bool List::isnumber(const Node* temp) const
{
    return temp->nors == 1 ? 1 : 0;
}

void List::Show() const
{
    Node* temp = front;

    while (temp != nullptr)
    {
        if (isnumber(temp))
            cout << temp->number << " ";
        else
            cout << temp->sign << " ";
        temp = temp->prior;
    }
    cout << endl;
}

bool List::first_is_number() const
{
    return isnumber(front);
}

List::~List()
{
    Node* temp;
    while (front != nullptr)
    {
        temp = front;
        front = front->prior;
        delete temp;
    }
}
