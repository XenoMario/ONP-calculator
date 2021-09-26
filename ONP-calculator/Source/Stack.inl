#include "Stack.h"

template<typename T>
inline void Stack<T>::push(const T& en)
{
	if (top == nullptr)
	{
		top = new Element;
		top->value = en;
	}
	else
	{
		Element* bufor = new Element;
		bufor->value = en;
		bufor->prior = top;
		top->next = bufor;
		top = bufor;
	}
}

template<typename T>
inline T Stack<T>::pop()
{


	return T();
}
